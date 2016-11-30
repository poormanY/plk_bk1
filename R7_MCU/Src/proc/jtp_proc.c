/* 
 * File:   jtp_proc.c
 * Author: YSW
 *
 * Created on 2015.08,10
 */

#include <xc.h>
#include "jtp_proc.h"
#include "../peripheral/spi.h"

U08 *Jtp_GetDataLoc(U08 *pBuf)
{
    JTP_FRAME *pFrame;

    pFrame = (JTP_FRAME *)pBuf;

    return pBuf + ((U08*)&pFrame->uChksum - (U08*)pFrame);
}

U16 JtpGetChecksum(U08 *pData, U16 uLen)
{
	U16 i;
	U16 uSum;
	U16 *puData;

	puData = (U16 *)pData;
	uLen >>= 1;

	uSum = 0;
	for( i = 0 ; i < uLen ; i++ )
	{
		uSum ^= puData[i];
	}

	uSum = ~uSum;

	return uSum;
}

U16 JtpMakeTransferData(U08 *pBuf, U16 uTgtID, U16 uSrcID, U16 uResult, U16 uCmd, U16 uDataLen)
{
    JTP_FRAME *pFrame;
    U16 uDataFieldLen;
    U16 uLen;

    pFrame = (JTP_FRAME *)pBuf;
    uDataFieldLen = _MK_ALIGN_2(uDataLen);

    pFrame->uHeader  = JTP_HEAD_VALUE;
    pFrame->uTgtID   = uTgtID;
    pFrame->uSrcID   = uSrcID;
    pFrame->uCommand = uCmd;
    pFrame->uParam   = uResult;
	pFrame->uDataLen = uDataFieldLen;

	*(U16*)((U08*)(&pFrame->uFooter) + uDataFieldLen) = JTP_FOOT_VALUE;

	uLen = (U16)((U08*)&pFrame->uChksum - (U08*)pFrame) + uDataFieldLen;
	*(U16*)( (U08*)(&pFrame->uChksum) + uDataFieldLen ) = JtpGetChecksum(pBuf, uLen);
    uLen = sizeof(JTP_FRAME) + uDataFieldLen;

	return uLen;
}

U16 JtpProtocol(U08 *pucRcvBuf)
{
    JTP_FRAME *pFrame;
    U16 uDataFieldLen;
    U16 uFooter;
    U16 uLen;
    U16 uCheckSum;

    pFrame = (JTP_FRAME *)pucRcvBuf;
    uDataFieldLen = _MK_ALIGN_2(pFrame->uDataLen);
    uFooter = *(U16*)((U08*)(&pFrame->uFooter) + uDataFieldLen);

    // Confirm whether Chksum is valid 
    uLen = (U16)((U08*)&pFrame->uChksum - (U08*)pFrame) + uDataFieldLen;
    uCheckSum = *(U16*)((U08*)(&pFrame->uChksum) + uDataFieldLen);
    
	if( pFrame->uHeader != JTP_HEAD_VALUE )
	{
		return _JTP_RESP_CMD_ERR;
	}
	else if( uFooter != JTP_FOOT_VALUE )
	{
		return _JTP_RESP_CMD_ERR;
	}
    else if( pFrame->uTgtID != JTP_ID_PIC )
    {
        return _JTP_RESP_CMD_ERR;
    }
    else if ( uCheckSum != JtpGetChecksum(pucRcvBuf, uLen))
    {
        return _JTP_RESP_TRANS_CHKSUM;
    }
    
	return _JTP_RESP_OK;
}

U08 CheckJtpData(U08 *pBuf)
{
    JTP_FRAME *pFrame;
    U16 uDataFieldLen;
    U16 uReadChecksum;
    U16 uCalcChecksum;
    U16 uLen;

    pFrame = (JTP_FRAME *)pBuf;
    uDataFieldLen = _MK_ALIGN_2(pFrame->uDataLen);

    uLen = (U16)((U08*)&pFrame->uChksum - (U08*)pFrame) + uDataFieldLen;
    uCalcChecksum = JtpGetChecksum(pBuf, uLen);
    uReadChecksum = *(U16*)((U08*)(&pFrame->uChksum) + uDataFieldLen);

    if ( uCalcChecksum == uReadChecksum )   return true;
    return false;
}
