#include "keyboard.h"
#include "delay.h"

char KeyValueTable[16] = {13, 14, 15, 16, 9, 10, 11, 12, 6, 5, 7, 8, 4, 3, 2, 1};

uint8_t key_Sensor_Level = 14;

void KeyBoardInit()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStruct.GPIO_Pin = KEYBOARD_SPI_NSS | KEYBOARD_SPI_SCK | KEYBOARD_SPI_MOSI ;

  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_SetBits(GPIOA, KEYBOARD_SPI_NSS | KEYBOARD_SPI_SCK | KEYBOARD_SPI_MOSI );
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStruct.GPIO_Pin = KEYBOARD_SPI_MISO ;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
  * @brief  
  * @param  None
  * @retval The received byte.
  */
void Key_SenInit(void)
{
  uint8_t i = 0;
	uint8_t temp = key_Sensor_Level;
	
  GPIO_ResetBits(GPIOA, KEYBOARD_SPI_NSS );
	
  do
  {
    if( (temp & 0x80 ) != 0 )
    {
			GPIO_SetBits(GPIOA, KEYBOARD_SPI_MISO );
    }
    else
    {
      GPIO_ResetBits(GPIOA, KEYBOARD_SPI_MISO );
    }

		GPIO_ResetBits(GPIOA, KEYBOARD_SPI_SCK );
    GPIO_SetBits(GPIOA, KEYBOARD_SPI_SCK );
		
		temp <<= 1;
		
		i++;
    
    DelayUs(5);
  }
  while (i < 8);

	GPIO_SetBits(GPIOA, KEYBOARD_SPI_NSS );
  GPIO_SetBits(GPIOA, KEYBOARD_SPI_MISO );
}

/**
  * @brief  从SD读一个字节.
  * @param  None
  * @retval The received byte.
  */
uint8_t CheckKey(void)
{
  uint8_t KeyValue;
  uint8_t i = 0;
	
  GPIO_SetBits(GPIOA, KEYBOARD_SPI_MISO );
  GPIO_ResetBits(GPIOA, KEYBOARD_SPI_NSS );
	
  do
  {
    KeyValue <<= 1;
    GPIO_ResetBits(GPIOA, KEYBOARD_SPI_SCK );
    GPIO_SetBits(GPIOA, KEYBOARD_SPI_SCK );
    if(GPIO_ReadInputDataBit(GPIOA, KEYBOARD_SPI_MOSI) == 1)
    {
      KeyValue |= 0x01;
    }
    else
    {
      KeyValue &= 0xFE;
    }
    i++;
    uDelay(5);
  }
  while (i < 8);
	
  GPIO_SetBits(GPIOA, KEYBOARD_SPI_NSS );

  if(KeyValue == NO_KEY_INPUT)
    return NO_KEY_INPUT;
  else
    return(KeyValueTable[KeyValue]);
}
