/**
  ******************************************************************************
  * @file    Project/Template/stm32f10x_it.h
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_IT_H
#define __STM32F10x_IT_H

#ifdef __cplusplus
extern "C"
{
#endif

    /* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

    /* Exported types ------------------------------------------------------------*/
    /* Exported constants --------------------------------------------------------*/
    /* Exported macro ------------------------------------------------------------*/
    /* Exported functions ------------------------------------------------------- */

    void NMI_Handler(void);
    void HardFault_Handler(void);
    void MemManage_Handler(void);
    void BusFault_Handler(void);
    void UsageFault_Handler(void);
    void SVC_Handler(void);
    void DebugMon_Handler(void);
    void PendSV_Handler(void);
    void SysTick_Handler(void);

    void NMIException(void);
    void HardFaultException(void);
    void MemManageException(void);
    void BusFaultException(void);
    void UsageFaultException(void);
    void DebugMonitor(void);
    void SVCHandler(void);
    void PendSVC(void);
    void SysTickHandler(void);
    void WWDG_IRQHandler(void);
    void PVD_IRQHandler(void);
    void TAMPER_IRQHandler(void);
    void RTC_IRQHandler(void);
    void FLASH_IRQHandler(void);
    void RCC_IRQHandler(void);
    void EXTI0_IRQHandler(void);
    void EXTI1_IRQHandler(void);
    void EXTI2_IRQHandler(void);
    void EXTI3_IRQHandler(void);
    void EXTI4_IRQHandler(void);
    void DMA1_Channel1_IRQHandler(void);
    void DMA1_Channel2_IRQHandler(void);
    void DMA1_Channel3_IRQHandler(void);
    void DMA1_Channel4_IRQHandler(void);
    void DMA1_Channel5_IRQHandler(void);
    void DMA1_Channel6_IRQHandler(void);
    void DMA1_Channel7_IRQHandler(void);
    void ADC1_2_IRQHandler(void);
    void USB_HP_CAN_TX_IRQHandler(void);
    void USB_LP_CAN_RX0_IRQHandler(void);
    void CAN_RX1_IRQHandler(void);
    void CAN_SCE_IRQHandler(void);
    void EXTI9_5_IRQHandler(void);
    void TIM1_BRK_IRQHandler(void);
    void TIM1_UP_IRQHandler(void);
    void TIM1_TRG_COM_IRQHandler(void);
    void TIM1_CC_IRQHandler(void);
    void TIM2_IRQHandler(void);
    void TIM3_IRQHandler(void);
    void TIM4_IRQHandler(void);
    void I2C1_EV_IRQHandler(void);
    void I2C1_ER_IRQHandler(void);
    void I2C2_EV_IRQHandler(void);
    void I2C2_ER_IRQHandler(void);
    void SPI1_IRQHandler(void);
    void SPI2_IRQHandler(void);
    void USART1_IRQHandler(void);
    void USART2_IRQHandler(void);
    void USART3_IRQHandler(void);
    void EXTI15_10_IRQHandler(void);
    void RTCAlarm_IRQHandler(void);
    void USBWakeUp_IRQHandler(void);
    void TIM8_BRK_IRQHandler(void);
    void TIM8_UP_IRQHandler(void);
    void TIM8_TRG_COM_IRQHandler(void);
    void TIM8_CC_IRQHandler(void);
    void ADC3_IRQHandler(void);
    void FSMC_IRQHandler(void);
    void SDIO_IRQHandler(void);
    void TIM5_IRQHandler(void);
    void SPI3_IRQHandler(void);
    void UART4_IRQHandler(void);
    void UART5_IRQHandler(void);
    void TIM6_IRQHandler(void);
    void TIM7_IRQHandler(void);
    void DMA2_Channel1_IRQHandler(void);
    void DMA2_Channel2_IRQHandler(void);
    void DMA2_Channel3_IRQHandler(void);
    void DMA2_Channel4_5_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_IT_H */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
