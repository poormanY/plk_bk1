//
// File   : serial.c
// Author : YSW
// Created on 2016.04.15
//
// Brief : Serial
// Detail :
//
#include "xc.h"
#include "def_var.h"
#include "serial.h"

U16 g_uartRxIdxW = 0;
U16 g_uartRxIdxR = 0;
U08 g_uartRxBuf[UART_RX_BUFF_MAX] = {0,};

// g_uartRxBuf
// | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | ... |
// g_uartRxTemp
// | 0 | 1 | 2 | 3 | 
// | 4 | 5 | 6 | 7 | 
// | ... |
U16 g_uartTempIdxW = 0;
U16 g_uartTempIdxR = 0;
U08 g_uartRxTemp[UART_RX_TEMP_MAX] = {0,};

U16 g_uartTxIdxW = 0;
U16 g_uartTxIdxR = 0;
U08 g_uartTxBuf[UART_TX_BUFF_MAX] = {0,};

U16 SerialGetLength(void)
{
    U16 uRxLen = 0;
    
    if ( g_uartRxIdxR <= g_uartRxIdxW )
    {
        uRxLen = g_uartRxIdxW - g_uartRxIdxR;
    }
    else
    {
        uRxLen = (UART_RX_BUFF_MAX - g_uartRxIdxR) + g_uartRxIdxW;
    }    
    
    return uRxLen;
}

U16 SerialGetByteData(U08 *pTemp, U16 uLen)
{
    U16 uReadCnt;
    
    uReadCnt = 0;
    while(1)
    {
        if ( uReadCnt >= uLen ) break;
        if ( uReadCnt >= UART_RX_TEMP_MAX ) break;
        
        if ( g_uartRxIdxR >= UART_RX_BUFF_MAX ) g_uartRxIdxR = 0;
        pTemp[uReadCnt++] = g_uartRxBuf[g_uartRxIdxR++];
    }
    
    return uReadCnt;
}


U08 Uart_Send_byte(U08 bData)
{
    if ( g_uartTxIdxW >= UART_TX_BUFF_MAX )  g_uartTxIdxW = 0;
    
    g_uartTxBuf[g_uartTxIdxW++] = bData;
    
    return 1;
}

U08 Uart_Send(U08 *pData, U16 uLen)
{
    U16 uSendCnt = 0;
    
    while(1)
    {
        if ( uSendCnt >= uLen ) break;
                
        Uart_Send_byte(pData[uSendCnt++]);
    }
    
    if ( PIE1bits.TXIE == 0 )
    {
        if ( g_uartTxIdxR >= UART_TX_BUFF_MAX )  g_uartTxIdxR = 0;
        TXREG1 = g_uartTxBuf[g_uartTxIdxR++];
        
        PIE1bits.TXIE = 1;
    }
    
    return 1;
}