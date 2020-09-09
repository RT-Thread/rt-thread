/**
  ******************************************************************************
  * @file    stm32wlxx_it.c
  * @author  MCD Application Team
  * @brief   Interrupt Service Routines
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32wlxx_it.h"

/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

extern RTC_HandleTypeDef hrtc;
extern UART_HandleTypeDef husart2;
extern SUBGHZ_HandleTypeDef hsubghz;

/* Exported functions --------------------------------------------------------*/
/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */
/******************************************************************************/

void HardFault_Handler(void)
{
  while (1);
}

void SysTick_Handler(void)
{
  HAL_IncTick();
}

/******************************************************************************/
/* STM32WLxx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32wle5xx.s)               */
/******************************************************************************/
void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&husart2);
}


void RTC_Alarm_IRQHandler(void)
{
  HAL_RTC_AlarmIRQHandler(&hrtc);
}



void Radio_IRQHandler(void)
{
  HAL_SUBGHZ_IRQHandler(&hsubghz);
}


void DMA1_Channel5_IRQHandler(void)
{
  HAL_DMA_IRQHandler(husart2.hdmatx);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
