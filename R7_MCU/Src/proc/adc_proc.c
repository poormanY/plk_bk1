#include <xc.h>
#include <string.h>
#include "adc_proc.h"
#include "../peripheral/adc.h"
#include "../proc/jtp_proc.h"

#define	USE_ADC_TO_TURN_SIGNAL

static ADC_INFO     g_stAdcInfo;

void adc_proc_init(void)
{
    adc_init();
}

void adc_proc2(void)
{
    // 12V in => ADC 1.2V => 420
    // 6V  in => ADC 0.6V => 210
    // 1V => 35
    U16 usAdcValue;
    U16 usTempValue;
    // Random Number for HIGHT Encryption
    g_stMcuData.uRandomNumber = adc_read(ADC_ID_IG_CHK_MCU);
    g_stMcuVersion.uRandomNumber = adc_read(ADC_ID_IG_CHK_MCU);
    // Speed Pulse
    g_stMcuData.uSpeedPulse = isr_get_car_pulse();  //g_car_pulse
    // Wiper signal
    g_stMcuData.uWiperIn = adc_read(ADC_ID_WIPER_IN);
    // Turn signal
    g_stMcuData.uTurnLeft = adc_read(ADC_ID_TURN_LEFT);
    g_stMcuData.uTurnRight = adc_read(ADC_ID_TURN_RIGHT);
    // IG Check signal
    g_stMcuData.uIgChkMcu = adc_read(ADC_ID_IG_CHK_MCU);   
    
    // Rear Lamp signal
    g_stMcuData.uRearLamp = adc_read(ADC_ID_REAR_LAMP);
    // Brake signal
    g_stMcuData.uBrake = adc_read(ADC_ID_BRAKE);
    // Temperature check
    usTempValue = 0;
    g_stMcuData.iTemperature = usTempValue;    
    
    if ( g_stMcuData.uWiperIn > 0
            || g_stMcuData.uSpeedPulse > 0
            || g_stMcuData.uTurnLeft > 0
            || g_stMcuData.uTurnRight > 0 )
    {
        usTempValue = 0;                
    }
}

ADC_INFO adc_proc_get_info(void)
{
    return g_stAdcInfo;
}