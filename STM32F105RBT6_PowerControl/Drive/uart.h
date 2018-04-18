#ifndef __UART_H
#define	__UART_H

#include <stdio.h>
#include "delay.h"

void UART_Print_Init(uint32_t BaudRate);
void UART_Print_Configuration(void);

#endif /* __UART_H */
