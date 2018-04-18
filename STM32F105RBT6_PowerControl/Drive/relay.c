#include "relay.h"
#include "delay.h"

static uint8_t relayOnLastTime[RELAY_CHANNELS];

TargetPin RelayGpioList[RELAY_CHANNELS] = {
																					{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_0}, {RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_1},
																					{RCC_APB2Periph_GPIOA, GPIOA, GPIO_Pin_12},
																					{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_5}, {RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_6},
																					{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_7}, {RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_8},
																					{RCC_APB2Periph_GPIOB, GPIOB, GPIO_Pin_9}, {RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_0},
																					{RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_1}, {RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_2},
																					{RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_3}, {RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_10},
																					{RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_11}, {RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_12},
																					{RCC_APB2Periph_GPIOC, GPIOC, GPIO_Pin_13}
																					};

void RelayInit()
{	
	uint32_t i = 0;
	GPIO_InitTypeDef GPIO_InitStruct;
	for(; i < RELAY_CHANNELS; i++)
	{
		RCC_APB2PeriphClockCmd(RelayGpioList[i].GPIO_CLOCK, ENABLE);
		GPIO_InitStruct.GPIO_Pin = RelayGpioList[i].GPIO_Pin;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(RelayGpioList[i].GPIOx, &GPIO_InitStruct);
		GPIO_SetBits(RelayGpioList[i].GPIOx, RelayGpioList[i].GPIO_Pin);
		relayOnLastTime[i] = 0;
		DelayMs(5);
	}
}

void RelayHandle()
{
	uint32_t i = 0;
	for(; i < RELAY_CHANNELS; i++)
	{
		if(relayOnLastTime[i] > 0)
		{
			relayOnLastTime[i]--;
		}
		else
		{
			RelayOff(RelayGpioList[i]);
			relayOnLastTime[i] = 0;
		}
	}
}

void RelayActive(uint8_t channel, uint8_t interval)
{
	//Time = 50ms * interval
	relayOnLastTime[channel] = interval;
	RelayOn(RelayGpioList[channel]);
}

void RelayOn(const TargetPin channel)
{
	GPIO_ResetBits(channel.GPIOx, channel.GPIO_Pin);
}

void RelayOff(const TargetPin channel)
{
	GPIO_SetBits(channel.GPIOx, channel.GPIO_Pin);
}
