//
// File   : adc_proc.h
// Author : YSW
// Created on 2016.04.21
//
// Brief :
// Detail :
//
#ifndef ADC_PROC_H
#define	ADC_PROC_H

#include "def_var.h"
#include "jtp.h"

//          RA0/AN0 : TURN_L_MCU
//          RA1/AN1 : TURN_R_MCU
//          RB2/AN8 : BRAKE_MCU
//          RB3/AN9 : IG CHK_MCU
//          RB4/AN11 : B+ CHK_MCU
//          RB5/AN13 : TEMP_CHK_MCU
enum ADC_ID
{
    ADC_ID_TURN_L = 0x00,   // AN0
    ADC_ID_TURN_R = 0x01,   // AN1
    ADC_ID_BRAKE  = 0x08,   // AN8
    ADC_ID_IG     = 0x09,   // AN9
    ADC_ID_B_PLUS = 0x0B,   // AN11
    ADC_ID_TEMP   = 0x0D,   // AN13
    ADC_ID_MAX
};

extern U08 adc_proc(MCU_DYNAMIC_INFO *pMcuDynamicInfo);

#endif	/* ADC_PROC_H */

