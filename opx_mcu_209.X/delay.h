//
// File   : delay.h
// Author : YSW
// Created on 2016.04.19
//
// Brief : Micro/Miele second delay function
// Detail :
//
//
#ifndef DELAY_H
#define	DELAY_H

#include "def_var.h"

#define _XTAL_FREQ 32000000

#ifndef __delay_us(x)
#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
#endif

#ifndef __delay_ms(x)
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
#endif

extern void delay_10ms(U16 uDelayCnt);

#endif	/* DELAY_H */