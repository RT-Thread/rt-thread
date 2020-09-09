/**
  ******************************************************************************
  * @file    stm32wlxx_it.h
  * @author  MCD Application Team
  * @brief   contains the headers of the interrupt handlers
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32WLxx_IT_H
#define __STM32WLxx_IT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void Radio_IRQHandler(void);

/**
 * @brief  This function handles SysTick Handler.
 * @param  None
 * @retval None
 */
void SysTick_Handler(void);


/**
  * @brief This function handles DMA1 channel1 global interrupt of ADC
  * @param none
  * @retval none
*/
void DMA1_Channel1_IRQHandler(void);

/**
  * @brief This function handles USARTx_DMA_TX_IRQHandler of USART2 global interrupt
  * @param none
  * @retval none
*/
void DMA1_Channel5_IRQHandler(void);


/**
  * @brief This function handles DMA1 channel7 global interrupt
  * @param none
  * @retval none
*/
void DMA1_Channel7_IRQHandler(void);

/**
  * @brief This function handles USART2 global interrupt
  * @param none
  * @retval none
*/
void USART2_IRQHandler(void);

/**
  * @brief This function handles RTC Alarm global interrupt
  * @param none
  * @retval none
*/
void RTC_Alarm_IRQHandler(void);


#ifdef __cplusplus
}
#endif

#endif /* __STM32WLxx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
