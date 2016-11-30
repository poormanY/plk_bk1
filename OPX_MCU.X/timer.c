//
// File   : timer.c
// Author : YSW
// Created on 2016.04.14
//
// Brief : Timer Module
// Detail : 
//  1. Timer0 Module : 8-BIT COUNTER MODE
//  2. Timer1 Module : 16-BIT TIMER MODE - 1us * (10000) = 10ms
//
#include <xc.h>
#include "timer.h"

void timer_init(void)
{
    ///////////////////////////////////////////////////////////////////////////
    // Timer0 Module : 8-BIT COUNTER MODE
    //  In 8-Bit Counter mode, the Timer0 module will increment 
    // on every rising or falling edge of the T0CKI pin.
    ///////////////////////////////////////////////////////////////////////////
    // TMR0CS: Timer0 Clock Source Select bit
    //  1 = Transition on T0CKI pin
    //  0 = Internal instruction cycle clock (FOSC/4)
    OPTION_REGbits.TMR0CS = 1;
    ANSELAbits.ANSA4 = 0;   // T0CK1 Pin
    // TMR0SE: Timer0 Source Edge Select bit
    //  1 = Increment on high-to-low transition on T0CKI pin
    //  0 = Increment on low-to-high transition on T0CKI pin
    OPTION_REGbits.TMR0SE = 0;
    
    // WPUEN: Weak Pull-Up Enable bit
    //  1 = All weak pull-ups are disabled (except MCLR, if it is enabled)
    //  0 = Weak pull-ups are enabled by individual WPUx latch values
    OPTION_REGbits.nWPUEN = 0;
    // INTEDG: Interrupt Edge Select bit
    //  1 = Interrupt on rising edge of INT pin
    //  0 = Interrupt on falling edge of INT pin
    OPTION_REGbits.INTEDG = 0;
    // PSA: Prescaler Assignment bit
    //  1 = Prescaler is not assigned to the Timer0 module
    //  0 = Prescaler is assigned to the Timer0 module
    OPTION_REGbits.PSA = 1;
    // PS<2:0>: Prescaler Rate Select bits
    //  000  1 : 2
    //  001  1 : 4
    //  010  1 : 8
    //  011  1 : 16
    //  100  1 : 32
    //  101  1 : 64
    //  110  1 : 128
    //  111  1 : 256
    OPTION_REGbits.PS = 0b000;
    
    // TMR0IF: Timer0 Overflow Interrupt Flag bit
    //  1 = TMR0 register has overflowed
    //  0 = TMR0 register did not overflow
	TMR0IF = 0;
    // TMR0IE: Timer0 Overflow Interrupt Enable bit
    //  1 = Enables the Timer0 interrupt
    //  0 = Disables the Timer0 interrupt
	TMR0IE = 1;
	TMR0 = 0xFF;

    
    ///////////////////////////////////////////////////////////////////////////
    // Timer1 Module : 16-BIT TIMER MODE
    //  16-bit timer (TMR1H:TMR1L)
    ///////////////////////////////////////////////////////////////////////////
    // TMR1CS<1:0>: Timer1 Clock Source Select bits
    //  11 = LFINTOSC
    //  10 = Timer1 clock source is pin or oscillator:
    //  If T1OSCEN = 0:
    //  External clock from T1CKI pin (on the rising edge)
    //  If T1OSCEN = 1:
    //  Crystal oscillator on SOSCI/SOSCO pins
    //  01 = Timer1 clock source is system clock (FOSC)
    //  00 = Timer1 clock source is instruction clock (FOSC/4)
    T1CONbits.TMR1CS = 0b00;    // 32MHz/4 = 8MHz
    // T1CKPS<1:0>: Timer1 Input Clock Prescale Select bits
    // 11 = 1:8 Prescale value
    // 10 = 1:4 Prescale value
    // 01 = 1:2 Prescale value
    // 00 = 1:1 Prescale value
    T1CONbits.T1CKPS = 0b11;    // 8MHz/8 = 1MHz = 1us
    
    // T1OSCEN: LP Oscillator Enable Control bit
    //  1 = Dedicated secondary oscillator circuit enabled
    //  0 = Dedicated secondary oscillator circuit disabled
    T1CONbits.T1OSCEN   = 0;
    // T1SYNC: Timer1 Synchronization Control bit
    //  1 = Do not synchronize asynchronous clock input
    //  0 = Synchronize asynchronous clock input with system clock (FOSC)
    T1CONbits.nT1SYNC   = 0;
    
    TMR1IF = 0;
    TMR1IE = 1;
    
    // 1us * (10000) = 10ms
    // 0xFFFF - 0x2710(10000) + 1 = 0xD8F0
    TMR1 = 0xD8F0;
    // TMR1ON: Timer1 On bit
    //  1 = Enables Timer1
    //  0 = Stops Timer1 and clears Timer1 gate flip-flop
 	TMR1ON = 1;
}