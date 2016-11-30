//
// File   : adc.c
// Author : YSW
// Created on 2016.04.14
//
// Brief : ADC Module
// Detail : Analog-to-Digital Converter Module
//
#include <xc.h>
#include "adc.h"
#include "def_var.h"
#include "delay.h"

#define ADC_FVR_MODE

enum ADC_REF_tag
{
    VREF_VDD = 0b00,
    VREF_PIN = 0b10,
    VREF_FVR = 0b11
};
enum FVR_REF_tag
{
    FVR_1024mV = 0b00,
    FVR_2048mV = 0b10,
    FVR_4096mV = 0b11
};

void adc_fvr_init(void)
{
    // FVREN: Fixed Voltage Reference Enable bit
    // 1 = Fixed Voltage Reference is enabled
    // 0 = Fixed Voltage Reference is disabled
    FVRCONbits.FVREN = 1;
    // ADFVR<1:0>: ADC FVR Buffer Gain Selection bit
    // 11 = ADC FVR Buffer Gain is 4x, with output VADFVR = 4x VFVR(2) => 4.048v
    // 10 = ADC FVR Buffer Gain is 2x, with output VADFVR = 2x VFVR(2) => 2.048v
    // 01 = ADC FVR Buffer Gain is 1x, with output VADFVR = 1x VFVR    => 1.024v
    // 00 = ADC FVR Buffer is off
    FVRCONbits.ADFVR = FVR_2048mV;
}

void adc_init(void)
{
    // ADON: ADC Enable bit
    //  1 = ADC is enabled
    //  0 = ADC is disabled and consumes no operating current
	ADCON0bits.ADON = 0;
    
    // * default value is 1, in other words default setting of pin is analog input
    // ANSA<5:0>: Analog Select between Analog or Digital Function on Pins RA<2:0>, respectively
    //  1 = Analog input. Pin is assigned as analog input(1). Digital input buffer disabled.
    //  0 = Digital I/O. Pin is assigned to port or digital special function.
    // RA1 - IN  : TURN_R_MCU
    // RA0 - IN  : TURN_L_MCU
    ANSELA = 0b00000011;
    // ANSB<5:0>: Analog Select between Analog or Digital Function on Pins RB<5:4>, respectively
    //  0 = Digital I/O. Pin is assigned to port or digital special function.
    //  1 = Analog input. Pin is assigned as analog input(1). Digital input buffer disabled.
    // RB5 - IN  : TEMP_CHK_MCU
    // RB4 - IN  : B+_CHK_MCU
    // RB3 - IN  : IG_CHK_MCU
    // RB2 - IN  : BRAKE_MCU
	ANSELB = 0b00111100;
    // ANSC<7:2>: Analog Select between Analog or Digital Function on Pins RC<7:0>, respectively(1)
    //  0 = Digital I/O. Pin is assigned to port or digital special function.
    //  1 = Analog input. Pin is assigned as analog input(1). Digital input buffer disabled.
	ANSELC = 0b00000000;
    
    // ADFM: ADC Result Format Select bit
    //  1 = Right justified. Six Most Significant bits of ADRESH are set to ?0? when the conversion result is loaded.
    //  0 = Left justified. Six Least Significant bits of ADRESL are set to ?0? when the conversion result is loaded.
    ADCON1bits.ADFM = 1;    //Right justified
    
    // ADCS<2:0>: ADC Conversion Clock Select bits
    //  111 = FRC (clock supplied from an internal RC oscillator)
    //  110 = FOSC/64
    //  101 = FOSC/16
    //  100 = FOSC/4
    //  011 = FRC (clock supplied from an internal RC oscillator)
    //  010 = FOSC/32
    //  001 = FOSC/8
    //  000 = FOSC/2     
 #ifdef ADC_FVR_MODE   
    ADCON1bits.ADCS = 0b011;
#else
    ADCON1bits.ADCS = 0b010;  // 32MHz/32 = 1us
#endif
    
    // ADNREF: A/D Negative Voltage Reference Configuration bit
    //  0 = VREF- is connected to VSS
    //  1 = VREF- is connected to VREF- pin
    ADCON1bits.ADNREF = 0;
    
    // ADPREF<1:0>: ADC Positive Voltage Reference Configuration bits
    //  11 = VREF+ is connected to internal Fixed Voltage Reference (FVR) module(1)
    //  10 = VREF+ is connected to external VREF+ pin(1)
    //  01 = Reserved
    //  00 = VREF+ is connected to VDD
#ifdef ADC_FVR_MODE
    ADCON1bits.ADPREF = VREF_FVR;
    adc_fvr_init();
#else
    ADCON1bits.ADPREF = VREF_PIN;
#endif
}

U16 adc_read(U08 ch)
{    
    if ( ch > 31 )  return 0;

    U16 uAdcValue = 0;
    ADRESH = 0;
    ADRESL = 0;
    
    ADCON0 = 0x00;
    // CHS<4:0>: Analog Channel Select bits
    //  11111 = FVR (Fixed Voltage Reference) Buffer 1 Output(2)
    //  11110 = DAC1_output(1)
    //  11101 = Temperature Indicator(3)
    //  11100 = DAC2_output(5)
    //  11011 = AN27(4)
    //  11010 = AN26(4)
    //  11001 = AN25(4)
    //  11000 = AN24(4)
    //  10111 = AN23(4)
    //  10110 = AN22(4)
    //  10101 = AN21(4)
    //  10100 = AN20(4)
    //  10011 = AN19
    //  10010 = AN18
    //  10001 = AN17
    //  10000 = AN16
    //  01111 = AN15
    //  01110 = AN14
    //  01101 = AN13
    //  01100 = AN12
    //  01011 = AN11
    //  01010 = AN10
    //  01001 = AN9
    //  01000 = AN8
    //  00111 = AN7(4)
    //  00110 = AN6(4)
    //  00101 = AN5(4)
    //  00100 = AN4
    //  00011 = AN3
    //  00010 = AN2
    //  00001 = AN1
    //  00000 = AN0
    ADCON0bits.CHS = ch;
    // ADON: ADC Enable bit
    //  1 = ADC is enabled
    //  0 = ADC is disabled and consumes no operating current
	ADCON0bits.ADON = 1;
    // ADC Acquisition Requirements
    //  Tacq = Amplifier Settling Time + Hold Capacitor Charging Time + Temperature Coefficient
    //       = Tamp + Tc + Tcoff
    //       = 2us + -CHOLD(Ric + Rss + Rs)ln(1/2047) + (Temperature - 25)*(0.05us)
    //       = 2us + 892ns + (100-25)*(0.05us)
    //       = 6.642us
    __delay_us(6);
    
    // GO/DONE: ADC Conversion Status bit
    //  1 = ADC conversion cycle in progress. Setting this bit starts an ADC conversion cycle.
    //   This bit is automatically cleared by hardware when the ADC conversion has completed.
    //  0 = ADC conversion completed/not in progress
    ADCON0bits.GO_nDONE = 1;
    while(ADCON0bits.GO_nDONE);
    
    //ADCON1bits.ADFM = 0 -> Left justified
    //uAdcValue = (U16)( ((ADRESH & 0xFF)<<2) | ((ADRESL & 0x60)>>>6) );
    //ADCON1bits.ADFM = 1 -> Right justified
    uAdcValue = (U16)( ((ADRESH & 0x03)<<8) | (ADRESL & 0xFF) );
    ADCON0bits.ADON = 0;
    
    return uAdcValue;
}