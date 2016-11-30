#ifndef _CAN_INMSG_H_
#define _CAN_INMSG_H_

#include "JDEFINE.H"
#include "PCANBasicClass.h"

class CCanInMsg
{
public:
    CCanInMsg(U32 a_wID, void (*a_pfUseMsg)(TPCANMsg* a_pCanMsg));
    void UseMsg(void);

    void    (*m_pfUseMsg)(TPCANMsg* a_pCanMsg);
    U32      m_wID;
    TPCANMsg m_CanMsg;
    U32      m_wMsgCnt;
};

#endif // _CAN_INMSG_H_
