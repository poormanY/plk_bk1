/////////////////////////////////////////////////////////
//
//  File name : uart.h
//	Author    : YSW
//  Date      : 2015.08.18
//
/////////////////////////////////////////////////////////

#ifndef UART_H
#define	UART_H

#include "../define.h"

/////////////////// UART Data Length ///////////////////
#define MAX_UART_BUFFER_LENGTH 256
#define MAX_JTP_SND_BUFFER 64
#define MAX_RCV_BUFFER_LENGTH 64
#define PACKET_ARRAY 4
#define DISPLAY_BUFFER_LENGTH 18

//// RX ////
U08 arbUartRxBuffer[MAX_UART_BUFFER_LENGTH];    // isr.c : RCREG value
U16 uUartRxIndexW;
U16 uUartRxIndexR;
U08 arbPacketRxBuffer[PACKET_ARRAY][MAX_RCV_BUFFER_LENGTH];
U16 uPacketArrayRxIndexR;
U16 uPacketArrayRxIndexW;
//// TX ////
U08 arbUartTxBuffer[MAX_UART_BUFFER_LENGTH];    // isr.c : TXREG1 value
U16 uUartTxIndexW;
U16 uUartTxIndexR;


void uart_init(void);
U16 SerialGetCount(void);
U16 SerialGetByteData(U08 *pBuf, U16 uLen);
void SerialPushData(U08 *pBuf, U16 uLen);
void SerialWriteData(U08 *pBuf, U16 uLen);

void UartSend(U08 uData);
void SendData(U08 *uData, U16 uLen);

#endif	/* UART_H */

