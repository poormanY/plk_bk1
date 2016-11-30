/* spi.c - summary description
*
* Copyright (c) 2000-2015 PLK TECHNOLOGY, Inc.
*
modification history
--------------------
01a,03jun15,hjm     first make


DESCRIPTION
	PIC16F1718 SPI driver
*/

/* includes */
#include <xc.h>
#include "spi.h"

/* typedefs */

/* define */

/* global variables */
U16	g_spiTxIdx = 0;
U16	g_spiTxLength = 0;
U16	g_spiRxIdx = 0;

U08	g_spiTxBuf[MAX_SEND_BUFFER_LENGTH];
U08	g_spiRxBuf[SPI_BUFF_MAX];

/* local variables */

/* imports */

/* function prototypes */


/********************************************************************
*   Function Name:  OpenSPI                                         *
*   Return Value:   void                                            *
*   Parameters:     SSP peripheral setup bytes                      *
*   Description:    This function sets up the SSP module on a       *
*                   PIC16Cxxx device for use with a Microchip SPI   *
*                   EEPROM device or SPI bus device.                *
********************************************************************/
void OpenSPI( void )
{
	// Set the SPI module to the options selected in the User Interface

	// BF RCinprocess_TXcomplete; UA dontupdate; SMP Sample At Middle; P stopbit_notdetected; S startbit_notdetected; R_nW write_noTX; CKE Idle:High, Active:Low ; D_nA lastbyte_address;
	SSP1STAT = 0x40;
	//SSP1STAT = 0x00;

	// SSPEN enabled; WCOL no_collision; SSPOV no_overflow; CKP Idle:High, Active:Low; SSPM SCKx_nSSxenabled;
	SSP1CON1 = 0x34;

	// BOEN disabled; AHEN disabled; SBCDE disabled; SDAHT 100ns; DHEN disabled; ACKTIM ackseq; PCIE disabled; SCIE disabled;
	SSP1CON3 = 0x00;


	// SS : RA5
	LATA &= 0xDF;
	TRISA |= 0x20;
	ANSELA &= 0xDF;
	WPUA &= 0xDF;

	// CLK : RC3, SDI : RC4, SDO : RC5
	LATC &= 0xC7;
	TRISC |= 0x18;
	ANSELC &= 0xC7;
	WPUC &= 0xC7;

	OPTION_REGbits.nWPUEN = 0x01;

	PPSLOCK = 0x55;
	PPSLOCK = 0xAA;
	PPSLOCKbits.PPSLOCKED = 0x00;		// unlock PPS

	SSPSSPPSbits.SSPSSPPS = 0x05;		// RA5->MSSP:SS
	RC5PPSbits.RC5PPS = 0x11;			// RC5->MSSP:SDO
	SSPCLKPPSbits.SSPCLKPPS = 0x13;		// RC3->MSSP:SCK
	SSPDATPPSbits.SSPDATPPS = 0x14;		// RC4->MSSP:SDI
	PPSLOCK = 0x55;
	PPSLOCK = 0xAA;
	PPSLOCKbits.PPSLOCKED = 0x01;		// lock PPS
}


/********************************************************************
*     Function Name:    CloseSPI                                    *
*     Return Value:     void                                        *
*     Parameters:       void                                        *
*     Description:      This function disables the SSP module. Pin  *
*                       I/O returns under the control of the port   *
*                       registers.                                  *
********************************************************************/
void CloseSPI( void )
{
	SSP1CON1 &= 0xDF;				// disable synchronous serial port
}


/********************************************************************
*     Function Name:    WriteSPI                                    *
*     Return Value:     Status byte for WCOL detection.             *
*     Parameters:       Single data byte for SPI bus.               *
*     Description:      This routine writes a single byte to the    *
*                       SPI bus.                                    *
********************************************************************/
S08 WriteSPI( U08 data_out )
{
	U08 TempVar;
	TempVar = SSPBUF;           // Clears BF
	PIR1bits.SSP1IF = 0;         // Clear interrupt flag
	SSP1CON1bits.WCOL = 0;			//Clear any previous write collision
	SSPBUF = data_out;           // write byte to SSP1BUF register
	if ( SSP1CON1 & 0x80 )        // test if write collision occurred
		return ( -1 );              // if WCOL bit is set return negative #
	else
	// while( !SSP1STATbits.BF );  // wait until bus cycle complete
		while( !PIR1bits.SSP1IF );  // wait until bus cycle complete
	return ( 0 );                // if WCOL bit is not set return non-negative#
}


/********************************************************************
*     Function Name:    putsSPI                                     *
*     Return Value:     void                                        *
*     Parameters:       address of write string storage location    *
*     Description:      This routine writes a string to the SPI bus.*
********************************************************************/
void putsSPI( U08 *wrptr, U16 ilength )
{
	U16 i = 0;

	for ( i = 0 ; i < ilength ; i++ )
	{
		PIR1bits.SSP1IF = 0;		 // Clear interrupt flag
		SSP1CON1bits.WCOL = 0;			//Clear any previous write collision
		SSP1BUF = *wrptr++;           // initiate SPI bus cycle
		while( !PIR1bits.SSP1IF );    // wait until 'BF' bit is set
	}
}


