// IoBoardMgt.cpp: implementation of the CIoBoardMgt class.
//
//////////////////////////////////////////////////////////////////////
//  KM 6050 Test Result: KM 6050�� 7���� Digital Inputs, 8���� Digital Output ��Ʈ�� �����Ǿ� �ִ�.
//      Send:?ID
//      Rcv :
//      1.ID 01                 <- ��ġ ��ȣ�� 1���̴�.
//      2.Model KM 6050         <- ���� KM 6050�̴�.
//      3.wR/W 0010,1010,2010   <- ���� ������ �б�/���Ⱑ ������ �޸𸮴� 0x00���� 16��, 0x10���� 16��, 0x20���� 16��
//      4.wR// 8010,9010,A010   <- ���� ������ �б⸸      ������ �޸𸮴� 0x80���� 16��, 0x90���� 16��, 0xA0���� 16��
//      5.bR/W 0010             <- ��Ʈ ������ �б�/���Ⱑ ������ �޸𸮴� 0x00���� 16��
//      6.bR// 8010             <- ���� ������ �б⸸      ������ �޸𸮴� 0x80���� 16��
//
//      Send:$01P8007           <- 01�� ��ġ�� 0x80�������� 7���� �����͸� �о��.
//      Rcv :!01P8007,0111111   <- Lo(DI0),Hi(DI1),Hi(DI2),Hi(DI3),Hi(DI4),Hi(DI5),Hi(DI6)
//      Send:$01A0008,1-------  <- 01�� ��ġ�� 0x00�������� 8���� �����͸� �����Ѵ�. ('1'=Hi, '0'=Lo, '-'=No Change)
//      Rcv :!01A0008,1-------  <- �״�� ���丸 �Ѵ�.
//      Send:$01P0008           <- 01�� ��ġ�� 0x00�������� 8���� �����͸� �о��.
//      Rcv :!01P0008,10000000  <- Hi(DO0),Lo(DO1),Lo(DO2),Lo(DO3),Lo(DO4),Lo(DO5),Lo(DO6),Lo(DO7)
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "y_IoBoardMgt.h"
#include "y_Uart4Pc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIoBoardMgt::CIoBoardMgt()
{
    m_hCom = INVALID_HANDLE_VALUE;

    memset(m_szMsg, 0, sizeof(m_szMsg));

    m_wMsgCnt = 0;
}

CIoBoardMgt::~CIoBoardMgt()
{
    Close();
}

bool CIoBoardMgt::Open(const char *a_pszCom)
{
    Close();

    m_hCom = UartSetup(a_pszCom, 9600);

   if (m_hCom == INVALID_HANDLE_VALUE)
   {
      return false;
   }

   return true;
}

void CIoBoardMgt::Close(void)
{
    if (m_hCom != INVALID_HANDLE_VALUE)
    {
        PurgeComm( m_hCom, PURGE_TXABORT | PURGE_RXABORT |
                           PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
        CloseHandle( m_hCom );

        m_hCom = INVALID_HANDLE_VALUE;
    }
}

char *CIoBoardMgt::GetMsg(void)
{
    return m_szMsg;
}

U32  CIoBoardMgt::GetMsgCnt(void)
{
    return m_wMsgCnt;
}

bool CIoBoardMgt::TransferMsg(const char *a_pszTx)
{
    int nLen;
    U32 wRxWaitTime;
    int iRxCount;

    // Check Error
    if ( (m_hCom == INVALID_HANDLE_VALUE) || (a_pszTx == NULL) )
    {
        return false;
    }

   // Clear Dummy Rx Buffer
   iRxCount = UartRxCount(m_hCom);
   while (iRxCount > 0)
   {
      UartRead(m_hCom, m_szMsg, iRxCount);
      Sleep(100);
      iRxCount = UartRxCount(m_hCom);
   }

   // Transmit Start
    nLen = strlen(a_pszTx);
    UartWrite(m_hCom, a_pszTx, nLen);

   // Wait Rx Start
    wRxWaitTime = GetTickCount() + 500;

    while ( UartRxCount(m_hCom) == 0 )
    {
        Sleep(50);
        if ( GetTickCount() >  wRxWaitTime )
        {
            return false;
        }
    }

    // Receive Rx
    nLen = UartRxCount(m_hCom);
    UartRead(m_hCom, m_szMsg, nLen);

    while (true)
    {
        Sleep(50);

        iRxCount = UartRxCount(m_hCom);
        if (iRxCount == 0)
        {
            m_szMsg[nLen] = 0;
            while (nLen > 0)
            {
                if ( (m_szMsg[nLen-1] == '\r') || (m_szMsg[nLen-1] == '\n') )
                {
                    nLen--;
                    m_szMsg[nLen] = 0;
                }
                else
                {
                    break;
                }
            }

            m_wMsgCnt++;
            break;
        }
        else
        {
            UartRead(m_hCom, &m_szMsg[nLen], iRxCount);
            nLen += iRxCount;
        }
    }

    return true;
}

U16  CIoBoardMgt::GetInPort(void)
{
//      Send:$01P8007           <- 01�� ��ġ�� 0x80�������� 7���� �����͸� �о��.
//      Rcv :!01P8007,0111111   <- Lo(DI0),Hi(DI1),Hi(DI2),Hi(DI3),Hi(DI4),Hi(DI5),Hi(DI6)
    char*pszRx;
    U16 uRtnData, uBitData, i;
   
	//01�� ��ġ�� 0x80�������� 16���� �����͸� �о��.
    if (TransferMsg("$01P8010\r") == false)
    {
        return 0xFFFF;  // error return
    }
    
    pszRx = GetMsg();
    pszRx = strchr(pszRx, ',');
    if (pszRx == NULL)
    {
        return 0xFFFF;
    }

    pszRx++;
    uRtnData = 0;
    uBitData = 0x0001;
  
     
    //for (i = 0; i < 7; i++)
    for (i = 0; i < 15; i++)
    {
        if (pszRx[i] == '1')
        {
            uRtnData |= uBitData;
        }
        uBitData <<= 1;
    }

    return uRtnData;
}

U16  CIoBoardMgt::GetOutPort(void)
{
//      Send:$01P0008           <- 01�� ��ġ�� 0x00�������� 8���� �����͸� �о��.
//      Rcv :!01P0008,10000000  <- Hi(DO0),Lo(DO1),Lo(DO2),Lo(DO3),Lo(DO4),Lo(DO5),Lo(DO6),Lo(DO7)
    char*pszRx;
    U16 uRtnData, uBitData, i;
       //kbr
   // if (TransferMsg("$01P0008\r") == false)     
    if (TransferMsg("$01P0010\r") == false)
    {
        return 0xFFFF;  // error return
    }
    
    pszRx = GetMsg();
    pszRx = strchr(pszRx, ',');
    if (pszRx == NULL)
    {
        return 0xFFFF;
    }

    pszRx++;
    uRtnData = 0;
    uBitData = 0x0001;
  
    //kbr
    //for (i = 0; i < 8; i++)
    for (i = 0; i < 16; i++)
    {
        if (pszRx[i] == '1')
        {
            uRtnData |= uBitData;
        }
        uBitData <<= 1;
    }

    return uRtnData;
}

//kbr
U16  CIoBoardMgt::PutOutPort(U16 a_bData)
{
//      Send:$01A0008,1-------  <- 01�� ��ġ�� 0x00�������� 8���� �����͸� �����Ѵ�. ('1'=Hi, '0'=Lo, '-'=No Change)
//      Rcv :!01A0008,1-------  <- �״�� ���丸 �Ѵ�.
    //             012345678901234567
    //char szTx[] = "$01A0008,01234567\r";
    char szTx[] = "$01A0010,01234567--------\r";
    U16 i;

    //for (i = 0; i < 8; i++)
    for (i = 0; i < 16; i++)
    {
        szTx[9+i] = (a_bData & 0x01)? '1': '0';
        a_bData >>= 1;
    }

    if (TransferMsg(szTx) == false)
    {
        return 0xFFFF;  // error return
    }

    return GetOutPort();
}
 
//kbr
U16  CIoBoardMgt::PutOutBit(U16 a_bBitPos, bool a_tHi)
{
    //             012345678901234567
    //kbr
    //char szTx[] = "$01A0008,--------\r";
    char szTx[] = "$01A0010,----------------\r";

    
    //if (a_bBitPos >= 8)
    if (a_bBitPos >= 16)
    {
        return 0xFFFF;
    }

    szTx[9+a_bBitPos] = (a_tHi == false)? '0': '1';

    if (TransferMsg(szTx) == false)
    {
        return 0xFFFF;  // error return
    }

    return GetOutPort();
}
