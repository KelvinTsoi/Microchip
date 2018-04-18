#include "gpio.h"
#include "exti.h"
#include "usart.h"
#include "TIM.h"
#include "SPI.h"

#define MAX_UART_RECV_BUF_LENGTH 32
#define MAX_UART_SEND_BUF_LENGTH 32

uint16_t g_byUartRecvLength = 0;   								 								//串口接收长度
uint8_t g_abyUartRecvBuf[MAX_UART_RECV_BUF_LENGTH] = {0x00};      //串口接收缓冲区

int main(void)
{
	SPI_FLASH_Init();
	USART1_Config();
	while(1)
	{
		;
	}
}
