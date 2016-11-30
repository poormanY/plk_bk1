/////////////////////////////////////////////////////////
//
//  File name : uart.c
//	Author    : YSW
//  Date      : 2015.08.18
//
/////////////////////////////////////////////////////////

#include <string.h>
#include <xc.h>
#include "uart.h"

void uart_init(void)
{
    PPSLOCKbits.PPSLOCKED = 0x00; 	// unlock PPS
    RC6PPS = 0b00010100; 			// TX Set to PORTC6
    PPSLOCKbits.PPSLOCKED = 0x01; 	// lock PPS

    TX1STA = 0;
	RC1STA = 0;
	BAUD1CON = 0;

    TX1STAbits.CSRC = 0;    // Asynchronous mode: Dont care
    TX1STAbits.TX9 = 0;     // Selects 8-bit transmission
    TX1STAbits.TXEN = 1;    // Transmit enabled
    TX1STAbits.SYNC = 0;    // Asynchronous mode
    TX1STAbits.SENDB = 0;   // Sync Break transmission completed
    TX1STAbits.BRGH = 0;    // Low speed
    TX1STAbits.TRMT = 1;    // TSR empty

    RC1STAbits.SPEN = 1;    // Serial port enabled
    RC1STAbits.RX9 = 0;     // Selects 8-bit reception
    RC1STAbits.SREN = 0;    // Asynchronous mode : Dont care
    RC1STAbits.CREN = 1;    // Enables receiver
    RC1STAbits.ADDEN = 0;   // Asynchronous mode 8-bit (RX9 = 0) : Dont care

    // 32MHz 9600bps
	// SPBRG = 51;
    // 16MHz 9600bps
	   SPBRG = 25;

    PIE1bits.RCIE = 1;
	PIE1bits.TXIE = 0;
}

U16 SerialGetCount(void)
{
    U16 uCount;

     if ( uUartRxIndexW < uUartRxIndexR )
    {
        uCount = uUartRxIndexW + MAX_UART_BUFFER_LENGTH - uUartRxIndexR;
    }
    else
    {
        uCount = uUartRxIndexW - uUartRxIndexR;
    }

    return uCount;
}

U16 SerialGetByteData(U08 *pBuf, U16 uLen)
{
    U16 uReadCnt;

    uReadCnt = 0;
    while(1)
    {
        if ( uReadCnt >= uLen ) break;

        pBuf[uReadCnt++] = arbUartRxBuffer[uUartRxIndexR++];
        if( uUartRxIndexR >= MAX_UART_BUFFER_LENGTH )   uUartRxIndexR = 0;
    }

    return uReadCnt;
}

void SerialPushData(U08 *pBuf, U16 uLen)
{
    memcpy(arbPacketRxBuffer[uPacketArrayRxIndexW], pBuf, uLen);
    uPacketArrayRxIndexW++;
    if (uPacketArrayRxIndexW >= PACKET_ARRAY) uPacketArrayRxIndexW = 0;
}

void SerialWriteData(U08 *pBuf, U16 uLen)
{
    U08 i;

    for (i = 0; i < uLen; i++)
    {
        arbUartTxBuffer[uUartTxIndexW++] = pBuf[i];
        if (uUartTxIndexW >= MAX_UART_BUFFER_LENGTH) uUartTxIndexW = 0;
    }
    
    if ( PIE1bits.TXIE == 0 )
    {
        TXREG1 = arbUartTxBuffer[uUartTxIndexR++];
        if ( uUartTxIndexR >= MAX_UART_BUFFER_LENGTH )  uUartTxIndexR = 0;
        PIE1bits.TXIE = 1;
    }
}

void UartSend(U08 uData)
{
    while(!TXSTA1bits.TRMT);
    TXREG1 = uData;
}

void SendData(U08 *uData, U16 uLen)
{
    U16 i;

    for (i=0; i<uLen; i++)
    {
        UartSend(uData[i]);
    }
}
