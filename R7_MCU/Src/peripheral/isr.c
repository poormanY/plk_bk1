#include <xc.h>
#include <string.h>
#include "isr.h"
#include "uart.h"
#include "timer.h"
#include "spi.h"
#include "../proc/spi_proc.h"
#include "delay.h"
#include "../define.h"

U16	g_car_pulse = 0;
U16	g_pulse = 0;
U16	g_xor_value = 0;
TimerFlag_t		g_stTimerFlags;

U32 wCTimerIrqCnt = 0;

// vehicle pulse
static void isr_timer0(void)
{
	if ( TMR0IF && TMR0IE )
	{
		TMR0IF	= 0;
		TMR0 	= 0xFF;

		g_pulse++;
	}
}


static void isr_timer1(void)
{
	static U16	uc1secCnt = 0;

	if ( (TMR1IF) && (TMR1IE) )		//  10ms
	{
		TMR1IF 	= 0;
		//TMR1	= 0x3CB0;   // 100ms
        TMR1    = 0xEC78;   //  10ms = 2us * 5000

        gulSystemTick++;
		uc1secCnt++;
		wCTimerIrqCnt++;			// SPI protocol timer

        g_stTimerFlags.flag10ms = 1;

		if ( uc1secCnt >= 100 )					// 1 second
		{
			uc1secCnt = 0;
			g_stTimerFlags.flag1sec = 1;

			// update pulse...
			g_car_pulse = g_pulse;

			g_pulse = 0;
		}
               
		if ( ++g_xor_value >= 100 )
			g_xor_value = 0;
	}
}

U16  isr_get_car_pulse(void)
{
	return g_car_pulse;
}


void interrupt ISR(void)
{
	if ( TMR0IF )	isr_timer0();
	if ( TMR1IF )	isr_timer1();

	if ( (SSP1IF) && (SSP1IE) )
	{
		SSP1IF = 0;
		if (uSPIModeState == MODE_READ)
		{
            if ( g_spiRxIdx >= SPI_BUFF_MAX )   g_spiRxIdx = 0;
            
			g_spiRxBuf[g_spiRxIdx++] = SSPBUF;
			//SSPBUF = 0;
			if ( (g_spiRxBuf[g_spiRxIdx-2] == 0xF0) && (g_spiRxBuf[g_spiRxIdx-1] == 0x55) )
			{
				uSPIModeState = MODE_READ_COMPLETE;
			}
		}
		else if (uSPIModeState == MODE_WRITE)
		{
			SSPBUF = g_spiTxBuf[g_spiTxIdx++];
			if (g_spiTxIdx >= g_spiTxLength)
			{
                g_spiRxIdx = 0;
				g_spiTxIdx = 0;
                wCTimerIrqCnt = 0;
				uSPIModeState = MODE_READ;
			}
		}
		else
		{
			SSPBUF = 0;
		}
	}
    
    
////// EUSART-RX : receive data
    if (PIR1bits.RCIF && PIE1bits.RCIE)
    {
        arbUartRxBuffer[uUartRxIndexW++] = RCREG;
        if ( uUartRxIndexW >= MAX_UART_BUFFER_LENGTH )  uUartRxIndexW = 0;
    }

////// EUSART-TX : transmit data
    if (PIR1bits.TXIF && PIE1bits.TXIE)
    {    
        if (uUartTxIndexR != uUartTxIndexW)
        {
            TXREG1 = arbUartTxBuffer[uUartTxIndexR++];
            if ( uUartTxIndexR >= MAX_UART_BUFFER_LENGTH )  uUartTxIndexR = 0;
        }
        else
        {
            PIE1bits.TXIE = 0;
        }
    }    
}
