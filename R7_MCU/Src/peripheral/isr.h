#ifndef	_ISR_H_
#define	_ISR_H_

#include "../define.h"

typedef	struct _tagTimerFlags
{
    U08   flag10ms;
	U08	flag100ms;
	U08	flag1sec;
}TimerFlag_t;

U32 gulSystemTick;

extern TimerFlag_t	g_stTimerFlags;
extern U16	g_car_pulse;
extern U16	g_xor_value;
extern U32 wCTimerIrqCnt;

U16  isr_get_car_pulse(void);

#endif
