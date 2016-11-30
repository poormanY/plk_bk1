/* spi_proc.c - summary description
*
* Copyright (c) 2000-2015 PLK TECHNOLOGY, Inc.
*
modification history
--------------------
01a,03jun15,hjm     first make


DESCRIPTION

*/

/* includes */
#include <xc.h>
#include <string.h>
#include "spi_proc.h"
#include "../peripheral/spi.h"
#include "../peripheral/gpio.h"
#include "../peripheral/isr.h"
#include "jtp_proc.h"
#include "../HIGHT_MCU.h"
#include "../app_version.h"

/* typedefs */

/* define */
#define SPI_ERROR_MAX_TIME	500	// 5sec

/* global variables */
U08 uSPIModeState = 0;

/* local variables */
U32 wCTimerSPIErrorProc = 0;


/* imports */

/* function prototypes */

//**************** SPI SLAVE *******************************************
//**********************************************************************
void spi_proc_init(void)
{
	U16 i=0;
	
	for ( i = 0 ; i < SPI_BUFF_MAX ; i++ )
	{
		g_spiRxBuf[i] = 0;
	}
    for ( i = 0; i < MAX_SEND_BUFFER_LENGTH; i++ )
    {
         g_spiTxBuf[i] = 0;
    }
	
	uSPIModeState == MODE_READ;
	g_spiRxIdx = 0;
	CloseSPI();	// Turn off SPI modules  if was previosly on

	SSP1IE = 1;	// SPI Interrupt Enable
	OpenSPI();
}

void spi_proc(void)
{
    JTP_FRAME *pFrame;
	U08 i = 0;
    U16 uRet = 0;
    U16 uLen = 0;
    U16 uEodCmd = 0;
    U16 uEodCnt = 0;

	if( (uSPIModeState == MODE_READ_COMPLETE) && (g_spiRxIdx > 0) )
	{
		////////// Confirm RECEIVED JTP_DATA //////////
        uLen = sizeof(JTP_FRAME) + sizeof(EOD_DATA);
        memcpy(g_spiRxTemp, &g_spiRxBuf[g_spiRxIdx-uLen], uLen);
        uRet = JtpProtocol(g_spiRxTemp);
        
        pFrame = (JTP_FRAME *)g_spiRxTemp;
        uLen = pFrame->uDataLen;
        uEodCmd = pFrame->uCommand;
        
        memcpy(&g_stEodData, Jtp_GetDataLoc(g_spiRxTemp), sizeof(EOD_DATA));
        JTP_Decrypt(pbRoundKey, &g_stEodData, 8);
        uEodCnt = g_stEodData.uEodCount;
        
        ////////// SEND JTP_DATA //////////
        g_stMcuData.uMcuCount = uEodCnt;
        g_stMcuVersion.uMcuCount = uEodCnt;
        adc_proc2();
                
        switch ( uEodCmd & CMD_MASK)
        {
            case CMD_READY :
                g_stMcuVersion.uMcuVersion = APP_VERSION;
                JTP_Encrypt(pbRoundKey, &g_stMcuVersion, 8);
                memcpy(Jtp_GetDataLoc(g_spiTxBuf), &g_stMcuVersion, sizeof(MCU_VERSION));
                uLen = JtpMakeTransferData(g_spiTxBuf, JTP_ID_BLACKFIN, JTP_ID_PIC , uRet, CMD_READY, sizeof(MCU_VERSION));
                break;
            case CMD_SEND_STATE3 :
                JTP_Encrypt(pbRoundKey, &g_stMcuData, 8);
                memcpy(Jtp_GetDataLoc(g_spiTxBuf), &g_stMcuData, sizeof(MCU_DATA));
                uLen = JtpMakeTransferData(g_spiTxBuf, JTP_ID_BLACKFIN, JTP_ID_PIC , uRet, CMD_SEND_STATE3, sizeof(MCU_DATA));
                break;
            default :
                JTP_Encrypt(pbRoundKey, &g_stMcuData, 8);
                uRet = _JTP_RESP_CMD_BAD;
                memcpy(Jtp_GetDataLoc(g_spiTxBuf), &g_stMcuData, sizeof(MCU_DATA));
                uLen = JtpMakeTransferData(g_spiTxBuf, JTP_ID_BLACKFIN, JTP_ID_PIC , uRet, CMD_SEND_STATE3, sizeof(MCU_DATA));
                break;
        }
        
		wCTimerSPIErrorProc = wCTimerIrqCnt;
		g_spiRxIdx = 0;
		g_spiTxLength = uLen;		// g_spiTxLength = sizeof(JTP_FRAME);
		uSPIModeState = MODE_WRITE;
	}

	if ( (uSPIModeState == MODE_WRITE) && ( wCTimerIrqCnt > (wCTimerSPIErrorProc + SPI_ERROR_MAX_TIME) ) )
	{
		g_spiTxIdx = 0;
		g_spiRxIdx = 0;
        wCTimerIrqCnt = 0;
		uSPIModeState = MODE_READ;
	}
}

