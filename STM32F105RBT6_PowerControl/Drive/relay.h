#include "stm32f10x.h"

#define RELAY_CHANNELS 16

typedef struct{
	uint32_t GPIO_CLOCK;
  GPIO_TypeDef* GPIOx;
  uint16_t GPIO_Pin;
}TargetPin;

void RelayInit(void);
void RelayHandle(void); 
void RelayActive(uint8_t channel, uint8_t interval);
void RelayOn(const TargetPin channel);
void RelayOff(const TargetPin channel);

