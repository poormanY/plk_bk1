#ifndef _PCAN_INF_H_
#define _PCAN_INF_H_

#include "JDEFINE.H"
#include "PCANBasicClass.h"
#include "can_cyclic_outmsg.h"
#include "can_inmsg.h"

#define _PCAN_CYCLIC_OUTMSG_MAX 16
//PSJ
//#define _PCAN_INMSG_MAX          4
#define _PCAN_INMSG_MAX         16

#define _PCAN_THREAD_WRITE_ENABLE       0
#define _PCAN_THREAD_WRITE_DISABLE_REQ  1
#define _PCAN_THREAD_WRITE_DISABLED     2

class CPcan
{
public:
    CPcan();
   ~CPcan();

    TOF  Open(void);
    void Close(void);

    TOF  Connect(U16 a_uKBps);
    void Disconnect(void);

    TOF  IsError(void) {return m_wError != PCAN_ERROR_OK;};
    TOF  Read (TPCANMsg *a_pCANMsg);
    TOF  Write(TPCANMsg *a_pCANMsg);
    TOF  Reset(void);

    // for Read/Write Thread
    TOF  AddCyclicOutMsg(CCanCyclicOutMsg *a_pCCanCyclicOutMsg);
    TOF  AddInMsg(CCanInMsg *a_pCanInMsg);
    
    TOF  Thread_Begin(void);
    TOF  Thread_End(void);

	TOF  SetCycle(U16 a_uCycle, U08 a_uIndex);

	S16 m_pub_nInMsg;
	CCanInMsg *m_pub_arpInMsg[_PCAN_INMSG_MAX];

private:
    TOF             m_tConnected;
    U32             m_wError;
    U08             m_bPCAN_Handle;  // = PCAN_USBBUS1;
    U16             m_uBpsCode;
    PCANBasicClass *m_pCAN;

    // Thread for Cyclic Out Message
    S16 m_nCyclicOutMsg;
    CCanCyclicOutMsg *m_arpCyclicOutMsg[_PCAN_CYCLIC_OUTMSG_MAX];

    // Thread for In Message
    S16 m_nInMsg;
    CCanInMsg *m_arpInMsg[_PCAN_INMSG_MAX];

    // Thread for Run
    TOF m_tThreadStop;
	CWinThread * m_pThreadCanReadMsg;
	CWinThread * m_pThreadCanCyclicOutMsg;

    friend UINT PCAN_ThreadCyclicOutMsg(LPVOID pParam);
    friend UINT PCAN_ThreadReadMsg(LPVOID pParam);
	friend UINT PCAN_ThreadReadMsg_ALL(LPVOID pParam);
};

#endif // _PCAN_INF_H_

