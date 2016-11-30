//
// File   : jtp.c
// Author : YSW
// Created on 2016.04.19
//
// Brief : JTP Protocol
// Detail :
//
#include <string.h>
#include <stdlib.h>
#include "def_var.h"
#include "jtp.h"
#include "serial.h"
#include "isr.h"
#include "opx_mcu_version.h"
#include "adc_proc.h"
#include "HIGHT_MCU.h"
#include "adc.h"
#include "adc_proc.h"
#include "pwr_ctrl.h"

#define _SAVE_RX_TIME() (uart_RxTimer = gulSystemTick)
#define _COMP_RX_TIME() (gulSystemTick < uart_RxTimer) ? (0xFFFFFFFF-uart_RxTimer+gulSystemTick) : (gulSystemTick - uart_RxTimer)
#define UART_RX_TIME_OUT 100    // 100*10ms (gulSystemTick is added 1 every 10ms)

#ifdef HIGHT_CRYPT_EN
static U16 g_OpxCount = 0;
#endif

static U08 arbJtpPackBuff[MAX_JTP_PACK_NUMBER][MAX_JTP_BUFFER_LENGTH] = {0,};
static U16 uJtpPackIdxW = 0;
static U16 uJtpPackIdxR = 0;

static OPX_STATIC_INFO *opx_static_info;
static OPX_DYNAMIC_INFO *opx_dynamic_info;
static U16 uOpxPowerState = POWER_STATE_READY;
static U16 uWatchDogFireSeconds = 120;

static MCU_STATIC_INFO *mcu_static_info;
static MCU_DYNAMIC_INFO *mcu_dynamic_info;

U08 Jtp_comm_init(void)
{
    //opx_static_info = (OPX_STATIC_INFO *)malloc(sizeof(OPX_STATIC_INFO));
    //memset(opx_static_info, 0, sizeof(OPX_STATIC_INFO));

    //opx_dynamic_info = (OPX_DYNAMIC_INFO *)malloc(sizeof(OPX_DYNAMIC_INFO));
    //memset(opx_dynamic_info, 0, sizeof(OPX_DYNAMIC_INFO));

    //mcu_static_info = (MCU_STATIC_INFO *)malloc(sizeof(MCU_STATIC_INFO));
    //memset(mcu_static_info, 0, sizeof(MCU_STATIC_INFO));

    //mcu_dynamic_info = (MCU_DYNAMIC_INFO *)malloc(sizeof(MCU_DYNAMIC_INFO));
    //memset(mcu_dynamic_info, 0, sizeof(MCU_DYNAMIC_INFO));


#ifdef HIGHT_CRYPT_EN
    HIGHT_KeySched(pbUserKey, pbRoundKey);
#endif

	return 1;
}

U08 Jtp_comm_close(void)
{
    //free(opx_static_info);
    //free(opx_dynamic_info);
    //free(mcu_static_info);
    //free(mcu_dynamic_info);

	return 1;
}




U08 Jtp_RxRun(void)
{
    static U08 arbJtpBuff[MAX_JTP_BUFFER_LENGTH];
    static U08 JTP_RxRunMode = _RXMGT_NODATA;
    static U16 uJtpBuffIdx = 0;
    static U16 uJTP_DATA_LEN = 0;
    static U32 uart_RxTimer = 0;
    
    U08 bRet = false;
    
    U16 uRxLen = 0;
    U16 uTempLen = 0;
    
    JTP_FRAME *pFrame;
    
    //                        |<---------uRxLen--------->|
    //  g_uartRxBuf | a0 | a1 | a2 | a3 | a4 | a5 | a6 | a7 | ... |
    //                        |-g_uartRxIdxR                |-g_uartRxIdxW
    uRxLen = SerialGetLength();
    
    // Time-out while uart data is being received
    if ( uRxLen == 0 )
    {
        if ( JTP_RxRunMode != _RXMGT_NODATA )
        {
            if( _COMP_RX_TIME() > UART_RX_TIME_OUT )
            {
                JTP_RxRunMode = _RXMGT_NODATA;
            }
        }        
        return bRet;
    }
        
    if ( uRxLen > 0 )
    {
        //                        |<---------uRxLen--------->|
        //  g_uartRxBuf | a0 | a1 | a2 | a3 | a4 | a5 | a6 | a7 | ... |
        //                        |-g_uartRxIdxR                |-g_uartRxIdxW
        //
        //              |<---------uRxLen--------->|
        // g_uartRxTemp | a2 | a3 | a4 | a5 | a6 | a7 | ... |
        //              |-g_uartTempIdxR              |-g_uartTempIdxW
        //
        memset(g_uartRxTemp, 0, UART_RX_TEMP_MAX);
        uTempLen = SerialGetByteData(g_uartRxTemp, uRxLen);
        g_uartTempIdxW = uTempLen;
        g_uartTempIdxR = 0;
    }
    
    while(true)
    {
        // JTP Frame begins with detecting JTP_HEAD_VALUE
        if ( JTP_RxRunMode == _RXMGT_NODATA )
        {
            // Read 1st Byte to check JTP_HEAD_VALUE (0xAAF0 & 0x00FF)
            while ( g_uartTempIdxR < g_uartTempIdxW )
            {
                if ( g_uartRxTemp[g_uartTempIdxR++] == (U08)(JTP_HEAD_VALUE & 0x00FF) )
                {
                    JTP_RxRunMode = _RXMGT_START;
                    break;
                }
            }
        }
        else if ( JTP_RxRunMode == _RXMGT_START )
        {
            // Read 2nd Byte to check JTP_HEAD_VALUE ((0xAAF0 & 0xFF00)>>8)
            if ( g_uartRxTemp[g_uartTempIdxR++] == (U08)((JTP_HEAD_VALUE & 0xFF00)>>8) )
            {
                // arbJtpBuff
                // | F0 | AA | ... |
                //           |- 2byte
                memset(arbJtpBuff, 0, MAX_JTP_BUFFER_LENGTH);
                pFrame = (JTP_FRAME *)arbJtpBuff;
                pFrame->uHeader = JTP_HEAD_VALUE;
                uJtpBuffIdx = sizeof(pFrame->uHeader);  // ~JTP_Frame.uHeader 2byte
                
                JTP_RxRunMode = _RXMGT_HEAD;
            }
            else
            {
                JTP_RxRunMode = _RXMGT_NODATA;                
            }            
        }
        else if ( JTP_RxRunMode == _RXMGT_HEAD )
        {
            // arbJtpBuff
            // | F0 | AA | 50 | 49 | 42 | 42 | 01 | 00 | 00 | 00 | 00 | 00 | ... |
            //                                                             |- 12byte
            while( g_uartTempIdxR < g_uartTempIdxW )
            {                
                arbJtpBuff[uJtpBuffIdx++] = g_uartRxTemp[g_uartTempIdxR++];
            
                if ( uJtpBuffIdx >= JTP_HEAD_LEN) // ~JTP_Frame.uDataLen : 12byte
                {
                    pFrame = (JTP_FRAME *)arbJtpBuff;
                    uJTP_DATA_LEN = pFrame->uDataLen;
                    
                    // arbJtpBuff Max Length is MAX_JTP_BUFFER_LENGTH
                    if ( (JTP_HEAD_LEN + uJTP_DATA_LEN + JTP_TAIL_LEN) >= MAX_JTP_BUFFER_LENGTH )
                    {
                        JTP_RxRunMode = _RXMGT_NODATA;
                    }
                    
                    JTP_RxRunMode = _RXMGT_DATA;
                    break;
                }
            }
        }
        else if ( JTP_RxRunMode == _RXMGT_DATA )
        {
            while( g_uartTempIdxR < g_uartTempIdxW )
            {
                arbJtpBuff[uJtpBuffIdx++] = g_uartRxTemp[g_uartTempIdxR++];
                
                if ( uJtpBuffIdx >= (JTP_HEAD_LEN + uJTP_DATA_LEN + JTP_TAIL_LEN) )
                {
                    JTP_RxRunMode = _RXMGT_END;
                    break;
                }
            }
            
            if ( JTP_RxRunMode == _RXMGT_END )
            {
                if ( uJtpPackIdxW >= MAX_JTP_PACK_NUMBER )  uJtpPackIdxW = 0;
                memcpy(arbJtpPackBuff[uJtpPackIdxW], arbJtpBuff, uJtpBuffIdx);
                uJtpPackIdxW++;

                JTP_RxRunMode = _RXMGT_NODATA;
            }
        }
        
        if ( g_uartTempIdxR < g_uartTempIdxW ) continue;
        
        uRxLen = SerialGetLength();
        if ( uRxLen == 0 )  break;
        
        memset(g_uartRxTemp, 0, UART_RX_TEMP_MAX);
        uTempLen = SerialGetByteData(g_uartRxTemp, uRxLen);
        g_uartTempIdxW = uTempLen;
        g_uartTempIdxR = 0;        
    }
    _SAVE_RX_TIME();
    
    return bRet;
}

U16 Jtp_GetDataLen(U08 *pData)
{
    U16 uDataLen = 0;
    JTP_FRAME *pFrame;
    
    pFrame = (JTP_FRAME *)pData;
    uDataLen = pFrame->uDataLen;
    
    return uDataLen;
}

U16 Jtp_GetCommand(U08 *pData)
{
    U16 uCmd = 0;
    JTP_FRAME *pFrame;
    
    pFrame = (JTP_FRAME *)pData;
    uCmd = pFrame->uCommand;
    
    return uCmd;
}

U16 Jtp_GetTgtId(U08 *pData)
{
    U16 uTgtId = 0;
    JTP_FRAME *pFrame;
    
    pFrame = (JTP_FRAME *)pData;
    uTgtId = pFrame->uTgtId;
    
    return uTgtId;
}

U16 Jtp_GetSrcId(U08 *pData)
{
    U16 uSrcId = 0;
    JTP_FRAME *pFrame;
    
    pFrame = (JTP_FRAME *)pData;
    uSrcId = pFrame->uSrcId;
    
    return uSrcId;    
}

U16 Jtp_GetChksum(U08 *pData)
{
    U16 *puData;
    U16 uDataLen = 0;
    U16 uXorLen = 0;
    U16 uChksum = 0;
    U16 uIdx = 0;
                
    uDataLen = Jtp_GetDataLen(pData);
    uXorLen = JTP_HEAD_LEN + uDataLen;
    
    puData = (U16 *)pData;
    uXorLen >>= 1;
    
    for ( uIdx = 0; uIdx < uXorLen; uIdx++ )
    {
        uChksum ^= puData[uIdx];
    }
    uChksum = ~uChksum;
    
    return uChksum;
}


// return err massage(JTP parameter) of received JTP data
U16 Jtp_ValidCheck(U08 *pData)
{
    U16 uDataLen = 0;
    U16 uChksum;
    U16 uFooter = 0;
    JTP_FRAME *pFrame;
    
    uDataLen = Jtp_GetDataLen(pData);
    uChksum = *((U16 *)(pData + JTP_HEAD_LEN + uDataLen));
    uFooter = *((U16 *)(pData + JTP_HEAD_LEN + uDataLen + 2 ));
    
    pFrame = (JTP_FRAME *)pData;
    
    if ( pFrame->uHeader != JTP_HEAD_VALUE )
    {
        return _JTP_RESP_TRANS_ERR;        
    }
    
    if ( (JTP_HEAD_LEN + uDataLen + JTP_TAIL_LEN) >= MAX_JTP_BUFFER_LENGTH )
    {
        return _JTP_RESP_TRANS_TOO_BIG;
    }
    
    if ( uFooter != JTP_FOOT_VALUE )
    {
        return _JTP_RESP_TRANS_MSGEND;
    }
    
    if ( uChksum != Jtp_GetChksum(pData))
    {
        return _JTP_RESP_TRANS_CHKSUM;
    }
    
    if ( (pFrame->uCommand != CMD_READY) && (pFrame->uCommand != CMD_SEND_STATE) )
    {
        return _JTP_RESP_CMD_RSV;
    }
    
    if ( (pFrame->uTgtId != JTP_ID_PIC) )
    {
        return _JTP_RESP_TRANS_ERR;
    }
    
    if ( (pFrame->uSrcId != JTP_ID_CAM) )
    {
        return _JTP_RESP_TRANS_ERR;
    }
        
    return _JTP_RESP_OK;
}

U16 Jtp_MakeTransferData(U08 *pBuf, U16 uTgtId, U16 uSrcId, U16 uCmd, U16 uParam, U16 uDataLen, U08 *pData)
{
    U16 uTotalLen = 0;
    U16 pTailData[2] = {0,};
    JTP_FRAME *pFrame;
    pFrame = (JTP_FRAME *)pBuf;
    
    pFrame->uHeader = JTP_HEAD_VALUE;
    pFrame->uTgtId = uTgtId;
    pFrame->uSrcId = uSrcId;
    pFrame->uCommand = uCmd;
    pFrame->uParam = uParam;
    pFrame->uDataLen = uDataLen;
    
    if ( uDataLen > 0 ) memcpy(&pBuf[JTP_HEAD_LEN], pData, uDataLen);
    
    pTailData[0] = Jtp_GetChksum(pBuf);
    pTailData[1] = JTP_FOOT_VALUE;
    memcpy(&pBuf[JTP_HEAD_LEN + uDataLen], pTailData, 4);
    
    uTotalLen = JTP_HEAD_LEN + uDataLen + JTP_TAIL_LEN;
        
    return uTotalLen;
}

U08 Jtp_SaveRxData(U08 *pRxData, U16 uCmd)
{
    U08 bRet = false;
    
#ifdef HIGHT_CRYPT_EN
        JTP_Decrypt(pbRoundKey, pRxData, 8);
#endif
        
    if ( uCmd == CMD_READY )
    {
        opx_static_info = (OPX_STATIC_INFO *)pRxData;
        
        set_adc_bplus_ref(opx_static_info->uBplusThresholdVolt);
        set_wakeup_temp_ref(opx_static_info->uWakeUpTemperature);
        uWatchDogFireSeconds = opx_static_info->uWatchDogFireTime;
        
        //power off bug
        //uOpxPowerState = POWER_STATE_ON;                
#ifdef HIGHT_CRYPT_EN
        g_OpxCount = opx_static_info->uOpxCount;
#endif
        
        bRet = true;        
    }
    else if ( uCmd == CMD_SEND_STATE )
    {
        opx_dynamic_info = (OPX_DYNAMIC_INFO *)pRxData;    
        
        uOpxPowerState = opx_dynamic_info->uPowerCommand;
#ifdef HIGHT_CRYPT_EN
        g_OpxCount = opx_dynamic_info->uOpxCount;
#endif        
        
        bRet = true;        
    }
    
    return bRet;
}

U16 Jtp_GetTxData(U08 *pTxData, U16 uCmd)
{
    U16 uTxLen = 0;
    
     if ( uCmd == CMD_READY )
    {
        mcu_static_info = (MCU_STATIC_INFO *)pTxData;         
        uTxLen = sizeof(MCU_STATIC_INFO);
        
        mcu_static_info->uMcuVersion = OPX_MCU_VERSION;
        
#ifdef HIGHT_CRYPT_EN
        mcu_static_info->uRandomNumber = adc_read(ADC_ID_B_PLUS);
        mcu_static_info->uMcuCount = g_OpxCount;
#endif
        
    }
    else if ( uCmd == CMD_SEND_STATE )
    {
        mcu_dynamic_info = (MCU_DYNAMIC_INFO *)pTxData;
        uTxLen = sizeof(MCU_DYNAMIC_INFO);
        
        adc_proc(mcu_dynamic_info);
                
        mcu_dynamic_info->uSpeedPulse = isr_get_car_pulse();
#ifdef HIGHT_CRYPT_EN
        mcu_dynamic_info->uRandomNumber = adc_read(ADC_ID_B_PLUS);
        mcu_dynamic_info->uMcuCount = g_OpxCount;
#endif
    }
    
 #ifdef HIGHT_CRYPT_EN
        JTP_Encrypt(pbRoundKey, pTxData, 8);
#endif           
    return uTxLen;
}

U08 Jtp_Protocol(void)
{
    U08 uJtpTxBuff[MAX_JTP_BUFFER_LENGTH] = {0,};
    U08 uJtpData[MAX_JTP_BUFFER_LENGTH] = {0,};
    U08 bRet = 0;
    U16 uCommand = 0;
    U16 uDataRxLen = 0;
    U16 uDataTxLen = 0;
    U16 uTxLen = 0;
    U16 uParam = 0;
        
    Jtp_RxRun();
    
    if ( uJtpPackIdxW != uJtpPackIdxR )
    {
        if ( uJtpPackIdxR >= MAX_JTP_PACK_NUMBER )  uJtpPackIdxR = 0;
        
        uCommand = Jtp_GetCommand(arbJtpPackBuff[uJtpPackIdxR]);
        uParam = Jtp_ValidCheck(arbJtpPackBuff[uJtpPackIdxR]);
        
        uDataRxLen = Jtp_GetDataLen(arbJtpPackBuff[uJtpPackIdxR]);        
        if ( uDataRxLen > 0 )
        {
            memcpy(uJtpData, &arbJtpPackBuff[uJtpPackIdxR][JTP_HEAD_LEN], uDataRxLen);
            Jtp_SaveRxData(uJtpData, uCommand);
            memset(uJtpData, 0, MAX_JTP_BUFFER_LENGTH);
        }
        
        uDataTxLen = Jtp_GetTxData(uJtpData, uCommand);

        uTxLen = Jtp_MakeTransferData(uJtpTxBuff, JTP_ID_CAM, JTP_ID_PIC, uCommand, uParam, uDataTxLen, uJtpData);
        
        bRet = Uart_Send(uJtpTxBuff,uTxLen);
        
        uJtpPackIdxR++;
    }
    
    return bRet;
}

U16 Jtp_Get_PowerCommand(void)
{
    return uOpxPowerState;
}
void Jtp_Set_PowerCommand(U16 uPwrCmd)
{
    uOpxPowerState = uPwrCmd;
}

U16 Jtp_Get_WatchDogFireSec(void)
{
    return uWatchDogFireSeconds;
}
void Jtp_Set_WatchDogFireSec(U16 uWDT)
{
    uWatchDogFireSeconds = uWDT;
}