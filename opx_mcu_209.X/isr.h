//
// File   : isr.h
// Author : YSW
// Created on 2016.04.15
//
// Brief :
// Detail :
//
#ifndef ISR_H
#define	ISR_H

#include "def_var.h"

extern U32 gulSystemTick;
extern U32 gulDelayTimer;

// return g_car_pulse
extern U16 isr_get_car_pulse(void);

#endif	/* ISR_H */

