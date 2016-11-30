#include "StdAfx.h"
#include "jtp.h"


void CJtp::Clear()
{
	jtpBuffIdx =0;
	memset(jtpBuff,0,JTP_BUFF_SIZE);
}

BOOL CJtp::JTP_PutByte(BYTE b)
{
	jtpBuff[jtpBuffIdx++] =b;
	jtpBuffIdx %= JTP_BUFF_SIZE;
	return TRUE;
}


BOOL CJtp::JTP_Frame_Get(BYTE buff)
{
	BOOL bResult = FALSE;
	static int JTP_RxRunMode = _RXMGT_JTP_START;
	static int chkBuff = 0;
	static int dataLen = 0;

	if ( JTP_RxRunMode == _RXMGT_JTP_START )
	{
		Clear();
		chkBuff = 0;
		JTP_RxRunMode = _RXMGT_JTP_HEADER;
	}
	
	if ( JTP_RxRunMode == _RXMGT_JTP_HEADER)
	{
		if ( chkBuff == 0 )
		{
			if ( buff == (JTP_HEAD_VALUE & 0x00FF) )
			{
				chkBuff = 1;
				JTP_PutByte(buff);
			}
		}
		else if ( chkBuff == 1 )
		{
			if ( buff == ((JTP_HEAD_VALUE & 0xFF00)>>8) )
			{
				chkBuff = 0;
				JTP_RxRunMode = _RXMGT_JTP_TGTID;

				JTP_PutByte(buff);
			}
			else
			{
				chkBuff = 0;
				JTP_RxRunMode = _RXMGT_JTP_START;
			}
		}
	}
	else if ( (JTP_RxRunMode >= _RXMGT_JTP_TGTID) && (JTP_RxRunMode <= _RXMGT_JTP_PARAMETER) )
	{
		if ( chkBuff == 0 )
		{
			chkBuff = 1;
			JTP_PutByte(buff);
		}
		else if ( chkBuff == 1 )
		{
			chkBuff = 0;
			JTP_RxRunMode++;

			JTP_PutByte(buff);
		}
	}
	else if ( JTP_RxRunMode == _RXMGT_JTP_DATALEN)
	{
		if ( chkBuff == 0 )
		{
			chkBuff = 1;
			dataLen = buff;

			JTP_PutByte(buff);
		}
		else if ( chkBuff == 1 )
		{
			chkBuff = 0;
			dataLen |= (buff<<8);

			if ( dataLen == 0 )
			{
				JTP_RxRunMode = _RXMGT_JTP_CHECKSUM;
				JTP_PutByte(buff);
			}
			// 데이터 길이가 버퍼 길이를 넘는지 확인
			else if ( dataLen <= (JTP_BUFF_SIZE - sizeof(JTP_FRAME)) )
			{
				JTP_RxRunMode = _RXMGT_JTP_DATA;
				JTP_PutByte(buff);
			}
			else
			{
				JTP_RxRunMode = _RXMGT_JTP_START;
			}
		}
	}
	else if ( JTP_RxRunMode == _RXMGT_JTP_DATA )
	{
		JTP_PutByte(buff);
		dataLen--;

		if ( dataLen == 0 )
		{
			JTP_RxRunMode = _RXMGT_JTP_CHECKSUM;
		}
	}
	else if ( JTP_RxRunMode == _RXMGT_JTP_CHECKSUM )
	{
		if ( chkBuff == 0 )
		{
			chkBuff = 1;
			JTP_PutByte(buff);
		}
		else if ( chkBuff == 1 )
		{
			chkBuff = 0;
			JTP_RxRunMode = _RXMGT_JTP_FOOTER;

			JTP_PutByte(buff);
		}
	}
	else if ( JTP_RxRunMode == _RXMGT_JTP_FOOTER )
	{
		if ( chkBuff == 0 )
		{
			chkBuff = 1;
			JTP_PutByte(buff);
		}
		else if ( chkBuff == 1 )
		{
			chkBuff = 0;
			JTP_RxRunMode = _RXMGT_JTP_END;

			JTP_PutByte(buff);
		}
	}

	// JTP FRAME 완성
	if ( JTP_RxRunMode == _RXMGT_JTP_END )
	{
		bResult = TRUE;
		jtpCommOk = 1;

		JTP_RxRunMode = _RXMGT_JTP_START;
	}


	return bResult;
}



U16 CJtp::JTP_Calc_Chksum(BYTE *buff)
{
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;
	U16 uChksumLen = 0;
	U16 uChecksum = 0;

	pJtpFrame = (JTP_FRAME *)buff;
	pJtpBuff = (U16 *)buff;

	// 1바이트 단위 데이터 길이 -> 2바이트 단위 데이터 길이
	uChksumLen = (sizeof(JTP_FRAME) + pJtpFrame->uDataLen - 4)>>1;

	for ( int i = 0; i < uChksumLen; i++ )
	{
		uChecksum ^= pJtpBuff[i];
	}
	uChecksum = ~uChecksum;

	return uChecksum;
}


U16 CJtp::JTP_Valid_Chk(BYTE *buff)
{
	U16 uParameter = _JTP_RESP_OK;
	U16 uCheckSum;
	U16 uFooter;
	JTP_FRAME *pJtpFrame;
	U16 *pJtpBuff;

	pJtpFrame = (JTP_FRAME *)buff;
	pJtpBuff = (U16 *)buff;
	uCheckSum = pJtpBuff[(sizeof(JTP_FRAME) + pJtpFrame->uDataLen - 4)>>1];
	uFooter = pJtpBuff[(sizeof(JTP_FRAME) + pJtpFrame->uDataLen - 2)>>1];

	if (pJtpFrame->uHeader != JTP_HEAD_VALUE)
	{
		uParameter = _JTP_RESP_TRANS_ERR;
	}
	else if (pJtpFrame->uDataLen > (JTP_BUFF_SIZE - sizeof(JTP_FRAME)))
	{
		uParameter = _JTP_RESP_TRANS_TOO_BIG;
	}
	else if (uCheckSum != JTP_Calc_Chksum(buff))
	{
		uParameter = _JTP_RESP_TRANS_CHKSUM;
	}
	else if (uFooter != JTP_FOOT_VALUE)
	{
		uParameter = _JTP_RESP_TRANS_MSGEND;
	}

	return uParameter;
}


U16 CJtp::JTP_Valid_Chk_Display(BYTE *buff)
{
	U16 uParameter = _JTP_RESP_OK;
	JTP_FRAME *pJtpFrame;

	// Check Jtp Format
	uParameter = JTP_Valid_Chk(buff);
	if ( uParameter != _JTP_RESP_OK )
	{
		return uParameter;
	}

	// Check Display Format
	pJtpFrame = (JTP_FRAME *)buff;

	if (pJtpFrame->uTgtId != JTP_ID_HUB)
	{
		uParameter = _JTP_RESP_TRANS_ERR;
	}
	else if (pJtpFrame->uSrcId != JTP_ID_TACO)
	{
		uParameter = _JTP_RESP_TRANS_ERR;
	}
	else if ((pJtpFrame->uCommand != CMD_SEND_ADAS) && (pJtpFrame->uCommand != CMD_READY))
	{
		uParameter = _JTP_RESP_CMD_BAD;
	}
	else if (pJtpFrame->uDataLen != sizeof(DISPLAY_INFO))
	{
		uParameter = _JTP_RESP_BAD_DATALEN;
	}

	return uParameter;
}

BYTE *CJtp::JTP_RCV_DATA(BYTE *buff)
{
	return &buff[sizeof(JTP_FRAME) - 4];
}

U16 CJtp::JTP_RCV_Command(BYTE *buff)
{
	JTP_FRAME *pJtpFrame;
	pJtpFrame = (JTP_FRAME *)buff;

	return pJtpFrame->uCommand;
}

U16 CJtp::JTP_Display_Get_Button(BYTE *buff)
{
	DISPLAY_INFO *pDisplayInfo;

	buff = JTP_RCV_DATA(buff);
	pDisplayInfo = (DISPLAY_INFO *)buff;

	return pDisplayInfo->uDisplayButtonState;
}

CString CJtp::JTP_Display_Get_Version(BYTE *buff)
{
	CString strVersion;
	VERSION_INFO *pVersion;
	
	buff = JTP_RCV_DATA(buff);
	pVersion = (VERSION_INFO *)buff;
	
	strVersion = pVersion->bVersionInfo;

	return strVersion;
}

int CJtp::JTP_Send_Data_Hub_to_Display(HUB_INFO *pHubInfo)
{
	int uLen = 0;
	JTP_FRAME *pJtpFrame;
	U16 chkSum = 0;
	U16 footer = JTP_FOOT_VALUE;

	memset(jtpSndBuff,0,JTP_BUFF_SIZE);

	pJtpFrame = (JTP_FRAME *)jtpSndBuff;
	pJtpFrame->uHeader = JTP_HEAD_VALUE;
	pJtpFrame->uTgtId = JTP_ID_TACO;
	pJtpFrame->uSrcId = JTP_ID_HUB;
	pJtpFrame->uParam = _JTP_RESP_OK;
	pJtpFrame->uCommand = CMD_SEND_ADAS;
	pJtpFrame->uDataLen = sizeof(HUB_INFO);

	// 데이터 복사
	memcpy((void *)&jtpSndBuff[sizeof(JTP_FRAME)-4], (const void *)pHubInfo, sizeof(HUB_INFO));

	chkSum = JTP_Calc_Chksum(jtpSndBuff);
	memcpy((void *)&jtpSndBuff[sizeof(JTP_FRAME)+sizeof(HUB_INFO)-4], (const void *)&chkSum, 2);
	memcpy((void *)&jtpSndBuff[sizeof(JTP_FRAME)+sizeof(HUB_INFO)-2], (const void *)&footer, 2);

	uLen = sizeof(JTP_FRAME) + sizeof(HUB_INFO);

	return uLen;
}

int CJtp::JTP_Send_Ready_Hub_to_Display(HUB_INFO *pHubInfo)
{
	int uLen = 0;
	JTP_FRAME *pJtpFrame;

	memset(jtpSndBuff,0,JTP_BUFF_SIZE);

	pJtpFrame = (JTP_FRAME *)jtpSndBuff;
	pJtpFrame->uHeader = JTP_HEAD_VALUE;
	pJtpFrame->uTgtId = JTP_ID_TACO;
	pJtpFrame->uSrcId = JTP_ID_HUB;
	pJtpFrame->uParam = _JTP_RESP_OK;
	pJtpFrame->uCommand = CMD_READY;
	pJtpFrame->uDataLen = 0;
	pJtpFrame->uChksum = JTP_Calc_Chksum(jtpSndBuff);
	pJtpFrame->uFooter = JTP_FOOT_VALUE;

	uLen = sizeof(JTP_FRAME);

	return uLen;
}