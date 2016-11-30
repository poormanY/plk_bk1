//
// File   : uart.c
// Author : YSW
// Created on 2016.04.14
//
// Brief : UART Communication
// Detail : Universal Asynchronous Receiver/Transmitter Communication
//
#include <xc.h>
#include "uart.h"

void uart_init(void)
{
    // PPSLOCKED: PPS Locked bit
    //  1= PPS is locked. PPS selections can not be changed.
    //  0= PPS is not locked. PPS selections can be changed.
    PPSLOCKbits.PPSLOCKED = 0x00; 	// unlock PPS
    RC6PPS = 0b10100;               // TX Set to PORTC6
    PPSLOCKbits.PPSLOCKED = 0x01; 	// lock PPS

    ///////////////////////////////////////////////////////////////////////////
    // UART Communication - TX1STA, RC1STA, BAUD1CON
    //  8-bit/Asynchronous
    ///////////////////////////////////////////////////////////////////////////    
    TX1STA = 0;
	RC1STA = 0;
	BAUD1CON = 0;
    
    // CSRC: Clock Source Select bit
    //  Asynchronous mode:
    //   Don?t care
    //  Synchronous mode:
    //   1 = Master mode (clock generated internally from BRG)
    //   0 = Slave mode (clock from external source)
    TX1STAbits.CSRC = 0;
    // TX9: 9-bit Transmit Enable bit
    // 1 = Selects 9-bit transmission
    // 0 = Selects 8-bit transmission 
    TX1STAbits.TX9 = 0;
    // TXEN: Transmit Enable bit(1)
    //  1 = Transmit enabled
    //  0 = Transmit disabled
    TX1STAbits.TXEN = 1;
    // SYNC: EUSART Mode Select bit
    //  1 = Synchronous mode
    //  0 = Asynchronous mode
    TX1STAbits.SYNC = 0;
    // SENDB: Send Break Character bit
    // Asynchronous mode:
    //  1 = Send Sync Break on next transmission (cleared by hardware upon completion)
    //  0 = Sync Break transmission completed
    // Synchronous mode:
    //  Don?t care
    TX1STAbits.SENDB = 0;
    // BRGH: High Baud Rate Select bit
    // Asynchronous mode:
    //  1 = High speed
    //  0 = Low speed
    // Synchronous mode:
    //  Unused in this mode    
    TX1STAbits.BRGH = 0;
    // TRMT: Transmit Shift Register Status bit
    //  1 = TSR empty
    //  0 = TSR full
    TX1STAbits.TRMT = 1;
    
    // SPEN: Serial Port Enable bit
    //  1 = Serial port enabled
    //  0 = Serial port disabled (held in Reset)
    RC1STAbits.SPEN = 1;
    // RX9: 9-Bit Receive Enable bit
    //  1 = Selects 9-bit reception
    //  0 = Selects 8-bit reception
    RC1STAbits.RX9 = 0;
    // SREN: Single Receive Enable bit
    // Asynchronous mode:
    // Don?t care
    // Synchronous mode ? Master:
    //  1 = Enables single receive
    //  0 = Disables single receive
    //  This bit is cleared after reception is complete.
    // Synchronous mode ? Slave
    //  Don?t care
    RC1STAbits.SREN = 0;
    // CREN: Continuous Receive Enable bit
    // Asynchronous mode:
    //  1 = Enables receiver
    //  0 = Disables receiver
    // Synchronous mode:
    //  1 = Enables continuous receive until enable bit CREN is cleared (CREN overrides SREN)
    //  0 = Disables continuous receive
    RC1STAbits.CREN = 1;
    // ADDEN: Address Detect Enable bit
    // Asynchronous mode 9-bit (RX9 = 1):
    //  1 = Enables address detection, enable interrupt and load the receive buffer when RSR<8> is set
    //  0 = Disables address detection, all bytes are received and ninth bit can be used as parity bit
    // Asynchronous mode 8-bit (RX9 = 0):
    //  Don?t care
    RC1STAbits.ADDEN = 0;

    // BAUD RATES FOR ASYNCHRONOUS MODES
    // SYNC = 0, BRGH = 0, BRG16 = 0
    // Fosc = 32.00 MHz
    //    Baud Rate      SPBRG
    //      2400          207
    //      9600          51
    //     10417          47
    //     19.2k          25
    //     57.6k          3
	SPBRG = 51;

    // RCIF: USART Receive Interrupt Flag bit
    //  1 = Interrupt is pending
    //   0 = Interrupt is not pending
    PIR1bits.RCIF = 0;
    // RCIE: USART Receive Interrupt Enable bit
    //  1 = Enables the USART receive interrupt
    //  0 = Disables the USART receive interrupt
    PIE1bits.RCIE = 1;
    // TXIE: USART Transmit Interrupt Enable bit
    //  1 = Enables the USART transmit interrupt
    //  0 = Disables the USART transmit interrupt
	PIE1bits.TXIE = 0;
}