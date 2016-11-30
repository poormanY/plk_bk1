#include <xc.h>
#include "adc.h"
#include "../peripheral/delay.h"


void adc_init(void)
{
    ADCON0bits.ADON=0;

    ANSELAbits.ANSA4 = 0;   // timer0 speed pulse
    ANSELBbits.ANSB0 = 0;   // WD_CLK
    ANSELBbits.ANSB1 = 0;   // WD_EN
    
    ANSELCbits.ANSC6 = 0;   // UART_TX
    ANSELCbits.ANSC7 = 0;   // UART_RX
    //ANSELA = 0b00001110;
    //ANSELB = 0b00011100;
    //ANSELC = 0b00000000;


}

U16 adc_read(U08 mode)
{
    U16	usAdcValue = 0;

    ADRESH = 0;
    ADRESL = 0;


    ADCON0 = 0;
    ADCON1 = 0b10100000;    // right justifined(1), focs/32(010), reserved(0), Vref- is Vss(0), Vref+ Vdd(00)

    ADCON2 = 0b00000000;


    /* update the channel to the A2D converter */
    // 0x01 : B+ check
    // 0x02 : IG check
    // 0x03 : Temperature
    //ADCON0 |= (mode & 0x1f)<<2;
    ADCON0bits.CHS = mode;

    ADCON0bits.ADON=1;	/* enable A2D converter */
    PIE1bits.ADIE=0;	/* not interrupt driven */

    // Acquisition time
    // Tacq = 2us + 892ns + ((100'C - 25'C)*0.05us) = 6.642us
    DelayUs(5);
    //DelayMs(1);
    ADCON0bits.GO_nDONE = 1;
    while ( ADCON0bits.GO_nDONE );

    usAdcValue = (U16)(((ADRESH&0x03)<<8)|(ADRESL&0xff));
    PIR1bits.ADIF = 0;
    ADCON0bits.ADON = 0;

    return usAdcValue;
}




