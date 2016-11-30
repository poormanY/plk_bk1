//
// File   : uart_proc.c
// Author : YSW
// Created on 2016년 9월 26일 (월), 오전 9:46
//
// Brief :
// Detail :
//
#include <string.h>
#include "../define.h"
#include "uart_proc.h"
#include "jtp_proc.h"
#include "../peripheral/uart.h"
#include "../app_version.h"

static U08 arbTempBuff[MAX_RCV_BUFFER_LENGTH];       // Hub : Header ~ Footer
static U08 arbRcvBuff[MAX_RCV_BUFFER_LENGTH];

U08 uart_proc(void)
{
    static U16 uJTP_RxRunMode = 0;
    static U16 uJTP_RxBuffIdx = 0;
    
    static TOF tMyFrame = false;
    static U08 arbFrame[sizeof(JTP_FRAME)];
    static U16 uFrameIdxW;

    U08 bRet;
    U16 uTempIdxR;
    U16 uTempIdxW;

    U16 uNeedRxLen;
    U16 uRxLen;

    JTP_FRAME *pFrame;

    bRet = false;
    // Read received data count
    uRxLen = SerialGetCount();
    if ( uRxLen == 0 )
    {
        if ( uJTP_RxRunMode != _RXMGT_NODATA )
        {
            if ( tMyFrame )
            {
                uJTP_RxRunMode = _RXMGT_NODATA;
            }
        }
        return bRet;
    }

    // Read received data
    uTempIdxR = 0;
    uTempIdxW = (uRxLen < sizeof(arbTempBuff)) ? uRxLen : sizeof(arbTempBuff);
    SerialGetByteData(arbTempBuff, uTempIdxW);

    while(true)
    {
        // JTP_FRANE begins with HEAD_VALUE
       if ( uJTP_RxRunMode == _RXMGT_NODATA )
       {
           // Read 1st Byte to check HEAD_VALUE
           while ( uTempIdxR < uTempIdxW )
           {
               if ( arbTempBuff[uTempIdxR++] == (U08)(JTP_HEAD_VALUE & 0x00FF) )
               {
                   uJTP_RxRunMode = _RXMGT_START;
                   break;
               }
           }
       }
       // Check other HEAD_VALUE
       else if ( uJTP_RxRunMode == _RXMGT_START )
       {
           // Read 2nd byte to check other HEAD_VALUE
           if ( arbTempBuff[uTempIdxR++] == (U08)((JTP_HEAD_VALUE >> 8) & 0x00FF) )
           {
               pFrame = (JTP_FRAME *)arbFrame;
               pFrame->uHeader = JTP_HEAD_VALUE;
               uFrameIdxW = sizeof(pFrame->uHeader);

               uJTP_RxRunMode = _RXMGT_HEAD;
           }
           else
           {
               uJTP_RxRunMode = _RXMGT_NODATA;
           }
       }
       // Read Frame.uTgID ~ Frame.uDataLen
       else if ( uJTP_RxRunMode == _RXMGT_HEAD )
       {
           pFrame = (JTP_FRAME *)arbFrame;
           uNeedRxLen = (U16)((U08*)&pFrame->uChksum - (U08*)pFrame) - uFrameIdxW;
           if ( uNeedRxLen > (uTempIdxW - uTempIdxR) )
           {
               uNeedRxLen = uTempIdxW - uTempIdxR;
           }
           // copy data
           memcpy(&arbFrame[uFrameIdxW], &arbTempBuff[uTempIdxR], uNeedRxLen);
           uFrameIdxW += uNeedRxLen;
           uTempIdxR += uNeedRxLen;

            // Check if the data is enough to be needed
            if ( uFrameIdxW >= (U16)((U08*)&pFrame->uChksum - (U08*)pFrame) )
            {
                if ( pFrame->uTgtID != 0x0000 )
                {
                    tMyFrame = true;
                    memcpy(arbRcvBuff, arbFrame, uFrameIdxW);
                    uJTP_RxBuffIdx = uFrameIdxW;

                    // start to read data
                    uJTP_RxRunMode = _RXMGT_DATA;

                    // if DataLen is too long
                    if ( pFrame->uDataLen > MAX_RCV_BUFFER_LENGTH)
                    {
                        tMyFrame = false;
                        uJTP_RxRunMode = _RXMGT_NODATA;
                    }
                 }
                else
                {
                    tMyFrame = false;
                    uJTP_RxRunMode = _RXMGT_NODATA;
                }
            }
       }
       // Frame.arbData ~ Frame.uFoot
       else if ( uJTP_RxRunMode == _RXMGT_DATA )
       {
           pFrame = (JTP_FRAME *)arbFrame;

           // read data
           uNeedRxLen = sizeof(JTP_FRAME) + _MK_ALIGN_2(pFrame->uDataLen) - uFrameIdxW;
           if ( uNeedRxLen > 0 )
           {
               if ( uNeedRxLen > (uTempIdxW - uTempIdxR) )
               {
                   uNeedRxLen = uTempIdxW - uTempIdxR;
               }

               if ( tMyFrame == true )
               {
                   memcpy(&arbRcvBuff[uJTP_RxBuffIdx], &arbTempBuff[uTempIdxR], uNeedRxLen);
                   uJTP_RxBuffIdx += uNeedRxLen;
               }
               uFrameIdxW += uNeedRxLen;
               uTempIdxR += uNeedRxLen;
           }

           // finish readinng data
           if ( uFrameIdxW >= (sizeof(JTP_FRAME) + _MK_ALIGN_2(pFrame->uDataLen)) )
           {
               uJTP_RxRunMode = _RXMGT_END;
               continue;
           }
       }
       else if ( uJTP_RxRunMode == _RXMGT_END )
       {
           if ( tMyFrame == true )
           {
               if ( CheckJtpData(arbRcvBuff) )
               {
                   SerialPushData(arbRcvBuff, uJTP_RxBuffIdx);
                   bRet = true;
               }
           }

           tMyFrame = false;
           uJTP_RxRunMode = _RXMGT_NODATA;
       }

       if ( uTempIdxR < uTempIdxW ) continue;

       uRxLen = SerialGetCount();
       if ( uRxLen == 0 )   break;

        // Read received data
        uTempIdxR = 0;
        uTempIdxW = (uRxLen < sizeof(arbTempBuff)) ? uRxLen : sizeof(arbTempBuff);
        SerialGetByteData(arbTempBuff, uTempIdxW);
    }
    return bRet;
}

void JtpSend_CmdSendReady(U16 uParameter)
{
    U08 arbJtpTxBuffer[MAX_JTP_SND_BUFFER];
    U16 uLen;    
    
    memcpy(Jtp_GetDataLoc(arbJtpTxBuffer), R7_MCU_VERSION, 16);
    uLen = JtpMakeTransferData(arbJtpTxBuffer, JTP_ID_BLACKFIN, JTP_ID_PIC, uParameter, CMD_READY, 16);
    SerialWriteData(arbJtpTxBuffer,uLen); // SendData(arbUartTxBuffer,uLen);   
}