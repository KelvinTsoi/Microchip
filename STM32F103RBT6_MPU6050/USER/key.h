#ifndef KEY_H
#define KEY_H

#include "stm32f10x.h"
#include "SPI.h"

#ifndef MAX_UART_RECV_BUF_LENGTH
#define MAX_UART_RECV_BUF_LENGTH 32
#endif //MAX_UART_RECV_BUF_LENGTH

#ifndef ERROR
#define ERROR 		0xFFFF
#endif

#define BIT_END 	'E'													//以'E'作为串口命令结束符

extern uint16_t g_byUartRecvLength;
extern uint8_t g_abyUartRecvBuf[MAX_UART_RECV_BUF_LENGTH];

void Rough_ms(uint16_t time);
int KeyBoardTest(void);
int FastKeyBoardTest(void);
void TIM_PWM_Init(u16 arr,u16 psc);
void clicked(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);

#endif //KEY_H
