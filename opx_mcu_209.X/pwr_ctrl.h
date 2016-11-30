//
// File   : pwr_ctrl.h
// Author : YSW
// Created on 2016.04.20
//
// Brief : Power Control
// Detail :
//
#ifndef POWER_CONTROL_H
#define	POWER_CONTROL_H

#include "def_var.h"

#define POWER_OFF 0
#define POWER_ON  1

extern void set_adc_bplus_ref(U16 uAdcRef);
extern void set_wakeup_temp_ref(U16 uTempRef);

extern void pwr_main_ctrl(U08 ctrl);
extern void pwr_pmic_ctrl(U08 ctrl);
extern void pwr_dsp_reset_ctrl(U08 ctrl);
extern void pwr_dsp_reset(void);


#endif	/* POWER_CONTROL_H */

