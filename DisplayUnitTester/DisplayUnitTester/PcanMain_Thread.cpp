#include "stdafx.h"
#include "resource.h"
#include "JDEFINE.H"
#include "pcan_inf.h"
#include "PcanDlg.h"
#include "SysCfg.h"

#define PCAN_CYCLE_TIME 100

static CPcan * pCan = NULL;
extern PcanDlg		*pPcanDlg;

TOF tMainThreadStop	= false;

U32 wCanEnable = 0;

static bool OpenCan(void)
{
	//CCanCyclicOutMsg *pCyclicOutMsg;
    //CCanInMsg        *pInMsg;

	pCan = new CPcan;
	if (pCan == NULL)
    {
        return false;
    }

	if (pCan->Open() == false)
    {
        return false;
    }

    if (pCan->Connect(500) == false)
    {
        return false;
    }
#if 0
	pCyclicOutMsg = new CCanCyclicOutMsg(_IN_CAN_SIG1, 10, MakeMsg_MESSAGE1);
    pCan->AddCyclicOutMsg(pCyclicOutMsg);

	pCyclicOutMsg = new CCanCyclicOutMsg(_IN_CAN_SIG2, 100, MakeMsg_MESSAGE2);
    pCan->AddCyclicOutMsg(pCyclicOutMsg);

	pCyclicOutMsg = new CCanCyclicOutMsg(_IN_CAN_SIG3, 200, MakeMsg_MESSAGE3);
    pCan->AddCyclicOutMsg(pCyclicOutMsg);

	pCyclicOutMsg = new CCanCyclicOutMsg(_IN_CAN_SIG4, 50, MakeMsg_MESSAGE4);
    pCan->AddCyclicOutMsg(pCyclicOutMsg);

	pCyclicOutMsg = new CCanCyclicOutMsg(_IN_CAN_SIG5, 200, MakeMsg_MESSAGE5);
    pCan->AddCyclicOutMsg(pCyclicOutMsg);

	pCyclicOutMsg = new CCanCyclicOutMsg(_IN_CAN_SIG6, 500, MakeMsg_MESSAGE6);
    pCan->AddCyclicOutMsg(pCyclicOutMsg);

	pCyclicOutMsg = new CCanCyclicOutMsg(_IN_CAN_SIG7, 1000, MakeMsg_MESSAGE7);
    pCan->AddCyclicOutMsg(pCyclicOutMsg);

	pInMsg = new CCanInMsg(_OUT_CAN_STATUS, UseMsg_ADASSTATUS);
    pCan->AddInMsg(pInMsg);

	//pInMsg = new CCanInMsg(_OUT_CAN_LANE, UseMsg_ADASLANE);
    //pCan->AddInMsg(pInMsg);

	pInMsg = new CCanInMsg(_OUT_CAN_CIPV, UseMsg_ADASCIPV);
    pCan->AddInMsg(pInMsg);

	//pInMsg = new CCanInMsg(_OUT_CAN_LANE_C, UseMsg_ADASLANECONF);
    //pCan->AddInMsg(pInMsg);

	//pInMsg = new CCanInMsg(_OUT_CAN_CIPV_C, UseMsg_ADASCIPVCONF);
    //pCan->AddInMsg(pInMsg);

	//pInMsg = new CCanInMsg(_OUT_CAN_SIGN, UseMsg_ADASSIGN);
    //pCan->AddInMsg(pInMsg);

	//pInMsg = new CCanInMsg(_OUT_CAN_OBJECT, UseMsg_ADASOBJECT);
    //pCan->AddInMsg(pInMsg);

	//pInMsg = new CCanInMsg(_OUT_CAN_OBJECT_C, UseMsg_ADASOBJECTCONF);
    //pCan->AddInMsg(pInMsg);

	pInMsg = new CCanInMsg(_CAN_ID_DTC_ECU, UseMsg_DTC);
    pCan->AddInMsg(pInMsg);
#endif
	// Run Thread
    pCan->Thread_Begin();

	return true;
}

static void CloseCan(void)
{
	pCan->Close();


	pPcanDlg->SetDlgItemTextW(IDC_CHECK_CAN_START, _T("CAN START"));
	if ( pPcanDlg->m_check_can_start == 1 )
	{
		pPcanDlg->m_check_can_start ^= 1;
		pPcanDlg->UpdateData(false);
	}
}

UINT PcanMainThread(LPVOID pParam)
{
	bool tCriticalError = false;
	S16 nInMsgIdx;
	int nListPos;
	CString strItem;
	unsigned int preMsgCnt[16], curMsgCnt[16], flag1s = 0;

	// Init CAN
    if (tCriticalError == false)
    {
		if (OpenCan() == true)
        {
            printf(("CAN Initialize OK\n"));
			
        }
        else
        {
            AfxMessageBox(_T("CAN Initialize Error!(PCANBasic.dll)"));
            printf(("CAN Initialize Error\n"));
            tCriticalError = true;

        }
    }
	
	Sleep(1000);
	while( (tCriticalError == false) && (tMainThreadStop == false) )
	{
		for (nInMsgIdx = 0; nInMsgIdx < (pCan->m_pub_nInMsg); nInMsgIdx++)
		{
			nListPos = nInMsgIdx;
			strItem.Format(_T("%04X"),pCan->m_pub_arpInMsg[nInMsgIdx]->m_wID);
			pPcanDlg->m_list_pcan.SetItemText(nListPos, 1, strItem);

			strItem.Format(_T("%d"), pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.LEN);
			pPcanDlg->m_list_pcan.SetItemText(nListPos, 2, strItem);

			strItem.Format(_T("%X"), pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.MSGTYPE);
			pPcanDlg->m_list_pcan.SetItemText(nListPos, 3, strItem);

			strItem.Format(_T("%02X %02X %02X %02X %02X %02X %02X %02X"), pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.DATA[0],
																	pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.DATA[1],
																	pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.DATA[2],
																	pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.DATA[3],
																	pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.DATA[4],
																	pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.DATA[5],
																	pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.DATA[6],
																	pCan->m_pub_arpInMsg[nInMsgIdx]->m_CanMsg.DATA[7] );
			pPcanDlg->m_list_pcan.SetItemText(nListPos, 4, strItem);
			
			if ( flag1s >= 1000 )
			{
				curMsgCnt[nInMsgIdx] = pCan->m_pub_arpInMsg[nInMsgIdx]->m_wMsgCnt;
				if (curMsgCnt[nInMsgIdx] - preMsgCnt[nInMsgIdx] > 0)
				{
					strItem.Format(_T("%d"), flag1s / (curMsgCnt[nInMsgIdx] - preMsgCnt[nInMsgIdx]) );
				}
				else
				{
					strItem.Format(_T("0"));
				}
				preMsgCnt[nInMsgIdx] = curMsgCnt[nInMsgIdx];
				pPcanDlg->m_list_pcan.SetItemText(nListPos, 5, strItem);
			}

			strItem.Format(_T("%d"),pCan->m_pub_arpInMsg[nInMsgIdx]->m_wMsgCnt);
			pPcanDlg->m_list_pcan.SetItemText(nListPos, 6, strItem);
		}
		pPcanDlg->UpdateData(false);
		
		if ( flag1s >= 1000 ) flag1s = 0;
		flag1s += PCAN_CYCLE_TIME;
		Sleep(PCAN_CYCLE_TIME);
	}
	CloseCan();

	return 0;
}