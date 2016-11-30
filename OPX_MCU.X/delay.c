//
// File   : delay.c
// Author : YSW
// Created on 2016.04.15
//
// Brief : Delay Micro/Miele Sceond 
// Detail :
//
#include <xc.h>
#include "def_var.h"
#include "delay.h"
#include "isr.h"

void delay_10ms(U16 uDelayCnt)
{
    gulDelayTimer = uDelayCnt;
    
    while(1)
    {
        if( gulDelayTimer == 0 )    break;
    }    
}