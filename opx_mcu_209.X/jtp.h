//
// File   : jtp.h
// Author : YSW
// Created on 2016.04.19
//
// Brief : JTP Protocol
// Detail :
//
#ifndef JTP_H
#define	JTP_H

#include "def_var.h"
#include "HIGHT_MCU.h"

/////////////////// Protocol //////////////////////////////////////////////////
#define JTP_HEAD_VALUE              0xAAF0
#define JTP_FOOT_VALUE              0x55F0

/////////////////// ID ///////////////////////////////////////////////////////
#define JTP_ID_PC					(('P'<<0) | ('C'<<8))
#define JTP_ID_CAM					(('B'<<0) | ('B'<<8))
#define JTP_ID_HUB					(('H'<<0) | ('U'<<8))
#define JTP_ID_DISPI				(('D'<<0) | ('I'<<8))
#define JTP_ID_BLACKFIN             (('B'<<0) | ('F'<<8))
#define JTP_ID_PIC                  (('P'<<0) | ('I'<<8))

 /////////////////// Command //////////////////////////////////////////////////
#define CMD_READY                   0x0001
#define CMD_GET_MANUFACTURER_CONFIG 0x0110
#define CMD_SET_MANUFACTURER_CONFIG 0x0112
#define CMD_GET_USER_CONFIG         0x0114
#define CMD_SET_USER_CONFIG         0x0116
#define CMD_ENABLE_BLACKBOX         0x0122
#define CMD_GET_RTC                 0x2100
#define CMD_SET_RTC                 0x2101
#define CMD_SEND_STATE              0x7004  // OPTIAN - MCU
#define CMD_ERASE_DATA              0x7006
#define CMD_FORMAT               	0x7009
#define CMD_SEND_STATE2             0x7016  // BB - DISPI
#define CMD_SEND_STATE3             0x7020  // EOD - MCU
#define CMD_SEND_AP_MCU             0x7024  // AP - MCU
#define CMD_MASK                    0x7FFF

/////////////////// Response or Received State ////////////////////////////////
#define _JTP_RESP_OK             	0x0000      // No Error (All OK)
#define _JTP_RESP_TRANS_TIMEOUT  	0xFFFF      // Transmit Error::Time out
#define _JTP_RESP_TRANS_TOO_BIG  	0xFFFE      // Transmit Error::Too Big Data
#define _JTP_RESP_TRANS_CHKSUM   	0xFFFD      // Transmit Error::Invalid ChkSum
#define _JTP_RESP_TRANS_MSGEND   	0xFFFC      // Transmit Error::Invalid MsgEnd
#define _JTP_RESP_TRANS_ERR      	0xFFF0      // Transmit Error::Others
#define _JTP_RESP_CMD_RSV        	0xFFEF      // Command Error::Reserved Cmd
#define _JTP_RESP_CMD_BAD        	0xFFEE      // Command Error::Unknown Cmd
#define _JTP_RESP_CMD_ERR        	0xFFE0      // Command Error::Others
#define _JTP_RESP_BAD_PARA       	0xFFD1      // Parameter Error:: Invalid Parameter
#define _JTP_RESP_BAD_DATALEN    	0xFFD2      // Parameter Error:: DataLen
#define _JTP_RESP_BAD_DATA       	0xFFD4      // Parameter Error:: Data
#define _JTP_RESP_ERROR          	0xFFD0      // Run Time Error(0xFFD0~0xFFFF)
#define _JTP_RESP_WARN           	0x0001      // Run Time Warning

/////////////////// Data Format ///////////////////////////////////////////////
// JTP_FRAME.uHeader ~ JTP_FRAME.uDataLen : 12bytes
#define JTP_HEAD_LEN    12
// JTP_FRAME.uChksum ~ JTP_FRAME.uFooter : 4bytes
#define JTP_TAIL_LEN    4
// JTP Data Package 
#define MAX_JTP_BUFFER_LENGTH 64
#define MAX_JTP_PACK_NUMBER 4

typedef struct
{
    U16 uHeader;        // Always 0xF0 0xAA = 0xAAF0
    U16 uTgtId;         // "PI" (PIC)
    U16 uSrcId;         // "BB" (CAM)
    U16 uCommand;		// 0x7016 (CMD_SEND_STATE)
    U16 uParam;			// Response of data format
    U16 uDataLen;    	// number of data[i]
    U16 uChksum;		// uHead ^ ~ ^ uData[i]
    U16 uFooter;       	// Always 0xF0 0x55 = 0x55F0
} JTP_FRAME;

/////////////////// JTP RX Data ///////////////////////////////////////////////
// CMD_READY
typedef struct
{
#ifdef HIGHT_CRYPT_EN
    U16 uRandomNumber;
    U16 uOpxCount;
#endif
    U16 uOpxVersion;
    U16 uWakeUpTemperature;
    U16 uWatchDogFireTime;
    U16 uBplusThresholdVolt;
} OPX_STATIC_INFO;

// CMD_SEND_STATE
typedef struct
{
#ifdef HIGHT_CRYPT_EN
    U16 uRandomNumber;
    U16 uOpxCount;
    U16 uReserved;
#endif
    U16 uPowerCommand;
} OPX_DYNAMIC_INFO;

enum POWER_STATE_Tag
{
    POWER_STATE_OFF = 0,
    POWER_STATE_ON,
    POWER_STATE_REBOOT,
    POWER_STATE_SUSPEND,
    POWER_STATE_PARKING,
    POWER_STATE_BPLUS_OUT,
    POWER_STATE_READY,
    POWER_STATE_MCU_RESET,
    POWER_STATE_MAX
};

/////////////////// JTP TX Data ///////////////////////////////////////////////
// CMD_READY
typedef struct
{
#ifdef HIGHT_CRYPT_EN
    U16 uRandomNumber;
    U16 uMcuCount;
    U16 uReserved;
#endif
    U16 uMcuVersion;
} MCU_STATIC_INFO;

// CMD_SEND_STATE
typedef struct
{
#ifdef HIGHT_CRYPT_EN
    U16 uRandomNumber;
    U16 uMcuCount;
#endif
    U16 uBplus;
    U16 uIg;
    U16 uTemp;
    U16 uTurnLeft;
    U16 uTurnRight;
    U16 uBrake;
    U16 uSpeedPulse;
} MCU_DYNAMIC_INFO;



enum RXMGT_MODE_tag
{
   _RXMGT_NODATA = 0,    // RX buffer is null
   _RXMGT_START,
   _RXMGT_HEAD,         // Read Frame.uHead ~ Frame.uDataLen;
   _RXMGT_DATA,
   _RXMGT_END,
   _RXMGT_TIME_OUT,
   _RXMGT_TOO_BIG,
   _RXMGT_SKIP
};

extern U08 Jtp_comm_init(void);
extern U08 Jtp_comm_close(void);

extern U08 Jtp_Protocol(void);

extern U16 Jtp_Get_PowerCommand(void);
extern void Jtp_Set_PowerCommand(U16 uPwrCmd);

extern U16 Jtp_Get_WatchDogFireSec(void);
extern void Jtp_Set_WatchDogFireSec(U16 uWDT);
#endif	/* JTP_H */

