//
// File   : gpio.c
// Author : YSW
// Created on 2016.04.14
//
// Brief : GPIO Control
// Detail : OPX SUB - T2 (2016.03.14)
//
#include <xc.h>
#include "gpio.h"

// I/O Ports, Pull-up, Data Latch
// TRIS register (data direction register : 1 input, 0 output)
// PORT register (input value - reads the levels on the pin)
// LAT register (output latch)
// WPU register (pull up or down : 1 enable, 0 disable)
void gpio_init(void)
{
    // RA7 - IN  : Reserve1
    // RA6 - IN  : Reserve0 (=> OPX_WD_CLK)
    // RA5 - IN  : Reserved (DSP_SPI1_SS)
    // RA4 - IN  : SPEED_MCU
    // RA3 - IN  : VDD_1V8
    // RA2 - IN  : GROUND
    // RA1 - IN  : TURN_R_MCU
    // RA0 - IN  : TURN_L_MCU
	TRISA = 0b11111111;
    PORTA = 0b00000000;
	WPUA  = 0b00000000;
	LATA  = 0b00000000;

    // RB7 - IN  : ICSPDAT (DEBUG)
    // RB6 - IN  : ICSPCLK (DEBUG)
    // RB5 - IN  : TEMP_CHK_MCU
    // RB4 - IN  : B+_CHK_MCU
    // RB3 - IN  : IG_CHK_MCU
    // RB2 - IN  : BRAKE_MCU 
    // RB1 - IN  : WD_EN 
    // RB0 - IN  : Reserved (WatchDog CLK)
	TRISB = 0b11111111;
    PORTB = 0b00000000;
	WPUB  = 0b00000000;
	LATB  = 0b00000000;

    // RC7 - IN  : UART RX
    // RC6 - OUT : UART TX
    // RC5 - OUT : Reserved (DSP_SPI1_MISO)
    // RC4 - IN  : Reserved (DSP_SPI1_MOSI)
    // RC3 - IN  : Reserved (DSP_SPI1_CLK)
    // RC2 - OUT : nDSP_RESET (PULL UP)
    // RC1 - OUT : PMIC_INPUT_PWR_EN_MCU
    // RC0 - OUT : MAIN_PWR_EN_MCU
	TRISC = 0b10011000;
    PORTC = 0b00000100;
	WPUC  = 0b00000000;
	LATC  = 0b00000100;
}