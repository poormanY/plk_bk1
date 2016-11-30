#include <xc.h>
#include "pwr_proc.h"
#include "../peripheral/gpio.h"
#include "../peripheral/delay.h"

// Output
#define		PMIC_PWR_EN		LATCbits.LATC1
#define		MAIN_PWR_EN		LATCbits.LATC2
#define		DSP_RESET		LATBbits.LATB2
// Input
#define		WATCHDOG_EN		PORTBbits.RB1
#define     WATCHDOG_CLK    PORTBbits.RB0

void pwr_proc_init(void)
{
	gpio_init();
}

void pwr_dc_dc_ctrl(U08 ctrl)
{
	MAIN_PWR_EN = ctrl;
}

void pwr_pmic_ctrl(U08 ctrl)
{
	PMIC_PWR_EN = ctrl;
}

void pwr_dsp_reset_ctrl(void)
{
	DSP_RESET = 0;
	DelayMs(500);
	DSP_RESET = 1;
}

U16	pwr_wdt_read(void)
{
	return WATCHDOG_EN;
}

U16 pwr_wdt_clk(void)
{
    return WATCHDOG_CLK;
}


U16 pwr_dsp_boot_on(void)
{
    static U16 boot_cnt = 0;
    U16 wdt_en_pin = 0;
    
    wdt_en_pin = pwr_wdt_read();
    // if WD_EN pin is LOW for 1m, dsp status is boot_on
    if ( wdt_en_pin == LOW )    // check per 1s
    {
        boot_cnt++;
        if ( boot_cnt > 60 )    // 1s x 60 = 1min
        {
            boot_cnt = 0;
            return 1;
        }
    }
    else
    {
        boot_cnt = 0;
    }
    
    return 0;
}


U16 pwr_dsp_wdt_reset(void)
{
    static U16 wdt_cnt = 0;
    static U16 pre_wdt_clk = 0;
    U16 wdt_clk,wdt_en_pin = 0;

    wdt_en_pin = pwr_wdt_read();
    // If WD_EN pin is LOW, check WD_CLK pin is ticking
    //  WD_CLK pin is not ticking for 10s(10ms x 1000). Then reset dsp
    if ( wdt_en_pin == LOW )   // check per 10ms
    {
        wdt_clk = pwr_wdt_clk();
        if ( pre_wdt_clk == wdt_clk )
        {
            wdt_cnt++;
            if ( wdt_cnt > 1000 )
            {
                pwr_dsp_reset_ctrl();
                wdt_cnt = 0;
                return 1;
            }
        }
        else
        {
            wdt_cnt = 0;
        }
        pre_wdt_clk = wdt_clk;
    }
    else
    {
        wdt_cnt = 0;
    }   

    return 0;
}