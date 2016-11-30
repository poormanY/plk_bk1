//
// File   : opx_mcu_version.h
// Author : YSW
// Created on 2016.04.14
//
// Brief : version indicator
// Detail : define current version, modificated date, details of each versions
//

///////////////////////////////////////////////////////////////////////////////
// ver.1.0.0
// date : 2016.04.14
// circuit diagram : OPX SUB - T2 (2016.03.14)
// opx version : ***
// detail : add function to be used for opx_mcu
//        1. uart communication for opx application (*used JTP Protocol)
//        2. read adc value to transmit to opx (*V-ref 1.8v : RA3/AN3)
//          RA0/AN0 : TURN_L_MCU
//          RA1/AN1 : TURN_R_MCU
//          RB2/AN8 : BRAKE_MCU
//          RB3/AN9 : IG CHK_MCU
//          RB4/AN11 : B+ CHK_MCU
//          RB5/AN13 : TEMP_CHK_MCU
//        3. read watch-dog enable pin
//          RB1 : WD_EN (High enable -> count)
//          RA6 : WD_CLOCK (--__--__--__)
//        4. opx power control (scenario)
//          RC0 : MAIN_PWR_EN_MCU (for Parking Mode)
//          RC1 : PMIC_INPUT_PWR_EN_MCU (power control for opx)
//          RC2 : nDSP_RESET (opx reset)
//        5. count tick for 1s (speed value)
//          RA4/T0CK1 : SPEED_MCU (use TMR0)
//
// ver.1.0.1
// date : 2016.05.04
// detail :
//        1. Add action each OPX Command 
//        2. V+ REF used to FVC 2.048V
//
// ver.1.0.2
// date : 2016.05.11
// detail :
//        1. fix uPowerCommand error
//        2. Use opx_static_info received from OPX
//        3. add uPowerCommand - Parking mode
//          
// ver.1.0.3
// date : 2016.05.13
// detail :
//        1. fix Power Command Reboot and Power Command init Power-On when cmd_ready is sent
//
// ver.1.0.4
// date : 2016.05.16
// detail :
//        1. define DSP_FIRST_REBOOT, DSP_REBOOT 
//
// ver.1.0.5
// date : 2016.05.25
// detail :
//        1. fix uart tx
//        2. fix reboot as not booting for 2minutes
//
// ver.1.0.6
// date : 2016.06.09
// detail :
//        1. add adcconvert.c
//
// ver.1.0.7
// date : 2016.06.13
// detail :
//        1. nDSP_RESET sets High (gpio.c)
//        2. check jtp protocol for 50ms (<-200ms)
//
// ver.1.0.8
// date : 2016.06.21
// detail :
//        1. fix speed pulse intelligently (sum 100ms * 10 before sending msg)
//
// ver.1.0.9
// date : 2016.06.21
// detail :
//        1. fix first reboot
//          - if Bplus is off for a while, no reboot
//
// ver.1.1.0
// date : 2016.06.27
// detail :
//        1. fix reboot
//          - add pwr_chk_wdt_count()
//
// ver.1.1.1
// date : 2016.06.28
// detail :
//        1. bFirstReboot = DSP_FIRST_REBOOT();
//          - check fist reboot status, when power off
//
// ver.1.1.2
// date : 2016.08.02
// detail :
//        1. fix first reboot 2times --__-__---
//          - add pwr_count_clear()
//
// ver.1.1.3
// date : 2016.08.12
// detail :
//        1. revive reboot when power is off
//
// ver.1.1.4
// date : 2016.08.26
// detail :
//        1. add delay(1000ms) on power off logic 
//
// ver.2.0.0
// date : 2016.09.12
// detail :
//        1. New DSP - Active Low
//
// ver.3.0.0
// date : 2016.09.12
// detail :
//        1. Active High 
//
// ver.3.0.1
// date : 2016.09.27
// detail :
//        1. Remake Boot up
//
// ver.3.0.2
// date : 2016.09.30
// detail :
//        1. fix WDT reboot bug
//           Uart Comm Disable for 1s after connecting -> watchdog reset
//           Power Off -> bFirstReboot = 0
//
// ver.3.0.3
// date : 2016.10.06
// detail :
//        1. use watchdog_timer from DSP
//        2. when comm is disable, reset (micom watchdog reset)
//                        pwr_main_ctrl(POWER_OFF);
//                        pwr_pmic_ctrl(POWER_OFF);
//                        while(1); -> watchdog reset
//
// ver.3.0.4
// date : 2016.10.10
// detail :
//        1. add Command [Watchdog Reset]
//
// ver.2.0.5
// date : 2016.10.27
// detail : fix reset bug when power on
//          1. case POWER_STATE_READY : //pwr_pmic_ctrl(POWER_ON)
//          2. RC2 - OUT : nDSP_RESET PULL UP enable
//
// ver.2.0.6
// date : 2016.11.01
// detail : delete "uOpxPowerState = POWER_STATE_ON" when cmd is readey
//
// ver.2.0.7
// date : 2016.11.07
// detail : 
//          1. add bBootUpCnt on Reset
//
// ver.2.0.8
// date : 2016.11.11
// detail : 
//          1. bBootUpCnt 6s
//          2. watchdog time 5s
//
// ver.2.0.9
// date : 2016.11.25
// detail : ***remake***
//          
//
///////////////////////////////////////////////////////////////////////////////

#ifndef OPX_MCU_VERSION_H
#define	OPX_MCU_VERSION_H

#define OPX_MCU_VERSION 209;
#define WDT_ACTIVE LOW

#endif	/* OPX_MCU_VERSION_H */

