#ifndef __UART_H
#define	__UART_H

#include "sys.h"  

#define LEFT_HAND_SIDE      0x00
#define RIGHT_HAND_SIDE     0x01

void USART2_Init(uint32_t BaudRate);

int Encode(unsigned char direction, const float pitch, const float roll, const float yaw, unsigned char * buffer);

#endif /* __UART_H */
