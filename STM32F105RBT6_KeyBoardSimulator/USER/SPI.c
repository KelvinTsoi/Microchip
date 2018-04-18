
#include "SPI.h"

void SPI_FLASH_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitStructure.GPIO_Pin = KEYBOARD_SPI_SCK | KEYBOARD_SPI_MOSI ;//sck mosi
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitStructure.GPIO_Pin = KEYBOARD_SPI_MISO ;//miso
    GPIO_Init(GPIOB,&GPIO_InitStructure);
		GPIO_SetBits(GPIOB, KEYBOARD_SPI_MISO);
		//GPIO_ResetBits(GPIOA, KEYBOARD_SPI_MISO);
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   
    GPIO_InitStructure.GPIO_Pin = KEYBOARD_SPI_CS;//cs
    GPIO_Init(GPIOB,&GPIO_InitStructure);

}

void sendSPIMsg(uint8_t msg)
{
	uint8_t i=0;
	while(GPIO_ReadInputDataBit(GPIOB,KEYBOARD_SPI_CS) != 0);				//片选信号
	do{
		while(GPIO_ReadInputDataBit(GPIOB,KEYBOARD_SPI_SCK) != 0);			//主机在接收上一个数据
		if((msg & (0x80 >> i)) != 0)
		{
			GPIO_SetBits(GPIOB, KEYBOARD_SPI_MISO);
		}else{
			GPIO_ResetBits(GPIOB, KEYBOARD_SPI_MISO);
		}
		while(GPIO_ReadInputDataBit(GPIOB,KEYBOARD_SPI_SCK) != 1);			//主机未准备好接收数据
		i++;
	}while(i < 8);
	GPIO_SetBits(GPIOB, KEYBOARD_SPI_MISO);
}
