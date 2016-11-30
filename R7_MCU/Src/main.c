#include <xc.h>
#include "./proc/pwr_proc.h"
#include "./proc/adc_proc.h"
#include "./proc/spi_proc.h"
#include "./proc/uart_proc.h"
#include "./proc/adc_proc.h"
#include "./proc/jtp_proc.h"
#include "./peripheral/isr.h"
#include "./peripheral/delay.h"
#include "./peripheral/uart.h"
#include "HIGHT_MCU.h"


#pragma config FOSC = INTOSC    //  (INTOSC oscillator; I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
//#pragma config LPBOR= ON    // Low Power Brown-out Reset enable bit (LPBOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)


void osc_init(void)
{
    OSCCON = 0b01111010;    // 16MHz
}


void main(void)
{
    U32 gulPreSystemTick = 0;
    U08	main_run = 0;
    U08 dsp_boot_on  = 0;
    U08 uart_rcv = 0;
    
    // uart.h variable
    uUartRxIndexW = 0;
    uUartRxIndexR = 0;
    uPacketArrayRxIndexR = 0;
    uPacketArrayRxIndexW = 0;
    uUartTxIndexW = 0;
    uUartTxIndexR = 0;
    

    osc_init();
    pwr_proc_init();
    adc_proc_init();
    timer_init();
    uart_init();
    spi_proc_init();
    
    // Peripheral Interrupt Enable bit
    INTCONbits.PEIE = 1;
    // Global Interrupt Enable bit
    INTCONbits.GIE = 1;

    HIGHT_KeySched(pbUserKey, pbRoundKey);
    
    DelayMs(1000*1000);

    pwr_dsp_reset_ctrl();
    
    spi_proc();

    main_run = 1;
    while ( main_run )
    {
        gulPreSystemTick = gulSystemTick;
		////////////////////////////////////////////////////////////////////////
		// Clear watchdog counter(4ms * 1025 postscaler = 4.096ms)
		////////////////////////////////////////////////////////////////////////
		asm("CLRWDT");
        
        spi_proc();

        if ( g_stTimerFlags.flag1sec && (dsp_boot_on == 0) )
        {
            // if WD_EN pin is LOW for 1m, dsp status is boot_on
            dsp_boot_on = pwr_dsp_boot_on();
                        
            g_stTimerFlags.flag1sec = 0;
        }
        
        if ( g_stTimerFlags.flag10ms && (dsp_boot_on == 1) )
        {
            // If WD_EN pin is LOW, check WD_CLK pin is ticking
            //  WD_CLK pin is not ticking for 1s. Then reset dsp
            if ( pwr_dsp_wdt_reset() == 1 )
            {
                dsp_boot_on = 0;
            }
            
            g_stTimerFlags.flag10ms = 0; 
        }
        
        // UART for test PC tool
        uart_rcv = uart_proc();
        if ( uPacketArrayRxIndexR != uPacketArrayRxIndexW )
        {
            JtpSend_CmdSendReady(_JTP_RESP_OK);

            uPacketArrayRxIndexR++;
            if( uPacketArrayRxIndexR >= 4 ) uPacketArrayRxIndexR = 0;
        }
        
        // wait if while's running time is 0
        while(gulPreSystemTick == gulSystemTick);
    }
}
