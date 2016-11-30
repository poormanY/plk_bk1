//
// File   : isr.c
// Author : YSW
// Created on 2016.04.15
//
// Brief : Interrupt ISR 
// Detail :
//
#include <xc.h>
#include "isr.h"
#include "def_var.h"
#include "timer.h"
#include "serial.h"

#define MAX_PULSE_PERIOD 11

static U16 uPulse[MAX_PULSE_PERIOD] = {0,};
static U08 bPulseIdx = 0;
static U16 uSumPulse = 0;

U32 gulSystemTick = 0;
U32 gulDelayTimer = 0;

static void isr_timer0(void)
{
    if ( TMR0IF && TMR0IE )
	{
		TMR0IF	= 0;
		//TMR0 	= 0xFF;
        TMR0 	= 0;
        
        uPulse[bPulseIdx] += TMR0;
	}    
}

static void isr_timer1(void)
{
    static U08 bCount100ms = 10;    // 10ms * 10 = 100ms
    
    if ( (TMR1IF) && (TMR1IE) )		// 10ms
	{
        TMR1IF 	= 0;    
        TMR1 = 0xD8F0; // 0xFFFF - 0x2710(10000us) + 1 = 0xD8F0
        if ( gulSystemTick >= 0xFFFFFFFF) gulSystemTick = 0;
        gulSystemTick++;
        
        // delay timer for 10ms
        if ( gulDelayTimer != 0 )   gulDelayTimer--;
        
        bCount100ms--;
        if ( bCount100ms == 0 )
        {
            uPulse[bPulseIdx] += TMR0;
            TMR0 = 0;
            uSumPulse += uPulse[bPulseIdx];
            
            // for next stack
            bPulseIdx++;
            if ( bPulseIdx >= MAX_PULSE_PERIOD )
            {
                bPulseIdx = 0;
            }
            uSumPulse -= uPulse[bPulseIdx];
            uPulse[bPulseIdx] = 0;
            
            bCount100ms = 10;
        }        
    }    
}

U16 isr_get_car_pulse(void)
{
    return uSumPulse;
}

void interrupt isr(void)
{
    if ( TMR0IF && TMR0IE )	isr_timer0();
    if ( TMR1IF && TMR1IE ) isr_timer1();
    ///////////////////////////////////////////////////////////////////////////
    // UART - RX : receive data
    ///////////////////////////////////////////////////////////////////////////    
    if ( PIR1bits.RCIF && PIE1bits.RCIE)
    {
        PIR1bits.RCIF = 0;
        
        if ( g_uartRxIdxW >= UART_RX_BUFF_MAX ) g_uartRxIdxW = 0;
        g_uartRxBuf[g_uartRxIdxW++] = RC1REG;
    }
    ///////////////////////////////////////////////////////////////////////////
    // EUSART-TX : transmit data
    ///////////////////////////////////////////////////////////////////////////
    if (PIR1bits.TXIF && PIE1bits.TXIE)
    {
        if (g_uartTxIdxR != g_uartTxIdxW)
        {
            if ( g_uartTxIdxR >= UART_TX_BUFF_MAX )  g_uartTxIdxR = 0;
            TXREG1 = g_uartTxBuf[g_uartTxIdxR++];
        }
        else
        {
            PIE1bits.TXIE = 0;
        }
    }    
}