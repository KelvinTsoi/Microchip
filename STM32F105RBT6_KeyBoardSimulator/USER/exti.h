#ifndef EXTI_H
#define EXTI_H

#include "stm32f10x.h"
#include "gpio.h"

void NVIC_USART_Rx_Configuration(void);
void NVIC_UnlockedTime_Configuration(void);
void EXTI_UnlockedTime_Config(void);

#endif //EXTI_H

