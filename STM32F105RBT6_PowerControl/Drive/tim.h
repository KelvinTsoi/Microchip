#ifndef __TIM_H
#define	__TIM_H

#include "stm32f10x_tim.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

void TIMER3_Init(uint16_t time_ms);
void TIMER3_Configuration(void);

#endif /* __TIM_H */
