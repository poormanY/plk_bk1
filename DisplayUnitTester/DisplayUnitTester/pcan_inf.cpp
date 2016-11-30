#include "StdAfx.h"
#include "pcan_inf.h"

//psj cycle set
#include <mmsystem.h>
//psj cycle set
#pragma comment(lib, "winmm")

#define dprintf(a) printf a

extern U32	wCanEnable;

CPcan::CPcan()
{
    U16 i;

    m_tConnected = false;
    m_wError = PCAN_ERROR_OK;
    m_bPCAN_Handle = PCAN_USBBUS1;
    m_pCAN = NULL;

    m_nCyclicOutMsg = 0;;
    for (i = 0; i < _PCAN_CYCLIC_OUTMSG_MAX; i++)
    {
        m_arpCyclicOutMsg[i] = NULL;
    }

    m_nInMsg = 0;
    for (i = 0; i < _PCAN_INMSG_MAX; i++)
    {
        m_arpInMsg[i] = NULL;
    }

    m_tThreadStop = false;
    m_pThreadCanReadMsg = NULL;
    m_pThreadCanCyclicOutMsg = NULL;
}

CPcan::~CPcan()
{
    Thread_End();
    Close();
}

TOF CPcan::Open(void)
{
    if (m_pCAN != NULL)
    {
        Close();
    }

    m_pCAN = new PCANBasicClass();

    if (m_pCAN == NULL)
    {
        dprintf(("CAN DLL Load Error!\n"));
        return false;
    }
    else
    {
        dprintf(("CAN DLL Load Success!\n"));
        return true;
    }
}

void CPcan::Close(void)
{
    U16 i;

    Thread_End();

    for (i = 0; i < m_nCyclicOutMsg; i++)
    {
        if (m_arpCyclicOutMsg[i] != NULL)
        {
            delete m_arpCyclicOutMsg[i];
            m_arpCyclicOutMsg[i] = NULL;
        }
    }
    m_nCyclicOutMsg = 0;

    for (i = 0; i < m_nInMsg; i++)
    {
        if (m_arpInMsg[i] != NULL)
        {
            delete m_arpInMsg[i];
            m_arpInMsg[i] = NULL;
        }
    }
    m_nInMsg = 0;

    if (m_pCAN != NULL)
    {
        if (m_tConnected == true)
        {
            Disconnect();
        }
        delete m_pCAN;
        m_pCAN = NULL;
    }
}

TOF CPcan::Connect(U16 a_uKBps)
{
    S32 lBuffer;
    U32 wReturn;

    wReturn = m_pCAN->GetValue(m_bPCAN_Handle, PCAN_CHANNEL_CONDITION, (void*)&lBuffer, sizeof(lBuffer));
    if ( (wReturn == PCAN_ERROR_OK) && (lBuffer == PCAN_CHANNEL_AVAILABLE) )
    {
        switch (a_uKBps)
        {
        case  250: m_uBpsCode = 0x011C; break;
        case  500: m_uBpsCode = 0x001C; break;
        case 1000: m_uBpsCode = 0x0014; break;
        default: return false;
        };

        wReturn = m_pCAN->Initialize(m_bPCAN_Handle, m_uBpsCode, 0, 0, 0);
        if (wReturn == PCAN_ERROR_OK)
        {
            m_tConnected = true;
            m_wError = PCAN_ERROR_OK;
            dprintf(("CAN Connected!\n"));
            return true;
        }
    }

    dprintf(("CAN is NOT Connected!\n"));
    return false;
}

void CPcan::Disconnect(void)
{
    Thread_End();

    m_tConnected = false;
    m_pCAN->Uninitialize(m_bPCAN_Handle);
}

TOF CPcan::Read(TPCANMsg *a_pCANMsg)
{
    U32 wCANStatus;
    TPCANTimestamp oCANTimeStamp;
    //char szBuff[128];
	char szBuff[128];

	memset(szBuff, 0x00, sizeof(char)*128);

    wCANStatus = m_pCAN->Read(m_bPCAN_Handle, a_pCANMsg, &oCANTimeStamp);
    if (wCANStatus == PCAN_ERROR_OK)	
    {
        return true;
    }
    else
    {
        if (wCANStatus != PCAN_ERROR_QRCVEMPTY)
        {
            m_wError = wCANStatus;
            m_pCAN->GetErrorText(wCANStatus, 0x09, szBuff);
            dprintf(("Read Error: %s\n", szBuff));

            Reset(); // PSJ CHECK
        }

        return false;
    }
}

TOF CPcan::Write(TPCANMsg *a_pCANMsg)
{
    U32 wCANStatus;

    wCANStatus = m_pCAN->Write(m_bPCAN_Handle, a_pCANMsg);

    if (wCANStatus == PCAN_ERROR_OK)
    {
        return true;
    }
    else
    {
        m_wError = wCANStatus;
        return false;
    }
}

TOF CPcan::Reset(void)
{
    int nTry = 0;

    U32 wCANStatus;
    
    while (true)
    {
        m_pCAN->Uninitialize(m_bPCAN_Handle);
        Sleep(100);
        wCANStatus = m_pCAN->Initialize(m_bPCAN_Handle, m_uBpsCode, 0, 0, 0);
        
        if (wCANStatus == PCAN_ERROR_OK)
        {
            return true;
        }
        else
        {
            nTry++;
            if (nTry > 10)
            {
                m_wError = wCANStatus;
                return false;
            }
            Sleep(100);
        }
    }
}

TOF  CPcan::SetCycle(U16 a_uCycle, U08 a_uIndex)
{
	m_arpCyclicOutMsg[a_uIndex]->m_wIntervalMsec = a_uCycle;

	return true;
}

TOF  CPcan::AddCyclicOutMsg(CCanCyclicOutMsg *a_pCCanCyclicOutMsg)
{
    if (a_pCCanCyclicOutMsg == NULL)
    {
        return false;
    }

    if (m_nCyclicOutMsg >= _PCAN_CYCLIC_OUTMSG_MAX)
    {
        return false;
    }

    m_arpCyclicOutMsg[m_nCyclicOutMsg] = a_pCCanCyclicOutMsg;
    m_arpCyclicOutMsg[m_nCyclicOutMsg]->m_wTimerMsec = timeGetTime();
    m_nCyclicOutMsg++;

    return true;
}

TOF  CPcan::AddInMsg(CCanInMsg *a_pCanInMsg)
{
    if (a_pCanInMsg == NULL)
    {
        return false;
    }

    if (m_nInMsg >= _PCAN_INMSG_MAX)
    {
        return false;
    }

    m_arpInMsg[m_nInMsg] = a_pCanInMsg;
    m_nInMsg++;

    return true;
}

TOF  CPcan::Thread_Begin(void)
{
    Thread_End();

    if (m_tConnected == false)
    {
        return false;
    }

    // New Start Thread
    m_tThreadStop = false;
    m_pThreadCanCyclicOutMsg = AfxBeginThread(PCAN_ThreadCyclicOutMsg, this);
    //m_pThreadCanReadMsg      = AfxBeginThread(PCAN_ThreadReadMsg, this);
	m_pThreadCanReadMsg      = AfxBeginThread(PCAN_ThreadReadMsg_ALL, this);


    if ( (m_pThreadCanCyclicOutMsg == NULL) || (m_pThreadCanReadMsg == NULL) )
    {
        Thread_End();
        return false;
    }

    Reset();
    return true;
}

TOF  CPcan::Thread_End(void)
{
    m_tThreadStop = true;
    if (m_pThreadCanCyclicOutMsg != NULL)
    {
        WaitForSingleObject(m_pThreadCanCyclicOutMsg->m_hThread, INFINITE);
        m_pThreadCanCyclicOutMsg = NULL;
    }
    if (m_pThreadCanReadMsg != NULL)
    {
        WaitForSingleObject(m_pThreadCanReadMsg->m_hThread, INFINITE);
        m_pThreadCanCyclicOutMsg = NULL;
    }

    m_tThreadStop = false;
    return true;
}

#define _PCAN_THREAD_SLEEP_WRITE	1
#define _PCAN_THREAD_SLEEP_READ		1

bool tPCAN_ThreadStop = false;
int  nPCAN_WriteState = _PCAN_THREAD_WRITE_ENABLE;

UINT PCAN_ThreadCyclicOutMsg(LPVOID pParam)
{
    CPcan *pCan = (CPcan *)pParam;

    S16 nIndex;
    U32 wTimerMsec;
    CCanCyclicOutMsg *pCyclicOutMsg;

    while (pCan->m_tThreadStop == false)
    {
        Sleep(_PCAN_THREAD_SLEEP_WRITE);

        if (nPCAN_WriteState == _PCAN_THREAD_WRITE_ENABLE)
        {
            wTimerMsec = timeGetTime();
            for (nIndex = 0; nIndex < pCan->m_nCyclicOutMsg; nIndex++)
            {
                pCyclicOutMsg = pCan->m_arpCyclicOutMsg[nIndex];
				//if ( wTimerMsec > (pCyclicOutMsg->m_wTimerMsec + pCyclicOutMsg->m_wIntervalMsec + 1) )
				if ( wTimerMsec > (pCyclicOutMsg->m_wTimerMsec + pCyclicOutMsg->m_wIntervalMsec) )
                {
					if ( ( wCanEnable >> nIndex ) & 0x01 )
					{
						pCyclicOutMsg->MakeMsg();
						pCan->Write(&pCyclicOutMsg->m_CanMsg);
						pCyclicOutMsg->m_wTimerMsec = wTimerMsec;
					}
                }
            }
		}

        if (nPCAN_WriteState == _PCAN_THREAD_WRITE_DISABLE_REQ)
        {
            nPCAN_WriteState = _PCAN_THREAD_WRITE_DISABLED;
        }
    }

    dprintf(("Cyclic Out Message Thread End\n"));

    return 0;
}

UINT PCAN_ThreadReadMsg(LPVOID pParam)
{
    CPcan *pCan = (CPcan *)pParam;
    TPCANMsg oCANMsg;
    CCanInMsg *pInMsg;
    S16 nInMsgIdx;

    while (pCan->m_tThreadStop == false)
    {
        Sleep(_PCAN_THREAD_SLEEP_READ);

        while (true)
        {
            if (pCan->Read(&oCANMsg) == true)
            {
                for (nInMsgIdx = 0; nInMsgIdx < pCan->m_nInMsg; nInMsgIdx++)
                {
                    pInMsg = pCan->m_arpInMsg[nInMsgIdx];
                    if (oCANMsg.ID == pInMsg->m_wID)
                    {
                        memcpy(&pInMsg->m_CanMsg, &oCANMsg, sizeof(TPCANMsg));
                        pInMsg->UseMsg();
                    }
                }
            }
            else
            {
                break;
            }
        }
    }

    dprintf(("Read Thead End\n"));
    return 0;
}



UINT PCAN_ThreadReadMsg_ALL(LPVOID pParam)
{
    CPcan *pCan = (CPcan *)pParam;
    TPCANMsg oCANMsg;
    CCanInMsg *pInMsg;
	CCanInMsg *pInMsgNew;
    S16 nInMsgIdx;
	BOOL bChkMsgId = false;

    while (pCan->m_tThreadStop == false)
    {
        Sleep(_PCAN_THREAD_SLEEP_READ);

        while (true)
        {
            if (pCan->Read(&oCANMsg) == true)
            {
				bChkMsgId = false;
				if ( pCan->m_nInMsg == 0 )
				{
					pInMsgNew = new CCanInMsg(oCANMsg.ID, 0);
					pCan->AddInMsg(pInMsgNew);
				}

				for (nInMsgIdx = 0; nInMsgIdx < pCan->m_nInMsg; nInMsgIdx++)
                {
					pInMsg = pCan->m_arpInMsg[nInMsgIdx];
					if ( oCANMsg.ID == pInMsg->m_wID )
					{
						pCan->m_pub_nInMsg = pCan->m_nInMsg;
						pCan->m_pub_arpInMsg[nInMsgIdx] = pCan->m_arpInMsg[nInMsgIdx];

						memcpy(&pInMsg->m_CanMsg, &oCANMsg, sizeof(TPCANMsg));
						pCan->m_arpInMsg[nInMsgIdx]->m_wMsgCnt++;
						//memcpy(&pInMsg->m_CanMsg, &oCANMsg, sizeof(TPCANMsg));
						//pInMsg->UseMsg();
						bChkMsgId = true;
						break;
					}
				}

				if ( bChkMsgId == false )
				{
					pInMsgNew = new CCanInMsg(oCANMsg.ID, 0);
					pCan->AddInMsg(pInMsgNew);
				}
            }
            else
            {
                break;
            }
        }
    }

    dprintf(("Read Thead End\n"));
    return 0;
}