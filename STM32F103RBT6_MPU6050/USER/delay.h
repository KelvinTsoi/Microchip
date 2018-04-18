#ifndef __DELAY_H
#define	__DELAY_H

#include "stm32f10x.h"
#include "core_cm3.h"

#include <stdio.h>

void Delay_Init(void);
void uDelay(__IO uint32_t nTime);
void DelayMs(__IO uint32_t nTime);
void DelayUs(__IO uint32_t nTime);

#endif 
