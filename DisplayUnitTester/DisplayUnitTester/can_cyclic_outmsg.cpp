#include "StdAfx.h"
#include "can_cyclic_outmsg.h"

CCanCyclicOutMsg::CCanCyclicOutMsg(U32 a_wID, U32 a_wIntervalMsec, void (*a_pfMakeMsg)(TPCANMsg* a_pCanMsg))
{
    m_CanMsg.ID      = a_wID;
    m_CanMsg.MSGTYPE = PCAN_MESSAGE_STANDARD;
    m_CanMsg.LEN     = 8;

    m_wIntervalMsec = a_wIntervalMsec;

    m_pfMakeMsg = a_pfMakeMsg;
    m_wMsgCnt = 0;
}

void CCanCyclicOutMsg::MakeMsg(void)
{
    m_pfMakeMsg(&m_CanMsg);
    m_wMsgCnt++;;
}
