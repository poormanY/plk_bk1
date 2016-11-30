/* 
 * File:   jtp_proc.h
 * Author: YSW
 *
 * Created on 2015.08,10
 */

#ifndef JTP_PROC_H
#define	JTP_PROC_H

#include "../define.h"

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

 /////////////////// Command ///////////////////
#define CMD_READY                   0x0001
#define CMD_GET_MANUFACTURER_CONFIG 0x0110
#define CMD_SET_MANUFACTURER_CONFIG 0x0112
#define CMD_GET_USER_CONFIG         0x0114
#define CMD_SET_USER_CONFIG         0x0116
#define CMD_ENABLE_BLACKBOX         0x0122
#define CMD_GET_RTC                 0x2100
#define CMD_SET_RTC                 0x2101
#define CMD_SEND_STATE              0x7004
#define CMD_ERASE_DATA              0x7006
#define CMD_FORMAT               	0x7009
#define CMD_SEND_STATE2             0x7016  // BB - DISPI
#define CMD_SEND_STATE3             0x7020  // EOD - MCU
#define CMD_MASK                    0x7FFF

/////////////////// Response or Received State /////////////////// 
#define _JTP_RESP_OK             	0x0000      // No Error (All OK)         			: 모두 정상적으로 처리됨
#define _JTP_RESP_TRANS_TIMEOUT  	0xFFFF      // Transmit Error::Time out       		: 데이터 수신중 0.1초 동안 데이터 수신이 없었음
#define _JTP_RESP_TRANS_TOO_BIG  	0xFFFE      // Transmit Error::Too Big Data   		: 전송되는 데이터의 크기가 너무 커 처리할 수 없음
#define _JTP_RESP_TRANS_CHKSUM   	0xFFFD      // Transmit Error::Invalid ChkSum 		: 체크섬 에러
#define _JTP_RESP_TRANS_MSGEND   	0xFFFC      // Transmit Error::Invalid MsgEnd 		: 메시지 종료값이 맞지 않음
#define _JTP_RESP_TRANS_ERR      	0xFFF0      // Transmit Error::Others         		: 기타 전송 에러(0xFFF0~0xFFFB)
#define _JTP_RESP_CMD_RSV        	0xFFEF      // Command Error::Reserved Cmd			: 아직 지원되지 않은 명령어임
#define _JTP_RESP_CMD_BAD        	0xFFEE      // Command Error::Unknown Cmd			: 잘못된 명령어임
#define _JTP_RESP_CMD_ERR        	0xFFE0      // Command Error::Others				: 기타 명령어 에러(0xFFE0~0xFFED)
#define _JTP_RESP_BAD_PARA       	0xFFD1      // Parameter Error:: Invalid Parameter : 명령어에 따른 파마메터 에러
#define _JTP_RESP_BAD_DATALEN    	0xFFD2      // Parameter Error:: DataLen           : 명령어에 따른 데이터 크기 에러
#define _JTP_RESP_BAD_DATA       	0xFFD4      // Parameter Error:: Data              : 잘못된 데이터
#define _JTP_RESP_ERROR          	0xFFD0      // Run Time Error(0xFFD0~0xFFFF)
#define _JTP_RESP_WARN           	0x0001      // Run Time Warning					: 명령어에 따라 다르게 해석됨. (0x0001~0xFFCF)

#define _MK_ALIGN_2(lData)          (((U32)(lData) + 1) & 0xFFFFFFFE)

enum RXMGT_MODE_tag
{
   _RXMGT_NODATA,    // RX buffer is null
   _RXMGT_START,
   _RXMGT_HEAD,      // Read Frame.uHead ~ Frame.uDataLen;
   _RXMGT_DATA,
   _RXMGT_END,
   _RXMGT_TIME_OUT,
   _RXMGT_TOO_BIG,
   _RXMGT_SKIP
};

typedef struct
{
    U16 uHeader;
    U16 uTgtID;
    U16 uSrcID;
    U16 uCommand;
    U16 uParam;
    U16 uDataLen;
    U16 uChksum;
    U16 uFooter;
} JTP_FRAME;

// Get EOD count data
typedef struct
{
    U16 uRandomNumber;  // Random Vale
    U16 uEodCount;      // EOD count recived data from EOD
    U16 uReserved1;     // Reserved1 : 2Byte
    U16 uReserved2;     // Reserved2 : 2Bytes
} EOD_DATA;

// Get MCU information Data struct
typedef struct
{
    U16 uRandomNumber;  // ADC Value
    U16 uMcuCount;      // = EOD_COUNT of received data from EOD
    U16 uSpeedPulse;	// Speed Pulse Count : ADC Value 2Byte
    U16 uWiperIn;       // Wiper in Signal : ADC Value 2Byte
	U16 uTurnLeft;		// Turn Left Signal : ADC Value 2Byte
	U16 uTurnRight;		// Turn Right Signal : ADC Value 2Byte
	U16 uRearLamp;		// Rear Lamp Signal : ADC Value 2Byte
	U16 uBrake;			// Brake Signal : ADC Value 2Byte
    U16 uIgChkMcu;      // IG Check Signal : ADC Value 2Byte
	S08 iTemperature;	// Temperature Value : Temperature Value -40 ~ +85 (Celsius) 1Byte
	U08 bReserved;      // Reserved : 1Byte
} MCU_DATA;

typedef struct
{
    U16 uRandomNumber;  // ADC Value
    U16 uMcuCount;      // = EOD_COUNT of recevied data by EOD
    U16 uMcuVersion;    // APP_VERSION (app_version.h)
    U16 uReserved;      // Reserved : 2byte
} MCU_VERSION;

EOD_DATA g_stEodData;
MCU_DATA g_stMcuData;
MCU_VERSION g_stMcuVersion;


U08 g_spiRxTemp[sizeof(JTP_FRAME)];

U08 *Jtp_GetDataLoc(U08 *pBuf);
U16 JtpGetChecksum(U08 *pData, U16 uLen);
U16 JtpMakeTransferData(U08 *pBuf, U16 uTgtID, U16 uSrcID, U16 uResult, U16 uCmd, U16 uDataLen);
U16 JtpProtocol(U08 *pucRcvBuf);
U08 CheckJtpData(U08 *pBuf);

#endif	/* JTP_PROC_H */

