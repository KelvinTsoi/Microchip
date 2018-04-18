#include "stm32f10x.h"
#include "uart.h"
#include "delay.h"
#include "relay.h"
#include "tim.h"
#include "keyboard.h"
#include "WatchDog.h"
#include "DebugPrintf.h"

#define TriggerInterval 		1	//min
#define TriggerClock				(TriggerInterval * 60 * 1000 / 50)

uint32_t TickerList[RELAY_CHANNELS] = {0};

uint8_t CurrentKey = NO_KEY_INPUT;
uint8_t LastKey1 = NO_KEY_INPUT;
uint8_t LastKey2 = NO_KEY_INPUT;

void KeyboardHandle(void)
{
  CurrentKey = CheckKey();
	
  if(CurrentKey != NO_KEY_INPUT && LastKey1 != CurrentKey && LastKey2 != CurrentKey)
  {
		if(CurrentKey > 0 && CurrentKey < RELAY_CHANNELS+1)
		{
			TickerList[CurrentKey-1] = TriggerClock;
		}
    printf("Tri->%d\r\n", CurrentKey);
  }
	
  LastKey2 = LastKey1;
  LastKey1 = CurrentKey;
}


void TIM3_IRQHandler(void)
{
  uint32_t i = 0;
  if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
    KeyboardHandle();
    RelayHandle();
		
		for(i = 0 ; i < RELAY_CHANNELS; i++)
		{
			TickerList[i]++;
			if(TickerList[i] > TriggerClock)
			{
				printf("R%d Tri\r\n", i+1);
				RelayActive(i, 50);
				TickerList[i] = 0;
			}			
		}
  }
}

uint8_t SystemInitial(void)
{
  SystemCoreClockUpdate();
  Delay_Init();
  //WatchDog_Init();
  RelayInit();
  KeyBoardInit();
  DelayMs(100);
  Key_SenInit();
  TIMER3_Init(50);
  SysTick_Config(SystemCoreClock / 100);
  UART_Print_Init(115200);

  printf("Configure Finished!\r\n");
  printf("SystemCoreClock: %dHz.\r\n", SystemCoreClock);

  return 0x00;
}

int main(void)
{
  if(SystemInitial())
  {
    printf("System Initial Failed\r\n");
  }
  else
  {
    printf("System Initial Successed\r\n");
  }

  while(1)
  {
		;
  }
}
