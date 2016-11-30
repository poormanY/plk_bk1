#include "stdafx.h"
#include "resource.h"
#include "EOL_TEST_R7.h"
#include "R7EOLvs2010Dlg.h"
#include "SettingDlg.h"
#include <mmsystem.h>	// sndPlaySound

#include "y_IoBoardMgt.h"
#include "y_BarcodeMgt.h"
#include "y_Debugging.h"
#include "y_Color.h"
#include "y_JTP_Com.h"

extern CR7EOLvs2010Dlg	*pMainDlg;
extern CEOL_R7		*EOL_TEST_R7;

static CIoBoardMgt	*pIoBoard = NULL;		// IO Board Ŭ����
static CBarcodeMgt	*pBarCode1 = NULL;		// Barcode1 Ŭ����
static CBarcodeMgt	*pBarCode2 = NULL;		// Barcode2 Ŭ����
static JTP_Com		m_JTP_Com;				// JTP Protocol Ŭ����

CEOL_R7::CEOL_R7()
{
	m_tThreadStop = false;
	bLogStart = false;
}

CEOL_R7::~CEOL_R7()
{
	m_tThreadStop = true;
}


BOOL CEOL_R7::START_EOL_TEST(void)
{	
	// Init
	//m_nVehicleLdwSpd = 


    // New Start Thread
    m_tThreadStop = false;
    m_pThread = AfxBeginThread(ThreadEolTest_R7, this);

    if (m_pThread == NULL)
    {
        END_EOL_TEST();
        return false;
    }

    return true;
}

BOOL CEOL_R7::END_EOL_TEST()
{
	// ADAS �׽�Ʈ ����
	m_tThreadStop = true;
	
	return TRUE;
}


UINT ThreadEolTest_R7(LPVOID pParam)
{
	pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, pMainDlg->strProductName + _T("\r\n�˻� �����"), UPDATE_ON);

	CString strProcess;
	int nTotalProcess = 0;
	int nCurProcess = 1;
	int nPassNum = 0, nFailNum = 0;
	CString strPassNum = _T("0"), strFailNum = _T("0"), strTotalNum, strPassPercent;

	EOL_TEST_R7->m_EOLTestResult = PASS;

	// ADAS �Է� ������
	EOL_TEST_R7->m_nVehicleSpeed = 0;
	EOL_TEST_R7->m_bWinkL = 0;
	EOL_TEST_R7->m_bWinkR = 0;
	
    pMainDlg->m_list_test_process.DeleteAllItems();	// ����Ʈ ��� ������ �����
	pMainDlg->m_edit_pass_num.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);			// ��ǰ���� ǥ��
	pMainDlg->m_edit_fail_num.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);			// �ҷ����� ǥ��
	pMainDlg->m_edit_total_num.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);		// ��ü���� ǥ��
	pMainDlg->m_edit_pass_percent.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);		// ��ǰ���� ǥ��

	pMainDlg->m_edit_in_speed.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);				// �Է¼ӵ� ǥ��
	pMainDlg->m_edit_in_wink_l.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);			// �Է¹������õ� ǥ��
	pMainDlg->m_edit_in_wink_r.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);			// �Է¹������õ� ǥ��
	pMainDlg->m_edit_out_ldw_detetc_l.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);		// �����ν� ǥ��
	pMainDlg->m_edit_out_m_ldw_detect_r.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);	// �����ν� ǥ��
	pMainDlg->m_edit_out_ldw_warn_l.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);		// �����溸 ǥ��
	pMainDlg->m_edit_out_ldw_warn_r.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);		// �����溸 ǥ��
	pMainDlg->m_edit_out_hmw.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);				// HMW�溸 ǥ��
	pMainDlg->m_edit_out_fcw.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);				// FCW�溸 ǥ��

	// �˻� ���� ��
	if ( pMainDlg->bEnStep_McuVer     == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_SwVer	  == 1 ) 	nTotalProcess++;
	if ( pMainDlg->bEnStep_SerialNum  == 1 )	nTotalProcess++;
	//if ( pMainDlg->bEnStep_IoBoard  == 1 )	nTotalProcess++;
	//if ( pMainDlg->bEnStep_Screw	  == 1 ) 	nTotalProcess++;
	//if ( pMainDlg->bEnStep_Bar1	  == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_Bar2	  	  == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_Accleration== 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_SpeedPulse == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_DTC_Clear  == 1 )	nTotalProcess++;

	if ( pMainDlg->bEnStep_LDW_Detect == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_LDW_Warn_L == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_LDW_Warn_R == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_FCW_Warn	  == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_FCDA_Warn == 1 )		nTotalProcess++;
	if ( pMainDlg->bEnStep_LDW_WarnL_WinkL == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_LDW_WarnL_WinkR == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_LDW_WarnL_WinkLR == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_LDW_WarnR_WinkL == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_LDW_WarnR_WinkR == 1 )	nTotalProcess++;
	if ( pMainDlg->bEnStep_LDW_WarnR_WinkLR == 1 )	nTotalProcess++;

	// ADAS �̹��� ����
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->CALIBRATION);

	if ( pMainDlg->bEnStep_IoBoard == 1 )
	{
		if ( EOL_TEST_R7->m_tThreadStop == false )
		{
			if ( EOL_TEST_R7->STEP_CONNECT_IOBOARD() == FALSE )
			{
				EOL_TEST_R7->m_tThreadStop = true;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("IO���� �������"), UPDATE_ON);
				AfxMessageBox(_T("IO���� �������"));
			}
		}

		if ( (EOL_TEST_R7->m_tThreadStop == false)  && (pMainDlg->bEnStep_Bar1) )
		{
			if ( EOL_TEST_R7->STEP_CONNECT_BARCODE1() == FALSE )
			{
				EOL_TEST_R7->m_tThreadStop = true;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("���ڵ� ��ĳ��1 �������"), UPDATE_ON);
				AfxMessageBox(_T("���ڵ� ��ĳ��1 �������"));
			}
		}

		if ( (EOL_TEST_R7->m_tThreadStop == false)  && (pMainDlg->bEnStep_Bar2) )
		{
			if ( EOL_TEST_R7->STEP_CONNECT_BARCODE2() == FALSE )
			{
				EOL_TEST_R7->m_tThreadStop = true;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("���ڵ� ��ĳ��2 �������"), UPDATE_ON);
				AfxMessageBox(_T("���ڵ� ��ĳ��2 �������"));
			}
		}
	}

	// �׽�Ʈ �α� ��� ����
	if ( EOL_TEST_R7->m_tThreadStop == false )
	{
		EOL_TEST_R7->START_EOL_TEST_LOG();
		EOL_TEST_R7->bLogStart = true;
	}
	while ( EOL_TEST_R7->m_tThreadStop == false )
	{		
		pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, pMainDlg->strProductName + _T("\r\n�˻� �����"), UPDATE_ON);

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( pMainDlg->bEnStep_IoBoard == 1 )
		{
			if ( EOL_TEST_R7->STEP_CONNECT_POWER() == FALSE )
			{
				EOL_TEST_R7->m_tThreadStop = true;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n���� �������"), UPDATE_ON);
			}
		}

		// �׽�Ʈ ���μ��� ī��Ʈ
		nCurProcess = 1;
		EOL_TEST_R7->m_EOLTestResult = PASS;
		// List Item All Clear
		pMainDlg->m_list_test_process.DeleteAllItems();
		
		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( EOL_TEST_R7->m_EOLTestResult == PASS )
		{
			if ( EOL_TEST_R7->STEP_CONNECT_USART() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\nUSART ��Ž���"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult) == PASS && (pMainDlg->bEnStep_SerialNum == 1) )
		{
			if ( EOL_TEST_R7->STEP_CHK_SERIAL() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\nSerial��ȣ Ȯ�ν���"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult) == PASS && (pMainDlg->bEnStep_SwVer == 1) )
		{
			if ( EOL_TEST_R7->STEP_CHK_SW_VERSION() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\nS/W���� Ȯ�ν���"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}
		
		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult) == PASS && (pMainDlg->bEnStep_McuVer == 1) )
		{
			if ( EOL_TEST_R7->STEP_CHK_MCU_VERSION() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\nMCU���� Ȯ�ν���"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}
		
		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_Accleration == 1) )
		{
			if ( EOL_TEST_R7->STEP_CHK_VANISH() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n���ӵ��� Ȯ�ν���"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}
		
		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_SpeedPulse == 1) )
		{
			if ( EOL_TEST_R7->STEP_CHK_SPEED_PULSE() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�ӵ��޽��� Ȯ�ν���"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_LDW_Detect == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_LDW_DETECT() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n���� �νĽ���"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}
		
		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_LDW_Warn_L == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_LDW_LEFT_WARN() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�������� �溸����"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}
		
		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_LDW_Warn_R == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_LDW_RIGHT_WARN() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�������� �溸����"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_LDW_WarnL_WinkL == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_LDW_LEFT_WARN_WINK_L() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�������� �溸����\r\n�������õ�(��)"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_LDW_WarnR_WinkR == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_LDW_RIGHT_WARN_WINK_R() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�������� �溸����\r\n�������õ�(��)"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_LDW_WarnL_WinkR == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_LDW_LEFT_WARN_WINK_R() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�������� �溸����\r\n�������õ�(��)"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_LDW_WarnR_WinkL == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_LDW_RIGHT_WARN_WINK_L() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�������� �溸����\r\n�������õ�(��)"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_LDW_WarnL_WinkLR == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_LDW_LEFT_WARN_WINK_LR() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�������� �溸����\r\n���������"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_LDW_WarnR_WinkLR == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_LDW_RIGHT_WARN_WINK_LR() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�������� �溸����\r\n���������"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}
		
		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_FCW_Warn == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_FCW_WARN() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n�����浹 �溸����"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_FCDA_Warn == 1) )
		{
			if ( EOL_TEST_R7->STEP_ADAS_FCDA_WARN() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\nFCDA �溸����"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}
		
		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_DTC_Clear == 1) )
		{
			if ( EOL_TEST_R7->STEP_DTC_ALL_CLEAR() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\nDTC ��������"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult == PASS) && (pMainDlg->bEnStep_IoBoard == 1) )
		{
			if ( EOL_TEST_R7->STEP_DISCONNECT_POWER() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n���� ��������"), UPDATE_ON);
			}
		}

		if ( EOL_TEST_R7->m_tThreadStop == true )
		{
			break;
		}
		else if ( (EOL_TEST_R7->m_EOLTestResult) == PASS && (pMainDlg->bEnStep_Bar2) )
		{
			if ( EOL_TEST_R7->STEP_CHECK_BARCODE2_SERIAL() == FALSE )
			{
				EOL_TEST_R7->m_EOLTestResult = FAIL;
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, _T("R7\r\n���̽� ���ڵ� ����"), UPDATE_ON);
			}
			else
			{
				strProcess.Format(_T("R7\r\n�˻��� %d/%d"), nCurProcess++, nTotalProcess);
				pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, strProcess, UPDATE_ON);
			}
		}

		////////////////////////////////////////////////////////////////////////////////////////
		// �˻� ��� - ��ǰ/�ҷ� �Ǵ�
		if ( EOL_TEST_R7->m_EOLTestResult == PASS )
		{
			pMainDlg->m_edit_notice.SetText(GREEN, BLACK, _T("��ǰ"), UPDATE_ON);
			pMainDlg->m_edit_notice2.SetText(GREEN, BLACK, pMainDlg->strProductName + _T("\r\n�˻� ���"), UPDATE_ON);

			if ( pMainDlg->bEnStep_IoBoard == 1 )
			{
				pIoBoard->PutOutBit(_BIT_OUT_LED_G_OK, true);
				pIoBoard->PutOutBit(_BIT_OUT_LED_R_NG, false);
			}
			CString strWavFile;
			strWavFile = _T("pass.wav");
			sndPlaySound (strWavFile, SND_ASYNC);

			nPassNum++;
			strPassNum.Format(_T("%d"), nPassNum);
		}
		else if ( EOL_TEST_R7->m_EOLTestResult == FAIL )
		{
			pMainDlg->m_edit_notice.SetText(RED, BLACK, _T("�ҷ�"), UPDATE_ON);
			pMainDlg->m_edit_notice2.SetText(RED, BLACK, pMainDlg->strProductName + _T("\r\n�˻� ����"), UPDATE_ON);
			
			if ( pMainDlg->bEnStep_IoBoard == 1 )
			{
				pIoBoard->PutOutBit(_BIT_OUT_LED_G_OK, false);
				pIoBoard->PutOutBit(_BIT_OUT_LED_R_NG, true);
			}
			AfxMessageBox(_T("�ҷ� �߻�"));

			nFailNum++;
			strFailNum.Format(_T("%d"), nFailNum);
		}
		strTotalNum.Format(_T("%d"), nPassNum+nFailNum);
		strPassPercent.Format(_T("%f"), (nPassNum/1.0)/(nFailNum/1.0));

		pMainDlg->m_edit_pass_num.SetText(SOFT_BLUE, GREY_ROAD, strPassNum, UPDATE_ON);			// ��ǰ���� ǥ��
		pMainDlg->m_edit_fail_num.SetText(SOFT_BLUE, GREY_ROAD,strFailNum, UPDATE_ON);			// �ҷ����� ǥ��
		pMainDlg->m_edit_total_num.SetText(SOFT_BLUE, GREY_ROAD, strTotalNum, UPDATE_ON);		// ��ü���� ǥ��
		pMainDlg->m_edit_pass_percent.SetText(SOFT_BLUE, GREY_ROAD, strPassPercent, UPDATE_ON);	// ��ǰ���� ǥ��

		////////////////////////////////////////////////////////////////////////////////////////
		// �׽�Ʈ �α� ���
		EOL_TEST_R7->SAVE_EOL_TEST_LOG();

		Sleep(1000);
	}
	// �׽�Ʈ �α� ��� ��
	if ( EOL_TEST_R7->bLogStart == TRUE )
	{
		EOL_TEST_R7->END_EOL_TEST_LOG();
		EOL_TEST_R7->bLogStart = FALSE;
	}
	
	// ������
	if ( pIoBoard != NULL )
	{
		EOL_TEST_R7->STEP_DISCONNECT_POWER();
	}
	EOL_TEST_R7->CloseIoBoard();
	EOL_TEST_R7->CloseBarcode1();
	EOL_TEST_R7->CloseBarcode2();

	
	// wait to finish thread
	delete EOL_TEST_R7;
	EOL_TEST_R7 = NULL;

	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("PLK Technologies\r\nLDWS ") + pMainDlg->strProductName + _T("\r\n��� �����˻�"), UPDATE_ON);
	pMainDlg->m_edit_notice2.SetText(SOFT_GREEN, BLACK, pMainDlg->strProductName + _T("\r\n�˻� ����"), UPDATE_ON);

	pMainDlg->PostMessageW(_WM_MAIN_DLG_END);

	return TRUE;
}

BOOL CEOL_R7::START_EOL_TEST_LOG()
{
	CString strLogFileName;
	CString strLogDay;
	CString strLogContent;
	CString strTester;
	CTime   oTime;

	oTime = CTime::GetCurrentTime();
	strLogDay.Format(_T("%d%d%d"), oTime.GetYear(), oTime.GetMonth(), oTime.GetDay());

	strLogFileName = pMainDlg->strLogPath;
	strLogFileName += _T("EOL_");
	strLogFileName += pMainDlg->strProductName;
	strLogFileName += _T("_");
	strLogFileName += strLogDay;
	strLogFileName += _T(".log");
	// EOL_R7_HMC_20161114.log
	pMainDlg->EOLSaveLog.SetFilePath(strLogFileName);

	strLogContent = _T("������� : ");
	strLogContent += pMainDlg->strProductLine;
	strLogContent += _T(", �˻��� : ");
	pMainDlg->m_combo_tester.GetLBText(pMainDlg->m_combo_tester.GetCurSel(), strTester);
	strLogContent += strTester;
	strLogContent += _T("\r\n");

	pMainDlg->EOLSaveLog.WriteLogTime(strLogContent);

	return true;
}

BOOL CEOL_R7::SAVE_EOL_TEST_LOG()
{
	int nListPos, nListSubPos, nListMax;
	int nItemLength, nSpaceNum;
	CString strItemTitle;
	CString strItemText;
	
	if ( EOL_TEST_R7->m_EOLTestResult == PASS )
	{
		strItemTitle.Format(_T("�׽�Ʈ%d [��ǰ]\r\n"), _ttoi(pMainDlg->m_edit_total_num.m_strMsg));
	}
	else if ( EOL_TEST_R7->m_EOLTestResult == FAIL )
	{
		strItemTitle.Format(_T("�׽�Ʈ%d [�ҷ�]\r\n"), _ttoi(pMainDlg->m_edit_total_num.m_strMsg));
	}
	pMainDlg->EOLSaveLog.WriteLogTime(strItemTitle);

	// Test ��� ����
	nListMax = pMainDlg->m_list_test_process.GetItemCount();
    for (nListPos = 0; nListPos < nListMax; nListPos++)
    {
		for (nListSubPos = 0; nListSubPos < 4; nListSubPos++)
		{
			strItemText = pMainDlg->m_list_test_process.GetItemText(nListPos, nListSubPos);
			pMainDlg->EOLSaveLog.WriteLog(strItemText);
						
			nSpaceNum = 26; // txt������ ���� ����(��������)
			nItemLength = strItemText.GetLength();
			while ( nItemLength-- > 0 )
			{
				// CString�� �ѱ��� ���
				if ( strItemText.GetAt(nItemLength) <= 0 || 127 < strItemText.GetAt(nItemLength) )
				{
					nSpaceNum -= 2;
				}
				else
				{
					nSpaceNum -= 1;
				}
			}
			while( nSpaceNum-- > 0 )
			{
				pMainDlg->EOLSaveLog.WriteLog(_T(" "));
			}
		}
		pMainDlg->EOLSaveLog.WriteLog(_T("\r\n"));
	}

	return true;
}

BOOL CEOL_R7::END_EOL_TEST_LOG()
{
	CString strLogContent;

	strLogContent = _T("��ǰ : ");
	strLogContent += pMainDlg->m_edit_pass_num.m_strMsg;
	strLogContent += _T(", �ҷ� : ");
	strLogContent += pMainDlg->m_edit_fail_num.m_strMsg;
	strLogContent += _T(", ��ü : ");
	strLogContent += pMainDlg->m_edit_total_num.m_strMsg;
	strLogContent += _T(", ��ǰ�� : ");
	strLogContent += pMainDlg->m_edit_pass_percent.m_strMsg;
	strLogContent += _T("\r\n**********************************************************************************\r\n");
	strLogContent += _T("\r\n\r\n");

	pMainDlg->EOLSaveLog.WriteLogTime(strLogContent);

	return true;
}

BOOL CEOL_R7::STEP_CONNECT_IOBOARD()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("IO ���� ������"), UPDATE_ON);
	
	// IO ���� �ʱ�ȭ
	pIoBoard = new CIoBoardMgt;
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
	
    if (pIoBoard == NULL)
    {
        return FALSE;
    }

	if (pIoBoard->Open(pbIoBdCom) == false)
    {
        dp("[%s] IO Board Open Fail!\n",pbIoBdCom);

		CloseIoBoard();
        return FALSE;
    }
		

	strIoBdProduct = _T("KM ");
    if (pIoBoard->TransferMsg("$01GA001\r") == false)
    {
        dp("[%s] IO Board communication error!!\n", pbIoBdCom);

		CloseIoBoard();
        return FALSE;
    }
	else
	{
		strIoBdProduct += (pIoBoard->GetMsg()+9);
	}

	strIoBdProduct += _T(" Ver ");
    if (strcmp(pIoBoard->GetMsg()+9, "6050") != 0)
    {
        dp("[%s] IO Board model %s error!\n",pbIoBdCom, pIoBoard->GetMsg()+9);

		CloseIoBoard();
        return FALSE;
    }
	else
	{
		strIoBdProduct += (pIoBoard->GetMsg()+9);
	}
		
	delete pbIoBdCom;
	pbIoBdCom= NULL;
	
	return TRUE;
}

BOOL CEOL_R7::STEP_CONNECT_BARCODE1()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("���ڵ� ��ĳ��1 ������"), UPDATE_ON);

	// ��Ʈ �ҷ�����
	CString strBar1Com;
	CLogManage	*pEolSetting;
	pEolSetting = new CLogManage;
	pEolSetting->SetFilePath(SETTING_FILE_PATH);
	strBar1Com = pEolSetting->ReadSetting(COM_BAR1);
	delete pEolSetting;
    pEolSetting = NULL;
		
	if ( pBarCode1 == NULL )
	{
		// ���ڵ� �ʱ�ȭ
		pBarCode1 = new CBarcodeMgt;

		if (pBarCode1->Open((CStringA)strBar1Com) == true)
		{
			dp("Barcode1 : %s Open Success\n", (CStringA)strBar1Com);

			// ���ڵ� Thread ����
			pBarCode1->Thread_Begin();
		}
		else
		{
			dp("Barcode1 : %s Open Fail\n", (CStringA)strBar1Com);

			CloseBarcode1();
		}
	}
	else
	{
		CloseBarcode1();
	}

	return TRUE;
}

BOOL CEOL_R7::STEP_CONNECT_BARCODE2()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("���ڵ� ��ĳ��2 ������"), UPDATE_ON);

	// ��Ʈ �ҷ�����
	CString strBar2Com;
	CLogManage	*pEolSetting;
	pEolSetting = new CLogManage;
	pEolSetting->SetFilePath(SETTING_FILE_PATH);
	strBar2Com = pEolSetting->ReadSetting(COM_BAR2);
	delete pEolSetting;
    pEolSetting = NULL;
	
	if ( pBarCode2 == NULL )
	{
		// ���ڵ� �ʱ�ȭ
		pBarCode2 = new CBarcodeMgt;

		if (pBarCode2->Open((CStringA)strBar2Com) == true)
		{
			dp("Barcode2 : %s Open Success\n", (CStringA)strBar2Com);

			// ���ڵ� Thread ����
			pBarCode2->Thread_Begin();
		}
		else
		{
			dp("Barcode2 : %s Open Fail\n", (CStringA)strBar2Com);

			CloseBarcode2();
		}
	}
	else
	{
		CloseBarcode2();
	}

	return TRUE;
}


BOOL CEOL_R7::CloseIoBoard()
{
	if (pIoBoard == NULL)
    {
        return FALSE;
    }

	delete pIoBoard;
    pIoBoard = NULL;
	dp("IO Board Close\n");

	return TRUE;
}
BOOL CEOL_R7::CloseBarcode1()
{
	if ( pBarCode1 == NULL )
	{
		return FALSE;
	}

	pBarCode1->Close();
	pBarCode1->DelAllData();
	delete pBarCode1;
	pBarCode1 = NULL;

	dp("Barcode1 Close\n");

	return TRUE;
}
BOOL CEOL_R7::CloseBarcode2()
{
	if ( pBarCode2 == NULL )
	{
		return FALSE;
	}

	pBarCode2->Close();
	pBarCode2->DelAllData();
	delete pBarCode2;
	pBarCode2 = NULL;

	dp("Barcode2 Close\n");

	return TRUE;
}

BOOL CEOL_R7::STEP_CONNECT_POWER()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("��ǰ�� ������Ű�� ���� �� �Ŀ�\r\n���� ��ư�� ��������"), UPDATE_ON);
	
	BOOL bResult = FALSE;

	// Power Off
	pIoBoard->PutOutBit(_BIT_OUT_POWER, false);
	Sleep(500);
	// Silinder Disenable
	pIoBoard->PutOutBit(_BIT_OUT_SILINDER_EN, false);
	// Init Test Settings
	pIoBoard->PutOutBit(_BIT_OUT_LED_Y_POWER, false);
	pIoBoard->PutOutBit(_BIT_OUT_LED_G_OK, false);
	pIoBoard->PutOutBit(_BIT_OUT_LED_R_NG, false);

	// Silinder Enable
	pIoBoard->PutOutBit(_BIT_OUT_SILINDER_EN, false);
	Sleep(200);
	pIoBoard->PutOutBit(_BIT_OUT_SILINDER_EN, true);
	while ( m_tThreadStop == false )
	{
		// ���� �Ϸ� ��ȣ HIGH
		if ((pIoBoard->GetInPort() & _PIN_IN_CONNECT) == 1)
        {
			bResult = TRUE;
            break;
        }
	}

	// Power On
	Sleep(200);
	pIoBoard->PutOutBit(_BIT_OUT_POWER, true);
	pIoBoard->PutOutBit(_BIT_OUT_LED_Y_POWER, true);

	return bResult;
}


BOOL CEOL_R7::STEP_DISCONNECT_POWER()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("������ ���� �մϴ�"), UPDATE_ON);

	BOOL bResult = FALSE;

	// Power Off
	pIoBoard->PutOutBit(_BIT_OUT_POWER, false);
	Sleep(500);
	// Silinder Disenable
	pIoBoard->PutOutBit(_BIT_OUT_SILINDER_EN, false);
	// Init Test Settings
	pIoBoard->PutOutBit(_BIT_OUT_LED_Y_POWER, false);
	pIoBoard->PutOutBit(_BIT_OUT_LED_G_OK, false);
	pIoBoard->PutOutBit(_BIT_OUT_LED_R_NG, false);

	bResult = TRUE;

	return bResult;
}


BOOL CEOL_R7::STEP_CONNECT_USART()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("��� ���� Ȯ��"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->CALIBRATION);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("��� ���� Ȯ��");
	CString strTgtMsg = _T("1");
	CString strSrcMsg = _T("0");
	int nListPos;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.AutoOpenCom() == TRUE )
		{
			dp("R7 JTP Comm Success\n");
			strSrcMsg = _T("1");
			bResult = TRUE;
			break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			dp("R7 JTP Comm Failed\n");
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);

	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	return bResult;
}

BOOL CEOL_R7::STEP_CHK_SERIAL()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("�ø��� ��ȣ Ȯ��"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->CALIBRATION);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("�ø��� ��ȣ");
	CString strTgtMsg = _T("-");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	CFG_SETUP_R7 *oCFG_Setup;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	strSerialNum = _T("");
	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_UserCfgGet(arbRxData, &nRxLength) == TRUE )
		{
			oCFG_Setup = new CFG_SETUP_R7;
			memcpy(oCFG_Setup, arbRxData, nRxLength);

			strSrcMsg.Format(_T("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"),
				oCFG_Setup->arbDeviceSerial[0],
				oCFG_Setup->arbDeviceSerial[1],
				oCFG_Setup->arbDeviceSerial[2],
				oCFG_Setup->arbDeviceSerial[3],
				oCFG_Setup->arbDeviceSerial[4],
				oCFG_Setup->arbDeviceSerial[5],
				oCFG_Setup->arbDeviceSerial[6],
				oCFG_Setup->arbDeviceSerial[7],
				oCFG_Setup->arbDeviceSerial[8],
				oCFG_Setup->arbDeviceSerial[9],
				oCFG_Setup->arbDeviceSerial[10],
				oCFG_Setup->arbDeviceSerial[11],
				oCFG_Setup->arbDeviceSerial[12],
				oCFG_Setup->arbDeviceSerial[13],
				oCFG_Setup->arbDeviceSerial[14],
				oCFG_Setup->arbDeviceSerial[15]);
			strSerialNum = strSrcMsg;
			delete oCFG_Setup;
			oCFG_Setup = NULL;
			bResult = TRUE;
			break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	return bResult;
}


BOOL CEOL_R7::STEP_CHK_SW_VERSION()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("SW ���� Ȯ��"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->CALIBRATION);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("SW ����");
	CString strTgtMsg = pMainDlg->strSwVer;
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	SYSTEM_VERSION *oSYSTEM_VERSION;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_DevInfoGet(arbRxData, &nRxLength) == TRUE )
		{
			oSYSTEM_VERSION = new SYSTEM_VERSION;
			memcpy(oSYSTEM_VERSION, arbRxData, nRxLength);

			strSrcMsg.Format(_T("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"),
					oSYSTEM_VERSION->szFirmwareVer[0],
					oSYSTEM_VERSION->szFirmwareVer[1],
					oSYSTEM_VERSION->szFirmwareVer[2],
					oSYSTEM_VERSION->szFirmwareVer[3],
					oSYSTEM_VERSION->szFirmwareVer[4],
					oSYSTEM_VERSION->szFirmwareVer[5],
					oSYSTEM_VERSION->szFirmwareVer[6],
					oSYSTEM_VERSION->szFirmwareVer[7],
					oSYSTEM_VERSION->szFirmwareVer[8],
					oSYSTEM_VERSION->szFirmwareVer[9],
					oSYSTEM_VERSION->szFirmwareVer[10],
					oSYSTEM_VERSION->szFirmwareVer[11],
					oSYSTEM_VERSION->szFirmwareVer[12],
					oSYSTEM_VERSION->szFirmwareVer[13],
					oSYSTEM_VERSION->szFirmwareVer[14],
					oSYSTEM_VERSION->szFirmwareVer[15]);
			delete oSYSTEM_VERSION;
			oSYSTEM_VERSION = NULL;

			if ( strSrcMsg.Compare(strTgtMsg) == 0 )
			{
				bResult = TRUE;
			}
			break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	return bResult;
}

BOOL CEOL_R7::STEP_CHK_MCU_VERSION()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("MCU ���� Ȯ��"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->CALIBRATION);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("MCU ����");
	CString strTgtMsg = pMainDlg->strMcuVer;
	CString strSrcMsg = _T("0");
	int nListPos;
	BYTE arbRxData[256];

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_GetMAVersion(1, &arbRxData) == TRUE )
		{
			strSrcMsg.Format(_T("%c%d%d%d"),
				arbRxData[0],  arbRxData[1],  arbRxData[2],  arbRxData[3]);

			if ( strSrcMsg.Compare(strTgtMsg) == 0 )
			{
				bResult = TRUE;
			}
			break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	return bResult;
}

BOOL CEOL_R7::STEP_CHK_VANISH()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("���ӵ� ���� �� Ȯ��"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->CALIBRATION);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("���ӵ� ���ð�");
	CString strTgtMsg = _T("Acc X, Acc Z");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	CFG_SETUP_R7 *oCFG_Setup;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_UserCfgGet(arbRxData, &nRxLength) == TRUE )
		{
			oCFG_Setup = new CFG_SETUP_R7;
			memcpy(oCFG_Setup, arbRxData, nRxLength);
						
			if ( oCFG_Setup->bAccSavedState == 1 )
			{
				strSrcMsg.Format(_T("%d, %d"), arbRxData[0],  arbRxData[1]);
				bResult = TRUE;
			}
			else
			{
				strSrcMsg = _T("No Saved");
			}

			delete oCFG_Setup;
			oCFG_Setup = NULL;
			break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	return bResult;
}

BOOL CEOL_R7::STEP_CHK_SPEED_PULSE()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("�ӵ� �޽� ���� �� Ȯ��"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->CALIBRATION);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("�ӵ��޽� ���ð�");
	CString strTgtMsg = _T("-");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	CFG_SETUP_R7 *oCFG_Setup;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_UserCfgGet(arbRxData, &nRxLength) == TRUE )
		{
			oCFG_Setup = new CFG_SETUP_R7;
			memcpy(oCFG_Setup, arbRxData, nRxLength);

			strSrcMsg.Format(_T("%d"), oCFG_Setup->uIOSpeedPulse );
			
			if ( oCFG_Setup->uIOSpeedPulse != 0 )
			{
				bResult = TRUE;
			}

			delete oCFG_Setup;
			oCFG_Setup = NULL;
			
			break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	return bResult;
}



BOOL CEOL_R7::DISPLAY_ADAS_INFO(void *a_pAdasInfoData, int a_puDataLen)
{
	CString strInSpeed;
	HUB_INFO *oOutput_COMM;
	oOutput_COMM = new HUB_INFO;
	memcpy(oOutput_COMM, a_pAdasInfoData, a_puDataLen);

	// �Է¼ӵ� ǥ��
	strInSpeed.Format(_T("%d"), m_nVehicleSpeed);
	pMainDlg->m_edit_in_speed.SetText(SOFT_BLUE, GREY_ROAD, strInSpeed, UPDATE_ON);
	// �Է¹������õ�L ǥ��
	if ( m_bWinkL == 0 )
	{
		pMainDlg->m_edit_in_wink_l.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);
	}
	else
	{
		pMainDlg->m_edit_in_wink_l.SetText(SOFT_BLUE, GREY_ROAD, _T("1"), UPDATE_ON);
	}
	// �Է¹������õ�R ǥ��
	if ( m_bWinkR == 0 )
	{
		pMainDlg->m_edit_in_wink_r.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);
	}
	else
	{
		pMainDlg->m_edit_in_wink_r.SetText(SOFT_BLUE, GREY_ROAD, _T("1"), UPDATE_ON);
	}


	// �����ν� ǥ��
	if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_DETECT) != 0 )
	{
		pMainDlg->m_edit_out_ldw_detetc_l.SetText(SOFT_BLUE, GREY_ROAD, _T("1"), UPDATE_ON);
		pMainDlg->m_edit_out_m_ldw_detect_r.SetText(SOFT_BLUE, GREY_ROAD, _T("1"), UPDATE_ON);
	}
	else
	{
		pMainDlg->m_edit_out_ldw_detetc_l.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);
		pMainDlg->m_edit_out_m_ldw_detect_r.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);
	}
	// �����溸L ǥ��
	if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_LEFT_WARN) != 0 )
	{
		pMainDlg->m_edit_out_ldw_warn_l.SetText(SOFT_BLUE, GREY_ROAD, _T("1"), UPDATE_ON);
	}
	else
	{
		pMainDlg->m_edit_out_ldw_warn_l.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);
	}
	// �����溸R ǥ��
	if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_RIGHT_WARN) != 0 )
	{
		pMainDlg->m_edit_out_ldw_warn_r.SetText(SOFT_BLUE, GREY_ROAD, _T("1"), UPDATE_ON);
	}
	else
	{
		pMainDlg->m_edit_out_ldw_warn_r.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);
	}
	// HMW�溸 ǥ��
	if ( (oOutput_COMM->uFcwState & ADAS_FCW_HMW_WARN) != 0 )
	{
		pMainDlg->m_edit_out_hmw.SetText(SOFT_BLUE, GREY_ROAD, _T("1"), UPDATE_ON);
	}
	else
	{
		pMainDlg->m_edit_out_hmw.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);
	}
	// FCW�溸 ǥ��
	if ( (oOutput_COMM->uFcwState & ADAS_FCW_HMW_WARN) != 0 )
	{
		pMainDlg->m_edit_out_fcw.SetText(SOFT_BLUE, GREY_ROAD, _T("1"), UPDATE_ON);
	}
	else
	{
		pMainDlg->m_edit_out_fcw.SetText(SOFT_BLUE, GREY_ROAD, _T("0"), UPDATE_ON);	
	}
	delete oOutput_COMM;
	oOutput_COMM = NULL;

	return true;
}



BOOL CEOL_R7::STEP_ADAS_LDW_DETECT()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("LDWS ���� �ν�"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("LDWS �����ν�");
	CString strTgtMsg = _T("1");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_LDW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleLdwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 0;
	m_bWinkR = 0;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_DETECT) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->bLaneDetectState & ADAS_LANE_DETECT );
				bResult = TRUE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == TRUE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_LDW_LEFT_WARN()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("LDWS ���� ��Ż �溸"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_WARN_L);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("LDWS ������Ż�溸");
	CString strTgtMsg = _T("4");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_LDW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleLdwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 0;
	m_bWinkR = 0;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_LEFT_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->bLaneDetectState & ADAS_LANE_LEFT_WARN );
				bResult = TRUE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == TRUE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_LDW_RIGHT_WARN()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("LDWS ���� ��Ż �溸"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_WARN_R);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("LDWS ������Ż�溸");
	CString strTgtMsg = _T("8");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_LDW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleLdwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 0;
	m_bWinkR = 0;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_RIGHT_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->bLaneDetectState & ADAS_LANE_RIGHT_WARN );
				bResult = TRUE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == TRUE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_LDW_LEFT_WARN_WINK_L()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("LDWS ���� ��Ż �溸\r\n�������õ�(��)"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_WARN_L);

	BOOL bResult = TRUE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("LDWS ��Ż(L)�������õ�(L)");
	CString strTgtMsg = _T("0");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_LDW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleLdwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 1;
	m_bWinkR = 0;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_LEFT_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->bLaneDetectState & ADAS_LANE_LEFT_WARN );
				bResult = FALSE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == FALSE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_LDW_LEFT_WARN_WINK_R()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("LDWS ���� ��Ż �溸\r\n�������õ�(��)"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_WARN_L);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("LDWS ��Ż(L)�������õ�(R)");
	CString strTgtMsg = _T("4");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_LDW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleLdwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 0;
	m_bWinkR = 1;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_LEFT_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->bLaneDetectState & ADAS_LANE_LEFT_WARN );
				bResult = TRUE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == TRUE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_LDW_LEFT_WARN_WINK_LR()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("LDWS ���� ��Ż �溸\r\n���������"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_WARN_L);

	BOOL bResult = TRUE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("LDWS ��Ż(L)���������");
	CString strTgtMsg = _T("0");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_LDW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleLdwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 1;
	m_bWinkR = 1;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_LEFT_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->bLaneDetectState & ADAS_LANE_LEFT_WARN );
				bResult = FALSE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == FALSE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_LDW_RIGHT_WARN_WINK_L()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("LDWS ���� ��Ż �溸\r\n�������õ�(��)"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_WARN_R);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("LDWS ��Ż(R)�������õ�(L)");
	CString strTgtMsg = _T("8");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_LDW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleLdwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 1;
	m_bWinkR = 0;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_RIGHT_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->bLaneDetectState & ADAS_LANE_RIGHT_WARN );
				bResult = TRUE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == TRUE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_LDW_RIGHT_WARN_WINK_R()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("LDWS ���� ��Ż �溸\r\n�������õ�(��)"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_WARN_R);

	BOOL bResult = TRUE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("LDWS ��Ż(R)�������õ�(R)");
	CString strTgtMsg = _T("0");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_LDW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleLdwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 0;
	m_bWinkR = 1;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_RIGHT_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->bLaneDetectState & ADAS_LANE_RIGHT_WARN );
				bResult = FALSE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == FALSE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_LDW_RIGHT_WARN_WINK_LR()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("LDWS ���� ��Ż �溸\r\n���������"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_WARN_R);

	BOOL bResult = TRUE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("LDWS ��Ż(R)���������");
	CString strTgtMsg = _T("0");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_LDW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleLdwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 1;
	m_bWinkR = 1;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->bLaneDetectState & ADAS_LANE_RIGHT_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->bLaneDetectState & ADAS_LANE_RIGHT_WARN );
				bResult = FALSE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == FALSE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_FCDA_WARN()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("FCDA �˶� �溸"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->FCDA_CAR_DETECT);
	Sleep(1000);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->FCDA_CAR_WARN);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("FCDA �˶��溸");
	CString strTgtMsg = _T("256");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	m_nVehicleSpeed = 0;
	m_bWinkL = 0;
	m_bWinkR = 0;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->uFcwState & ADAS_FCDA_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->uFcwState & ADAS_FCDA_WARN );
				bResult = TRUE;
			}			

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == TRUE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_ADAS_FCW_WARN()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("FCW ���� �溸"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->FCW_CAR_DETECT);
	Sleep(1000);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->FCW_CAR_WARN);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("FCW �����溸");
	CString strTgtMsg = _T("2,8");
	CString strSrcMsg = _T("0");
	int nListPos;
	int nRxLength;
	BYTE arbRxData[256];
	HUB_INFO *oOutput_COMM;

	// ADAS �Է� ������
	( pMainDlg->bEnStep_FCW_Speed == 1 )? (m_nVehicleSpeed = pMainDlg->m_nVehicleFcwSpd) : (m_nVehicleSpeed = 100);
	m_bWinkL = 0;
	m_bWinkR = 0;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_ADASInfoGet_R7(arbRxData, &nRxLength, m_nVehicleSpeed, m_bWinkL, m_bWinkR) == TRUE )
		{
			DISPLAY_ADAS_INFO(arbRxData, nRxLength);

			oOutput_COMM = new HUB_INFO;
			memcpy(oOutput_COMM, arbRxData, nRxLength);

			if ( (oOutput_COMM->uFcwState & ADAS_FCW_HMW_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->uFcwState & ADAS_FCW_HMW_WARN );
				bResult = TRUE;
			}
			else if ( (oOutput_COMM->uFcwState & ADAS_FCW_HMW_WARN) != 0 )
			{
				strSrcMsg.Format(_T("%d"), oOutput_COMM->uFcwState & ADAS_FCW_FCW_WARN );
				bResult = TRUE;
			}

			delete oOutput_COMM;
			oOutput_COMM = NULL;

			if ( bResult == TRUE ) break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->LDW_DETECT);
	return bResult;
}

BOOL CEOL_R7::STEP_DTC_ALL_CLEAR()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("DTC ALL CLEAR"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->CALIBRATION);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("DTC ALL CLEAR");
	CString strTgtMsg = _T("1");
	CString strSrcMsg = _T("0");
	int nListPos;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	while ( m_tThreadStop == false )
	{
		if ( m_JTP_Com.SendMsg_GetDTCData(4, 0, NULL, NULL) == TRUE )
		{
			bResult = TRUE;
			break;
		}

		// 5�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 5000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	return bResult;
}

BOOL CEOL_R7::STEP_CHECK_BARCODE2_SERIAL()
{
	pMainDlg->m_edit_notice.SetText(SOFT_GREEN, BLACK, _T("���̽� ���ڵ� Ȯ��"), UPDATE_ON);
	pMainDlg->pImgDlg->ImgSet(pMainDlg->pImgDlg->CALIBRATION);

	BOOL bResult = FALSE;
	int nStartTime = GetTickCount();
	CString strTestItem = _T("���̽� ���ڵ�");
	CString strTgtMsg = _T("-");
	CString strSrcMsg = _T("0");
	int nListPos;
	int preBarcodeCount;

	nListPos = pMainDlg->m_list_test_process.GetItemCount();
	pMainDlg->m_list_test_process.InsertItem(nListPos, strTestItem);
	pMainDlg->m_list_test_process.SetItemText(nListPos, 1, strTgtMsg);

	preBarcodeCount = pBarCode2->GetCount();
	while ( m_tThreadStop == false )
	{
		pIoBoard->PutOutBit(_BIT_OUT_BARCODE2, true);
		if ( pBarCode2->GetCount() > preBarcodeCount)
		{
			strSrcMsg = (LPCSTR)pBarCode2->GetDataAt(preBarcodeCount-1);

			if ( strSrcMsg.Compare(strSerialNum) == 0 )
			{
				bResult = TRUE;
			}
			break;
		}

		// 20�ʰ� ������ ���� ������ Fail
		if ( (GetTickCount() - nStartTime) > 20000 )
		{
			strSrcMsg = _T("Comm Error");
			break;
		}
	}

	pMainDlg->m_list_test_process.SetItemText(nListPos, 2, strSrcMsg);
	
	if ( bResult == TRUE )
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("PASS"));
	}
	else
	{
		pMainDlg->m_list_test_process.SetItemText(nListPos, 3, _T("FAIL"));
	}

	return bResult;
}