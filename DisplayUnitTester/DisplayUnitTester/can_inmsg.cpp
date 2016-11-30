#include "StdAfx.h"
#include "can_inmsg.h"

CCanInMsg::CCanInMsg(U32 a_wID, void (*a_pfUseMsg)(TPCANMsg* a_pCanMsg))
{
    m_wID = a_wID;

    m_pfUseMsg = a_pfUseMsg;
    m_wMsgCnt = 0;
}

void CCanInMsg::UseMsg(void)
{
    m_pfUseMsg(&m_CanMsg);
    m_wMsgCnt++;
}
