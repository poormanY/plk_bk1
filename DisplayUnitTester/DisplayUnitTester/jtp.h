/////////////////////////////////////////////////////////
//
//  File name : jtp.h
//	Author    : YSW
//  Date      : 2015.08.18
//
/////////////////////////////////////////////////////////
#pragma once

#ifndef JTP_H
#define	JTP_H

#include "def_var.h"
#include "StdAfx.h"

/////////////////// Protocol ///////////////////
#define JTP_HEAD_VALUE              0xAAF0
#define JTP_FOOT_VALUE              0x55F0

/////////////////// ID ////////////////////////
#define JTP_ID_PC					(('P'<<0) | ('C'<<8))
#define JTP_ID_CAM					(('B'<<0) | ('B'<<8))
#define JTP_ID_HUB					(('H'<<0) | ('U'<<8))
#define JTP_ID_DISPI				(('D'<<0) | ('I'<<8))
#define JTP_ID_BLACKFIN             (('B'<<0) | ('F'<<8))
#define JTP_ID_PIC                  (('P'<<0) | ('I'<<8))
#define JTP_ID_TACO                 (('T'<<0) | ('A'<<8))

 /////////////////// Command ///////////////////
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
#define CMD_SEND_ADAS               0x7018  // R7 - New Dispaly
#define CMD_SEND_STATE3             0x7020  // EOD - MCU
#define CMD_SEND_AP_MCU             0x7024  // AP - MCU
#define CMD_MASK                    0x7FFF

/////////////////// Response or Received State ///////////////////
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

/////////////////// Data Length modification ///////////////////
#define _MK_ALIGN_2(lData)          (((U32)(lData) + 1) & 0xFFFFFFFE)
#define _MK_ALIGN_4(lData)          (((U32)(lData) + 3) & 0xFFFFFFFC)
#define SWAP_WORD(a)                ((a << 8) & 0xFF00) | ((a >> 8) & 0x00FF)

//Sets an optional structure alignment
#pragma pack (1)
/////////////////// Data Format ///////////////////
typedef struct
{
    U16 uHeader;        // Always 0xF0 0xAA = 0xAAF0
    U16 uTgtId;         // "PI" (PIC)
    U16 uSrcId;         // "PC" (PC)
    U16 uCommand;		// 0x7016 (CMD_SEND_STATE)
    U16 uParam;			// 2byte
    U16 uDataLen;    	// number of data[i]
    U16 uChksum;		// uHead ^ ~ ^ uData[i]
    U16 uFooter;       	// Always 0xF0 0x55 = 0x55F0
} JTP_FRAME;

////////////////// Optian2 Data ///////////////////
typedef struct
{
    U16 uTemp;
    U16 uTurn_L;
    U16 uTurn_R ;
    U16 uSpeed_cnt;
    U16 uCan_Vss;
    U16 uExtern_Vss;
    U16 uBrake;
    U16 uMcuVersion;
} UBULK_DATA;

////////////////// Display Data ///////////////////
typedef struct
{
	U16 ttc;
	U08 speed;
	U08 signal;
	U08 luminance;
	U08 reserved1;
	U08 reserved2;
	U08 reserved3;
} MAIN_INFO;

////////////////// CMD_SEND_ADAS //////////////////
// Hub -> New Disaplay
typedef struct
{
    U08 bDeviceState;
    U08 bLaneDetectState;
    U16 uFcwState;
    U16 uHmwTTT;
    U08 bPdState;
    U08 bHBA;
    U16 uTSR;
    U08 bTsrOverSpd;
    U08 bIoOutput;
    U16 uPdDistance;
    U08 bDisplayModuleState;
    U08 bSignal;
} HUB_INFO;

// New Display -> Hub
typedef struct
{
    U16 uDisplayButtonState;
} DISPLAY_INFO;

typedef struct
{
	U08 bVersionInfo[16];
} VERSION_INFO;

enum RXMGT_MODE_tag
{
	_RXMGT_JTP_START,
	_RXMGT_JTP_HEADER,
	_RXMGT_JTP_TGTID,
	_RXMGT_JTP_SRCID,
	_RXMGT_JTP_COMMAND,
	_RXMGT_JTP_PARAMETER,
	_RXMGT_JTP_DATALEN,
	_RXMGT_JTP_DATA,
	_RXMGT_JTP_CHECKSUM,
	_RXMGT_JTP_FOOTER,
	_RXMGT_JTP_END,
};

/////////////////// OPX JTP TX Data ///////////////////////////////////////////////
// CMD_READY
typedef struct
{
    U16 uRandomNumber;
    U16 uOpxCount;
    U16 uOpxVersion;
    U16 uWakeUpTemperature;
    U16 uWatchDogFireTime;
    U16 uBplusThresholdVolt;
} OPX_STATIC_INFO;
/////////////////// OPX JTP RX Data ///////////////////////////////////////////////
// CMD_READY
typedef struct
{
    U16 uRandomNumber;
    U16 uMcuCount;
    U16 uReserved;
    U16 uMcuVersion;
} MCU_STATIC_INFO;


#define JTP_BUFF_SIZE 512

class CJtp
{
public:
	BYTE jtpBuff[JTP_BUFF_SIZE];//JTP FRAME 수신 데이터 버프
	BYTE jtpSndBuff[JTP_BUFF_SIZE];//JTP FRAME 송신 데이터 버프
	int jtpBuffIdx;//JTP 버퍼에 데이터를 넣고 빼 올때 사용할 변수
	int jtpCommOk;//JTP 통신을 하고 있으면 Ok

	void Clear();//버퍼를 초기화 시킴

	BOOL JTP_PutByte(BYTE b);//큐버퍼에 1바이트를 넣음
	BOOL JTP_Frame_Get(BYTE buff);//들어오는 데이터가 JTP FRAME이면 TRUE, 아니면 FALSE를 리턴
	int JTP_Send_Data_Hub_to_Display(HUB_INFO *pHubInfo);//디스플레이에 ADAS데이터를 송신
	int JTP_Send_Ready_Hub_to_Display(HUB_INFO *pHubInfo);//디스플레이에서 version정보를 받기위함

	U16 JTP_Calc_Chksum(BYTE *buff);//JTP Checksum 계산 값 리턴
	U16 JTP_Valid_Chk(BYTE *buff);//들어온 버퍼가 JTP 형식에 맞는 확인, 에러 코드 리턴
	U16 JTP_Valid_Chk_Display(BYTE *buff);//들어온 버퍼가 JTP,Display 형식에 맞는 확인, 에러 코드 리턴

	BYTE *JTP_RCV_DATA(BYTE *buff);//들어온 버퍼에서 데이터 버퍼부터 리턴
	U16 JTP_RCV_Command(BYTE *buff);//들어온 버퍼에서 Command 리턴
	U16 JTP_Display_Get_Button(BYTE *buff);//수신 데이터 버퍼에서 버튼 상태 값을 얻음
	CString JTP_Display_Get_Version(BYTE *buff);//수신 데이터 버퍼에서 버전 정보를 얻음
};

#endif	/* JTP_H */

