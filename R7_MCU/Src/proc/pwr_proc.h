#ifndef	_POWER_PROC_H_
#define	_POWER_PROC_H_

#include "../define.h"

enum POWER_CTRL
{
	POWER_OFF = 0x00,
	POWER_ON,
};

void	pwr_proc_init(void);
void	pwr_dc_dc_ctrl(U08 ctrl);
void	pwr_pmic_ctrl(U08 ctrl);
void	pwr_dsp_reset_ctrl(void);
U16		pwr_wdt_read(void);
U16     pwr_wdt_clk(void);
U16     pwr_dsp_wdt_reset(void);
#endif