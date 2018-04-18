#include "TIM.h"

void TIM3_PWM_Init(int CCR1)  						
{  
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);   
	TIM_TimeBaseStructure.TIM_Prescaler = 72-1;//
	TIM_TimeBaseStructure.TIM_Period = 20000-1;    
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);  
	
	TIM_ARRPreloadConfig(TIM3, DISABLE); 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
 
	TIM_OCInitStructure.TIM_Pulse = CCR1-1;     
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
	TIM_CtrlPWMOutputs(TIM3,ENABLE); 
	TIM_ARRPreloadConfig(TIM3, ENABLE);
	TIM_Cmd(TIM3, ENABLE);  
} 
