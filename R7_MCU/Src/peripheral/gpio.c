#include <xc.h>
#include "gpio.h"

void gpio_init(void)
{
    // 0 : output, 1 : input

    // Bit7 : Not used 			: IN
    // Bit6 : Not used 			: IN
    // Bit5 : DSP_SP1_SS    	: IN
    // Bit4 : SPEED_PULSE 		: IN
    // Bit3 : REAR_LAMP         : AD
    // Bit2 : IG_CHK_MCU        : AD
    // Bit1 : TURN_L 			: AD
    // Bit0 : TURN_R            : AD
    TRISA = 0b11111111;
    PORTA = 0b00000000;
    WPUA = 0b00000000;
	LATA = 0b00000000;

    // Bit7 : UART_EXT_RX2 		: IN
    // Bit6 : UART_EXT_TX2 		: OUT
    // Bit5 : Not used 			: IN
    // Bit4 : Not used 			: IN
    // Bit3 : WIPER_IN			: AD
    // Bit2 : DSP0_RESET        : OUT
    // Bit1 : WD_EN 			: IN
    // Bit0 : WD_CLK 			: IN - tick
    TRISB = 0b10111011;
    PORTB = 0b00000100;
    WPUB = 0b00000000;
	LATB = 0b00000000;

    // Bit7 : UART_FALCO_RX1    : IN
    // Bit6 : UART_FALCO_TX1    : OUT
    // Bit5 : DSP_SPI1_MISO		: OUT
    // Bit4 : DSP_SPI1_MOSI		: IN
    // Bit3 : DSP_SPI1_CLK      : IN
    // Bit2 : MAIN_PWR_EN_MCU   : OUT
    // Bit1 : PMIC_INPUT_PEW_EN : OUT
    // Bit0 : TURN_R 			: IN
    TRISC = 0b10011001;
    PORTC = 0b00100110;
    WPUC = 0b00000000;
	LATC = 0b00000000;

    PEIE 	= 1;//Peripheral Interrupt Enable bit
    GIE  	= 1;//Global Interrupt Enable bit
}

