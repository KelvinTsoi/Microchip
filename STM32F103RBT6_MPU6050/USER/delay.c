#include "delay.h"

void Delay_Init()
{
  SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
  SysTick->CTRL = 0X00000000;
  SysTick->VAL = 0X00000000;
}
//extern volatile uint32_t SystemTick;
volatile uint32_t SystemTick;
void DelayMs(__IO uint32_t nTime)
{
  /*
  int i;
  for(i = 0;i<nTime;i++)
  {
  	DelayUs(1000);
  }
  */
#if	0
  uint32_t nDelaySysTick = SystemTick;
  while (SystemTick - nDelaySysTick <= nTime / 10)
  {;}
#endif

#if 1
  u32 temp;
  SysTick->LOAD = 9000 * nTime;
  SysTick->VAL = 0x00;
  SysTick->CTRL = 0x01;
  do
  {
    temp = SysTick->CTRL;
  }
  while ((temp & 0x01) && (!(temp & (1 << 16))));
  SysTick->CTRL = 0x00;
  SysTick->VAL = 0x00;
#endif
}
#if 0
void DelayUs(__IO uint32_t nTime)
{
  /*
  SysTick->LOAD=nTime*6;          //6*8 = 48Ms
  SysTick->CTRL|=0x01;             //????
  while(!(SysTick->CTRL&(1<<16))); //??????
  {
  	__NOP();
  }
  SysTick->CTRL=0X00000000;        //?????
  SysTick->VAL=0X00000000;         //?????
  */

  u32 temp;
  SysTick->LOAD = 9 * nTime;
  SysTick->VAL = 0x00;
  SysTick->CTRL = 0x01;
  do
  {
    temp = SysTick->CTRL;
  }
  while ((temp & 0x01) && (!(temp & (1 << 16))));
  SysTick->CTRL = 0x00;
  SysTick->VAL = 0x00;
}

void uDelay(__IO uint32_t nTime)
{
  uint16_t i, j;
  for(i = 0; i < nTime; i++)
  {
    for(j = 0; j < 4; j++);
  }
}
#endif

void DelayUs(__IO uint32_t nTime)
{
  u32 temp;
  SysTick->LOAD = 9 * nTime;     //设置重装数值, 72MHZ时
  SysTick->CTRL = 0X01;       //使能，减到零是无动作，采用外部时钟源
  SysTick->VAL = 0;              //清零计数器
  do
  {
    temp = SysTick->CTRL;         //读取当前倒计数值
  }
  while((temp & 0x01) && (!(temp & (1 << 16)))); //等待时间到达
  SysTick->CTRL = 0;  //关闭计数器
  SysTick->VAL = 0;      //清空计数器
}

void uDelay(__IO uint32_t nTime)
{
  u32 temp;
  SysTick->LOAD = 9 * nTime;     //设置重装数值, 72MHZ时
  SysTick->CTRL = 0X01;       //使能，减到零是无动作，采用外部时钟源
  SysTick->VAL = 0;              //清零计数器
  do
  {
    temp = SysTick->CTRL;         //读取当前倒计数值
  }
  while((temp & 0x01) && (!(temp & (1 << 16)))); //等待时间到达
  SysTick->CTRL = 0;  //关闭计数器
  SysTick->VAL = 0;      //清空计数器
}


