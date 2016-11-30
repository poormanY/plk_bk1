//
// File   : serial.h
// Author : YSW
// Created on 2016.04.15
//
// Brief : Serial
// Detail :
//
#ifndef SERIAL_H
#define	SERIAL_H

#define UART_RX_BUFF_MAX 256
#define UART_TX_BUFF_MAX 64

#define UART_RX_TEMP_MAX 128

// Variable
extern U16 g_uartRxIdxW;
extern U16 g_uartRxIdxR;
extern U08 g_uartRxBuf[UART_RX_BUFF_MAX];

extern U16 g_uartTempIdxW;
extern U16 g_uartTempIdxR;
extern U08 g_uartRxTemp[UART_RX_TEMP_MAX];

extern U16 g_uartTxIdxW;
extern U16 g_uartTxIdxR;
extern U08 g_uartTxBuf[UART_TX_BUFF_MAX];


// Function
extern U16 SerialGetLength(void);
extern U16 SerialGetByteData(U08 *pTemp, U16 uLen);

extern U08 Uart_Send_byte(U08 bData);
extern U08 Uart_Send(U08 *pData, U16 uLen);

#endif	/* SERIAL_H */

