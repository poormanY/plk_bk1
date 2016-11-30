/*
 *	Delay functions
 *	See delay.h for details
 *
 *	Make sure this code is compiled with full optimization!!!
 */

#include	"delay.h"

void
DelayMs(U08 cnt)
{
	U08 i;
	while (cnt--) {
		i=8;
		while(i--) {
			DelayUs(uS_CNT);	/* Adjust for error */
		} ;
	} ;
}


