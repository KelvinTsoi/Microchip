#include "usart.h"

void USART1_Config(void)						//串口初始化
{
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;
	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	USART_DeInit(USART1);  						//复位串口1(各参数置为缺省值)
	USART1_GPIO_Config();
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	/* Configure the USART1 synchronous paramters */
	USART_ClockInit(USART1, &USART_ClockInitStructure);
	
	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	NVIC_USART_Rx_Configuration();
	/* Configure USART1 basic and asynchronous paramters */ 
	USART_Init(USART1, &USART_InitStructure);
	/* Enable USART1 Receive interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	/* Enable USART1 */ 
	USART_Cmd(USART1, ENABLE);
}

