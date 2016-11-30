//
// File   : adc_proc.c
// Author : YSW
// Created on 2016.04.21
//
// Brief : ADC Protocol
// Detail :
//
#include <xc.h>
#include "def_var.h"
#include "adc_proc.h"
#include "adc.h"
#include "jtp.h"

U08 adc_proc(MCU_DYNAMIC_INFO *pMcuDynamicInfo)
{
    pMcuDynamicInfo->uBplus     = adc_read(ADC_ID_B_PLUS);
    pMcuDynamicInfo->uIg        = adc_read(ADC_ID_IG);
    pMcuDynamicInfo->uTemp      = adc_read(ADC_ID_TEMP);
    pMcuDynamicInfo->uTurnLeft  = adc_read(ADC_ID_TURN_L);
    pMcuDynamicInfo->uTurnRight = adc_read(ADC_ID_TURN_R);
    pMcuDynamicInfo->uBrake     = adc_read(ADC_ID_BRAKE);
    
    return 1;
}