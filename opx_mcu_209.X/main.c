///////////////////////////////////////////////////////////////////////////////
// File   : main.c
// Author : ysw
// Created on 2016.04.14
//
// Mcu : PIC16F1718
// Compiler : MPLAB X IDE x3.05 - XC8
//
// Brief : opx mcu
// Detail : 1. read adc value of turn, brake, ig, b+, temp and transmit to opx
//          2. power control for opx
//          3. watch-dog reset for opx
//          4. encryption communication for chip business
//
///////////////////////////////////////////////////////////////////////////////
#include <xc.h>
#include <string.h>
#include "osc.h"
#include "gpio.h"
#include "adc.h"
#include "timer.h"
#include "uart.h"
#include "isr.h"
#include "delay.h"
#include "serial.h"
#include "jtp.h"
#include "HIGHT_MCU.h"
#include "pwr_ctrl.h"
#include "opx_mcu_version.h"

// PIC16(L)F171X_Memory_Programming_Specification.pdf - 11p
// CONFIG1 register
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor is disabled
#pragma config IESO = OFF       // Internal/External Switchover mode is disabled
#pragma config CLKOUTEN = OFF   // CLKOUT function is disabled. I/O or oscillator function on CLKOUT
#pragma config BOREN = ON       // Brown-out Reset Enable bits
#pragma config CP = ON          // Program memory code protection is enabled
#pragma config MCLRE = ON       // This bit is ignored.
#pragma config PWRTE = ON       // PWRT enabled
#pragma config WDTE = ON        // WDT enabled
#pragma config FOSC = INTOSC    // Internal HFINTOSC, I/O function on OSC1/CLKIN

// CONFIG2 register
#pragma config LVP = ON         // Low-voltage programming enabled
//#pragma config DEBUG = ON     // In-Circuit Debugger enabled, ICSPCLK and ICSPDAT are dedicated to the debugger
#pragma config LPBOR = ON       // Low-Power Brown-out Reset is enabled
#pragma config BORV = HI        // Brown-out Reset voltage (VBOR), high trip point selected
#pragma config STVREN = ON      // Stack Overflow or Underflow will cause a Reset
#pragma config PLLEN = ON       // 4xPLL enabled
#pragma config ZCDDIS = ON      // Zero-cross detection is disabled on POR. can be controlled by software
#pragma config PPS1WAY = ON     // The PPSLOCK bit is permanently set after the first access sequence that sets it
#pragma config WRT = OFF        // Write protection off

// DEFINE TIMER
#define WAIT_BOOT_TIMER 10      // after rebooting, wait for 10s
#define WDT_TIMER       2       // Watchdog Reboot timer
#define PROTOCOL_TIMER  120     // Protocol Error Reboot timer
#define TEMP_TIMER      1       // Temp Check timer

U08 DSP_RESET(void)
{
    U08 bReset = 0;
    U08 bChk_wd_en = 0;
    U16 uWaitTimer = 0;
    
    // 1, Main Power Enable
    pwr_main_ctrl(POWER_ON);
    // 2. Pmic Power Enable
    pwr_pmic_ctrl(POWER_ON);
    // 3. Reboot DSP
    pwr_dsp_reset();
    
    for ( uWaitTimer = 0; uWaitTimer < WAIT_BOOT_TIMER; uWaitTimer++ )
    {
        bChk_wd_en = pwr_wdt_enable_read();
        // On Kernel, Watchdog Enable Pin (Low -> High)
        if ( bChk_wd_en != WDT_ACTIVE)
        {
            bReset = 1;
            return bReset;
        }
        __delay_ms(1000);
        asm("CLRWDT");
    }
    // NO REBOOT
    pwr_pmic_ctrl(POWER_OFF);
    
    return bReset;
}

U08 CheckWatchDog(void)
{
    U08 bError = 0;
    U08 bChk_wd_en, bChk_wd_clk_cur;
    static U08 Chk_wd_clk_pre = 0;
    
    bChk_wd_en = pwr_wdt_enable_read();    
    if ( bChk_wd_en == WDT_ACTIVE )
    {
        bChk_wd_clk_cur = pwr_wdt_clock_read();
        if ( Chk_wd_clk_pre == bChk_wd_clk_cur )
        {
            bError = 1;
        }
        Chk_wd_clk_pre = bChk_wd_clk_cur;
    }
    
    return bError;
}


void main(void)
{
    // Init Prepheral
    osc_init();
    gpio_init();
    adc_init();
    timer_init();
    uart_init();
    // PEIE: Peripheral Interrupt Enable bit
    //  1 = Enables all active peripheral interrupts
    //  0 = Disables all peripheral interrupts
    INTCONbits.PEIE = 1;
    // GIE: Global Interrupt Enable bit
    //  1 = Enables all active interrupts
    //  0 = Disables all interrupts
    INTCONbits.GIE = 1;
    // Encryption Init
    Jtp_comm_init();
    
    // Init Variable
    U32 IMainSystemTick = 0;
    
    U16 uWdtCnt = 0;
    U16 uProcErrCnt = 0;
    U16 uTempCnt = 0;
    U16 uPowerCommand = POWER_STATE_READY;
    U16 uWatchdogFireSec = PROTOCOL_TIMER;
    
    U08 main_roop = 1;
    U08 bProtocolStatus = 0;
    U08 bChkTemp = 0;
    U08 bChkIg = 0;
    
    while ( main_roop)
    {
        // Clear watchdog counter(4ms * 1025 postscaler = 4.096s)
         asm("CLRWDT");
         IMainSystemTick = gulSystemTick;
        ////////////////////////////////////////////////////////////////////////
        
        ///////////////////////////////////////////////////
        // DSP Watchdog Reset
        ///////////////////////////////////////////////////
         if ( CheckWatchDog() ) uWdtCnt++; // per 10ms
         else                   uWdtCnt = 0;
         
         if ( uWdtCnt > (WDT_TIMER*100) )
         {
             uWdtCnt = 0;
             DSP_RESET();
             uPowerCommand = POWER_STATE_READY;
         }
         
        ///////////////////////////////////////////////////
        // JTP Protocol
        ///////////////////////////////////////////////////
         if ( Jtp_Protocol() )
         {
             uProcErrCnt = 0;
             uPowerCommand = Jtp_Get_PowerCommand();
             uWatchdogFireSec = Jtp_Get_WatchDogFireSec();
         }
         else
         {
             if ( uPowerCommand != POWER_STATE_READY )
             {
                 uProcErrCnt++; // per 10ms
             }
         }
         
          if ( uProcErrCnt > (uWatchdogFireSec*100) )
          {
              uProcErrCnt = 0;
              while(1); // MCU watchdog reset (HW reset)
          }
         
        ///////////////////////////////////////////////////
        // DSP Power Command
        ///////////////////////////////////////////////////
         switch ( uPowerCommand )
         {
             case POWER_STATE_READY:
                 pwr_main_ctrl(POWER_ON);
                 break;
             case POWER_STATE_PARKING:
             case POWER_STATE_ON:
                 pwr_main_ctrl(POWER_ON);
                 pwr_pmic_ctrl(POWER_OFF);
                 
                 break;
             case POWER_STATE_OFF:
                 pwr_main_ctrl(POWER_OFF);
                 pwr_pmic_ctrl(POWER_OFF);
                 
                 break;
             case POWER_STATE_REBOOT:
                 pwr_main_ctrl(POWER_ON);
                 pwr_pmic_ctrl(POWER_ON);
                 
                 break;
             case POWER_STATE_SUSPEND:
                 pwr_main_ctrl(POWER_ON);
                 pwr_pmic_ctrl(POWER_OFF);
                 
                 while(1)
                 {
                    bChkTemp = pwr_chk_Temp();
                    bChkIg = pwr_chk_IG();
                    if ( bChkTemp == 1 )  uTempCnt++;
                    else                  uTempCnt = 0;

                    if ( (uTempCnt > TEMP_TIMER*10) || (bChkIg == 1) )
                    {
                        uTempCnt = 0;
                        break;
                    }
                    
                    __delay_ms(100);
                    asm("CLRWDT");     
                 }
                 uPowerCommand = POWER_STATE_READY;
                 break;
             case POWER_STATE_MCU_RESET:
                 pwr_main_ctrl(POWER_OFF);
                 pwr_pmic_ctrl(POWER_OFF);
                 while(1); // MCU watchdog reset (HW reset)
                 
                 break;
             default:
                 break;
         }

        ////////////////////////////////////////////////////////////////////////
        while ( IMainSystemTick == gulSystemTick )  asm("NOP");
    }
}