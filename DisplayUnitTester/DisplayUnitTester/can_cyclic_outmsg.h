#ifndef _CAN_CYCLIC_OUTMSG_H_
#define _CAN_CYCLIC_OUTMSG_H_

#include "JDEFINE.H"
#include "PCANBasicClass.h"

class CCanCyclicOutMsg
{
public:
    CCanCyclicOutMsg(U32 a_wID, U32 a_wIntervalMsec, void (*a_pfMakeMsg)(TPCANMsg* a_pCanMsg));
    void MakeMsg(void);

    void    (*m_pfMakeMsg)(TPCANMsg* a_pCanMsg);
    U32      m_wIntervalMsec;
    U32      m_wTimerMsec;
    TPCANMsg m_CanMsg;
    U32      m_wMsgCnt;
};

#endif // _CAN_CYCLIC_OUTMSG_H_
