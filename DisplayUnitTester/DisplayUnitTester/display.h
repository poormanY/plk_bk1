/////////////////////////////////////////////////////////
//
//  File name : display.h
//	Author    : YSW
//  Date      : 2015.08.31
//
/////////////////////////////////////////////////////////

#ifndef DISPLAY_H
#define	DISPLAY_H

#include "def_var.h"
#include "jtp.h"

/////////////////////////////////////////////////////
//BUTTON STATUS
/////////////////////////////////////////////////////
#define BTN_DEFAULT 0
#define FUNC_OFF    1
#define VOL_UP      2
#define VOL_DOWN    3
#define VOL_UPnDOWN    4

/////////////////////////////////////////////////////
//CMD_SEND_ADAS HUB INFO
/////////////////////////////////////////////////////
#define DISPLAY_ON           0x01

#define DEVICE_ON            0x01
#define DEVICE_INSTALL_MODE  0x02

#define GPS_STATUS_INVALID   0x08
#define GPS_STATUS_VALID     0x10
#define GPS_STATUS_SPEED     0x20
#define GPS_STATUS_OK        0x30
#define DEVICE_ERROR         0x40

#define ADAS_LANE_DETECT     0x01
#define ADAS_LANE_LEFT_WARN  0x04
#define ADAS_LANE_RIGHT_WARN 0x08
#define ADAS_LANE_NO_DISPLAY_DETECT 0x20
#define ADAS_LANE_ERROR		 0x40


#define ADAS_PD_DETECT       0x01
#define ADAS_PD_WARN         0x02

#define ADAS_FCW_HMW_DETECT  0x0001
#define ADAS_FCW_HMW_WARN    0x0002
#define ADAS_FCW_HMW_WARN2    0x0004
#define ADAS_FCW_HMW_WARN3    0x0008
#define ADAS_FCW_FCW_WARN    0x0010
#define ADAS_FCW_VB_WARN     0x0020
#define ADAS_FCDA_RUNNING    0x0040
#define ADAS_FCDA_DETECT     0x0080
#define ADAS_FCDA_WARN       0x0100

#define ADAS_HBA_ON          0x0001
#define ADAS_HBA_OFF         0x0002

#define ADAS_TSR_KPH         0x00FF
#define ADAS_TSR_ON          0xFF00

#define ADAS_BRAKE_ON        0x01
#define ADAS_TURN_LEFT_ON    0X02
#define ADAS_TURN_RIGHT_ON   0X04
#define ADAS_SIGNAL_DISPLAY  0x20

#define ADAS_MODE_DAY_NIGHT  0x08
#define ADAS_MODE_DAY        0x00
#define ADAS_MODE_NIGHT      0x08

#define ADAS_MODE_SAVING     0x10

#define DISPLAY_ADAS_WARNING ( (hub_info.bLaneDetectState & 0xFF)      || \
                             (hub_info.uFcwState & ~ADAS_FCDA_RUNNING) || \
                             (hub_info.bPdState & 0xFF)                || \
                             (hub_info.bTsrOverSpd & 0XFF)             || \
                             (hub_info.bDeviceState & DEVICE_ERROR) )

// Segment LED indicates 0~9
#define MAX_TTC_SEGMENT_TBL     12
#define MAX_WAIT_SEGMENT_TBL    7

const U08 arbTTcSegmentTbl[MAX_TTC_SEGMENT_TBL] =
{
	0x3F ,	//0 | dot
	0x06 ,	//1
	0x5B ,	//2
	0x4F ,	//3
	0x66 ,	//4
	0x6D ,	//5
	0x7C ,	//6
	0x27 ,	//7
	0x7F ,	//8
	0x67 ,  //9
    0x00 ,  //Null
    0x40 ,  // -
};

const U08 arbWaitingSegmentTbl[MAX_WAIT_SEGMENT_TBL] =
{
    0x00,   //Null
	0x01,	//A
	0x03,	//AB
	0x07,	//ABC
	0x0F,	//ABCD
	0x1F,	//ABCDE
	0x3F,	//ABCDEF
};

U08 bLedAutoCDS;    // noon(3.3v) or night(5v) mode
U08 bLedLaneL;
U08 bLedLaneR;
U08 bLedDotL;
U08 bLedDotR;
U08 bLedBrake;
U08 bLedCarGreen;
U08 bLedCarRed;
U08 bLedPdGreen;
U08 bLedPdRed;
U08 bLedDataSaving;

U08 bLedSegmentA;
U08 bLedSegmentB;
U08 bLedSegmentC;
U08 bLedSegmentD;
U08 bLedSegmentE;
U08 bLedSegmentF;
U08 bLedSegmentG;
U08 bLedSegmentDot;

//// Display Data
U08 bLedToggle;     // LED toggles
U08 bLdwToggle;     // LDW toggles
U08 bRecToggle;     // Recording toggle
U08 bSegmentTick;   // Segment LED Tick
U08 uSegmentWaitNum;// FCDA Watching mode or Speed is 0
U08 bTtcMode;
U16 uMainState;
U16 uTTC;
U16 uSegNumL;
U16 uSegNumR;


void Display_init(void);
void DisplayExpress(void);
void DisplayState(void);
void DisplayState_CommErr(void);
#endif	/* DISPLAY_H */