/* spi.h - summary description

*
* Copyright (c) 2000-2015 PLK TECHNOLOGY, Inc.
*

modification history
--------------------
01a,03jun15,hjm     first make

*/

#ifndef _SPI_H
#define _SPI_H
/******************************************************************************
 // *                   SPI PERIPHERAL LIBRARY HEADER FILE
 ******************************************************************************
 * FileName:        		spi.h
 * Dependencies:    	See include below
 * Processor:       		PIC16F1718
 * Compiler:        		XC8
 * Company:         		PLK Technology, Inc.
 *
 *****************************************************************************/

/* PIC16F1718 SPI peripheral library header */

/* includes */
#include "../define.h"

/* typedefs */

/* define */ 
#define MODE_READ			0x0
#define MODE_READ_COMPLETE	0x1
#define MODE_WRITE			0x2
#define MODE_WRITE_COMPLETE	0x3

#define SPI_BUFF_MAX	128
#define MAX_SEND_BUFFER_LENGTH 32

/* global variables */
extern U16	g_spiTxIdx;
extern U16	g_spiTxLength;
extern U16	g_spiRxIdx;

extern U08	g_spiTxBuf[MAX_SEND_BUFFER_LENGTH];
extern U08	g_spiRxBuf[SPI_BUFF_MAX];

/* local variables */

/* imports */

/* function prototypes */

/* ***** SPI ***** */
void OpenSPI( void );
void CloseSPI( void );
S08 WriteSPI(  U08 data_out );
void putsSPI(  U08 *wrptr, U16 ilength);

#endif  /* _SPI_H */

