//
// File   : osc.c
// Author : YSW
// Created on 2016.04.14
//
// Brief : OSCILLATOR CONTROL REGISTER
// Detail :
//
#include <xc.h>
#include "osc.h"

// Oscillator Control
// Internal Oscillator Frequency sets 32MHz
void osc_init(void)
{
    // SPLLEN: Software PLL Enable bit
    // If PLLEN in Configuration Words = 1:
    //  SPLLEN bit is ignored. 4x PLL is always enabled (subject to oscillator requirements)
    // If PLLEN in Configuration Words = 0:
    //  1 = 4x PLL Is enabled
    //  0 = 4x PLL is disabled    
    OSCCONbits.SPLLEN = 1;
    
    // IRCF<3:0>: Internal Oscillator Frequency Select bits
    // 1111 = 16 MHz HF
    // 1110 = 8 MHz or 32 MHz HF(2)
    // 1101 = 4MHz HF
    // 1100 = 2MHz HF
    // 1011 = 1MHz HF
    // 1010 = 500kHz HF(1)
    // 1001 = 250kHz HF(1)
    // 1000 = 125kHz HF(1)
    // 0111 = 500 kHz MF (default upon Reset)
    // 0110 = 250kHz MF
    // 0101 = 125kHz MF
    // 0100 = 62.5kHz MF
    // 0011 = 31.25kHz HF(1)
    // 0010 = 31.25kHz MF
    // 000x = 31kHz LF
    OSCCONbits.IRCF = 0b1110;
    
    // SCS<1:0>: System Clock Select bits
    // 1x = Internal oscillator block
    // 01 = Secondary oscillator
    // 00 = Clock determined by FOSC<2:0> in Configuration Words
    OSCCONbits.SCS = 0b00;
}