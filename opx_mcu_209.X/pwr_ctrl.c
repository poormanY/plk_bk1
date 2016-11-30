//
// File   : pwr_ctrl.c
// Author : YSW
// Created on 2016.04.20
//
// Brief : Power Control
// Detail :
//
#include <xc.h>
#include "def_var.h"
#include "pwr_ctrl.h"
#include "delay.h"
#include "adc.h"
#include "adc_proc.h"
#include "adcconvert.h"

// RA6 - IN  : Reserve0 (=> OPX_WD_CLK)
// RB1 - IN  : WD_EN 
#define WATCHDOG_CLK PORTAbits.RA6
#define WATCHDOG_EN  PORTBbits.RB1

// RC2 - OUT : nDSP_RESET
// RC1 - OUT : PMIC_INPUT_PWR_EN_MCU
// RC0 - OUT : MAIN_PWR_EN_MCU
#define DSP_RESET   LATCbits.LATC2
#define PMIC_PWR_EN LATCbits.LATC1
#define MAIN_PWR_EN LATCbits.LATC0

static U16 uAdcBplus_ref = 0;
static U16 uWakeupTemp_ref = 55;

void set_adc_bplus_ref(U16 uAdcRef)
{
    uAdcBplus_ref = uAdcRef;
}

void set_wakeup_temp_ref(U16 uTempRef)
{
    uWakeupTemp_ref = uTempRef;
}


void pwr_main_ctrl(U08 ctrl)
{
    MAIN_PWR_EN = ctrl;
}
void pwr_pmic_ctrl(U08 ctrl)
{
    PMIC_PWR_EN = ctrl;
}

void pwr_dsp_reset_ctrl(U08 ctrl)
{
    DSP_RESET = ctrl;
}

void pwr_dsp_reset(void)
{
    DSP_RESET = 0;
    __delay_ms(500);
    DSP_RESET = 1;
}

U08 pwr_wdt_enable_read(void)
{    
    return WATCHDOG_EN;
}

U08 pwr_wdt_clock_read(void)
{
    return WATCHDOG_CLK;
}

U08 pwr_chk_IG(void)
{
    U08 bChk_IG = 0;
    U16 uAdc_IG = 0;
    
    uAdc_IG = adc_read(ADC_ID_IG);
    ( uAdc_IG > uAdcBplus_ref ) ? bChk_IG=1 : bChk_IG=0;
    
    return bChk_IG;
}

U08 pwr_chk_Bplus(void)
{
    U08 bChk_Bplus = 0;
    U16 uAdc_Bplus = 0;
    
    uAdc_Bplus = adc_read(ADC_ID_B_PLUS);
    ( uAdc_Bplus > uAdcBplus_ref ) ? bChk_Bplus=1 : bChk_Bplus=0;
    
    return bChk_Bplus;
}

// when temp is over uWakeupTemp_ref, return 0
U08 pwr_chk_Temp(void)
{
    U08 bTempCelsius = 0;
    U08 bChk_Temp = 0;
    U16 uAdc_Temp = 0;
    
    uAdc_Temp = adc_read(ADC_ID_TEMP);
    
    bTempCelsius = mcu_adcvalue_to_temp(uAdc_Temp);
    ( bTempCelsius > uWakeupTemp_ref ) ? bChk_Temp=0 : bChk_Temp=1;
    
    return bChk_Temp;
}