/////////////////////////////////////////////////////////
//
//  File name : app_version.h
//	Author    : YSW
//  Date      : 2015.08.06
//
//  v1.0.0 : initial version
//  v2.0.0 : EOD version - SPI communication
//      1. COMMAND 1) READY : Send MCU version
//                 2) SEND_STATE3 : Send MCU data (ADC Value)
//      2. WD_EN : WD_EN Pin is LOW, check WD_CLK Pin is ticking
//  v2.0.1 : SPI Error Rate down - removed spibuf = 0, when received data 
//  v2.1.0 : First Release Version
//  v2.2.0 : WD_CLK pin is not ticking for 1s -> 10s(10ms x 10000). Then reset dsp
//           dsp_boot_on Count Bug modification
//
//  v2.3.0 : uart port open for check mcu version by PC tool
//
/////////////////////////////////////////////////////////
#ifndef APP_VERSION_H
#define	APP_VERSION_H

#define APP_VERSION 230


unsigned char R7_MCU_VERSION[16] = "v230";


#endif	/* APP_VERSION_H */

