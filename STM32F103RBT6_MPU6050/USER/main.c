/**
  ******************************************************************************
  * @author  Kelvin Tsoi
  * @version V1.0.06
  * @date    08-April-2018
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include "delay.h"
#include "usart.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"

#include <stdio.h>

/* Private functions ---------------------------------------------------------*/

uint8_t UART1TxBuffer[MAX_UART1_TX_BUFFER_SIZE];

uint8_t g_IsUartTxBusy = 0;

uint32_t g_byDmaBufferCurrentTab = 0;

float pitch, roll, yaw = 0;

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{	
	int ret = 0;

	delay_init();
	
	USART1_Init(115200);

  if((ret=MPU_Init())!=0)
	{
		//printf("MPU6050 Init Error! Error code [%d]\r\n", ret);
		assert_failed((uint8_t *)__FILE__, __LINE__);
	}

  while((ret=mpu_dmp_init())!=0)
  {
    //printf("MPU6050 DMP Init Error! Error code [%d], Try again!\r\n");
    delay_ms(200);
  }

  /* Infinite loop */
  while (1)
  {
    if(mpu_dmp_get_data(&pitch, &roll, &yaw) == 0)
    {
			Encode(LEFT_HAND_SIDE, pitch, roll, yaw, UART1TxBuffer);
			SendMsg(UART1TxBuffer, sizeof(UART1TxBuffer));
    }
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
