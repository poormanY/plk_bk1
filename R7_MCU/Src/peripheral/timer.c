#include <xc.h>
#include "timer.h"

void timer_init(void)
{
	// Timer0 8bit, prescaler 1:1 // 62.5us
	//T0CON = 0b01000101;
    // Timer0 8bit,clock T0CKI,no prescaler  //
  	//T0CON = 0b01101000;
    OPTION_REGbits.TMR0CS = 1;
    OPTION_REGbits.TMR0SE = 0;
    OPTION_REGbits.PS     = 0;
    OPTION_REGbits.PSA    = 1;
    OPTION_REGbits.nWPUEN = 0;

	TMR0IF = 0;
	TMR0IE = 1;
	TMR0 = 0xff;
  	//TMR0IP =0; //low priority
	// Timer0 count 16bit, T0CK1 pin, prescaler not used
	//T0CON = 0b00111000;

#if 1
	// Timer1 16bit, instruction clock(Fosc/4), prescaler 1:8
	// 16MHz / 4 = 4MHz / 8 = 500KHz = 2us  ==> *5000 = 10ms
	T1CON = 0b00110110;//2us
	TMR1IF = 0;
	TMR1IE = 1;
	//TMR1 =0x2A;
    TMR1 = 0xEC77;  // 2us * 5000 = 10ms
  	//TMR1IP = 1; //high priority
#endif


	//TMR0ON = 1;
 	TMR1ON = 1;
}



