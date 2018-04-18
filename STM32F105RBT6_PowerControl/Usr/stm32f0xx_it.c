/**
  ******************************************************************************
  * @file    RCC/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    23-March-2012
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "define.h"


/** @addtogroup STM32F0_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup RCC_Example
  * @{
  */ 
	


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
  /* This interrupt is generated when HSE clock fails */

  if (RCC_GetITStatus(RCC_IT_CSS) != RESET)
  {
    /* At this stage: HSE, PLL are disabled (but no change on PLL config) and HSI
       is selected as system clock source */

    /* Enable HSE */
    RCC_HSEConfig(RCC_HSE_ON);

    /* Enable HSE Ready and PLL Ready interrupts */
    RCC_ITConfig(RCC_IT_HSERDY | RCC_IT_PLLRDY, ENABLE);

    /* Clear Clock Security System interrupt pending bit */
    RCC_ClearITPendingBit(RCC_IT_CSS);

    /* Once HSE clock recover, the HSERDY interrupt is generated and in the RCC ISR
       routine the system clock will be reconfigured to its previous state (before
       HSE clock failure) */
  }
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
//void SVC_Handler(void)
//{
//}

///**
//  * @brief  This function handles PendSVC exception.
//  * @param  None
//  * @retval None
//  */
//void PendSV_Handler(void)
//{
//}

///**
//  * @brief  This function handles SysTick Handler.
//  * @param  None
//  * @retval None
//  */
//void SysTick_Handler(void)
//{
//}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles RCC interrupt request. 
  * @param  None
  * @retval None
  */
void RTC_IRQHandler(void)
{
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
    RTC_TimeTypeDef RTC_TimeStructure;
    
    /* Set the time to 00h 00mn 00s AM */
    RTC_TimeStructure.RTC_H12     = RTC_H12_AM;
    RTC_TimeStructure.RTC_Hours   = 0x00;
    RTC_TimeStructure.RTC_Minutes = 0x00;
    RTC_TimeStructure.RTC_Seconds = 0x00;  
  
    RTC_SetTime(RTC_Format_BCD, &RTC_TimeStructure);
    
    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
  } 
}

//void USART1_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
//	{
//		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
//		UartRX[0] = USART_ReceiveData(USART1);
//	}
//}

void DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC1) != RESET)
	{
		DMA_ClearFlag(DMA1_FLAG_TC1);	//清除DMA中断标志位
		
	}
}

//void TIM14_IRQHandler()
//{
//	if(TIM_GetITStatus(TIM14 , TIM_IT_Update) == SET)
//	{
//		TIM_ClearITPendingBit(TIM14,TIM_FLAG_Update);
//	}
//}

void TIM15_IRQHandler()
{
	if(TIM_GetITStatus(TIM15 , TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM15,TIM_FLAG_Update);
	}
}

//void EXTI4_15_IRQHandler(void)
//{
//   if(EXTI_GetITStatus(EXTI_Line4) != RESET)
//	 {
//		  EXTI_ClearITPendingBit(EXTI_Line4); 
//	 }
//	 if(EXTI_GetITStatus(EXTI_Line12) != RESET)
//	 {
//		  EXTI_ClearITPendingBit(EXTI_Line12); 
//	 }
//}






/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
