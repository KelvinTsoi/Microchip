#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "stm32f10x.h"

#define NO_KEY_INPUT 0xff

void Key_SenInit(void);
uint8_t CheckKey(void);
void KeyBoardInit(void);

#define KEYBOARD_SPI_PORT    GPIOA

#define KEYBOARD_SPI_NSS     GPIO_Pin_4
#define KEYBOARD_SPI_SCK     GPIO_Pin_5
#define KEYBOARD_SPI_MOSI    GPIO_Pin_7
#define KEYBOARD_SPI_MISO    GPIO_Pin_6

#endif
