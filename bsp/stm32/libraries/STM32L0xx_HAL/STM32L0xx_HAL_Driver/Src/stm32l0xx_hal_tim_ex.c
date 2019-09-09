/**
  ******************************************************************************
  * @file    stm32l0xx_hal_tim_ex.c
  * @author  MCD Application Team
  * @brief   TIM HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Timer Extended peripheral:
  *           + Time Master and Slave synchronization configuration
  *           + Timer remapping capabilities configuration
  @verbatim
  ==============================================================================
                      ##### TIMER Extended features #####
  ==============================================================================
  [..]
    The Timer Extended features include:
    (#) Synchronization circuit to control the timer with external signals and to
        interconnect several timers together.

  @endverbatim
  ******************************************************************************
    * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup TIMEx TIMEx
  * @brief TIM Extended HAL module driver
  * @{
  */

#ifdef HAL_TIM_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup TIMEx_Exported_Functions TIM Extended Exported Functions
  * @{
  */
/** @defgroup TIMEx_Exported_Functions_Group5 Extended Peripheral Control functions
  * @brief    Peripheral Control functions
  *
@verbatim
  ==============================================================================
                    ##### Peripheral Control functions #####
  ==============================================================================
  [..]
    This section provides functions allowing to:
      (+) Configure Master synchronization.
      (+) Configure timer remapping capabilities.

@endverbatim
  * @{
  */

/**
  * @brief  Configures the TIM in master mode.
  * @param  htim TIM handle.
  * @param  sMasterConfig pointer to a TIM_MasterConfigTypeDef structure that
  *         contains the selected trigger output (TRGO) and the Master/Slave
  *         mode.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TIMEx_MasterConfigSynchronization(TIM_HandleTypeDef *htim,
                                                        TIM_MasterConfigTypeDef *sMasterConfig)
{
  uint32_t tmpcr2;
  uint32_t tmpsmcr;

  /* Check the parameters */
  assert_param(IS_TIM_SYNCHRO_INSTANCE(htim->Instance));
  assert_param(IS_TIM_TRGO_SOURCE(sMasterConfig->MasterOutputTrigger));
  assert_param(IS_TIM_MSM_STATE(sMasterConfig->MasterSlaveMode));

  /* Check input state */
  __HAL_LOCK(htim);

  /* Change the handler state */
  htim->State = HAL_TIM_STATE_BUSY;

  /* Get the TIMx CR2 register value */
  tmpcr2 = htim->Instance->CR2;

  /* Get the TIMx SMCR register value */
  tmpsmcr = htim->Instance->SMCR;

  /* Reset the MMS Bits */
  tmpcr2 &= ~TIM_CR2_MMS;
  /* Select the TRGO source */
  tmpcr2 |=  sMasterConfig->MasterOutputTrigger;

  /* Reset the MSM Bit */
  tmpsmcr &= ~TIM_SMCR_MSM;
  /* Set master mode */
  tmpsmcr |= sMasterConfig->MasterSlaveMode;

  /* Update TIMx CR2 */
  htim->Instance->CR2 = tmpcr2;

  /* Update TIMx SMCR */
  htim->Instance->SMCR = tmpsmcr;

  /* Change the htim state */
  htim->State = HAL_TIM_STATE_READY;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

/**
  * @brief  Configures the TIMx Remapping input capabilities.
  @if STM32L073xx
  * @note   It is not possible to connect TIM2 and TIM21 on PB5(AF4) at the same time.
  *         When selecting TIM3_TI2_GPIOB5_AF4, Channel2 of TIM3 will be
  *         connected to PB5(AF4) and Channel2 of TIM21 will be connected to
  *         some other GPIOs. (refer to alternate functions for more details)
  *         When selecting TIM3_TI2_GPIO_DEF, Channel2 of Timer 3 will be
  *         connected an GPIO (other than PB5(AF4)) and Channel2 of TIM21
  *         will be connected to PB5(AF4).
  * @note   When TIM2 ETR is fed with HSI48, this ETR must be prescaled internally
  *         to the TIMER2 because the maximum system frequency is 32 MHz
  @endif
  * @param  htim TIM handle.
  * @param  Remap specifies the TIM remapping source.
  @if STM32L073xx
  *         For TIM2, the parameter is a combination of 2 fields (field1 | field2):
  *
  *                   field1 can have the following values:
  *           @arg TIM2_ETR_GPIO:      TIM2  ETR connected to GPIO (default):
  *                                    PA0(AF5) or PA5(AF2) or PA15(AF2) or PE9(AF2)
  *           @arg TIM2_ETR_HSI48:     TIM2  ETR connected to HSI48
  *           @arg TIM2_ETR_HSI16:     TIM2  ETR connected to HSI16
  *           @arg TIM2_ETR_LSE:       TIM2  ETR connected to LSE
  *           @arg TIM2_ETR_COMP2_OUT: TIM2  ETR connected to COMP2 output
  *           @arg TIM2_ETR_COMP1_OUT: TIM2  ETR connected to COMP1 output
  *
  *                   field2 can have the following values:
  *           @arg TIM2_TI4_GPIO :     TIM2  TI4 connected to GPIO1(default):
  *                                    PA3(AF2) or PB11(AF2) or PE12(AF0)
  *           @arg TIM2_TI4_COMP1:     TIM2  TI4 connected to COMP1
  *           @arg TIM2_TI4_COMP2:     TIM2  TI4 connected to COMP2
  @endif
  @if STM32L031xx
  *         For TIM2, the parameter is a combination of 2 fields (field1 | field2):
  *
  *                   field1 can have the following values:
  *           @arg TIM2_ETR_GPIO:      TIM2  ETR connected to GPIO (default):
  *                                    PA0(AF5) or PA5(AF2) or PA15(AF2)
  *           @arg TIM2_ETR_HSI16:     TIM2  ETR connected to HS16 (HSIOUT)
  *           @arg TIM2_ETR_LSE:       TIM2  ETR connected to LSE
  *           @arg TIM2_ETR_COMP2_OUT: TIM2  ETR connected to COMP2 output
  *           @arg TIM2_ETR_COMP1_OUT: TIM2  ETR connected to COMP1 output
  *
  *                   field2 can have the following values:
  *           @arg TIM2_TI4_GPIO :     TIM2  TI4 connected to GPIO (default):
  *                                    PA3(AF2) or PB11(AF2) or PB1(AF5)
  *           @arg TIM2_TI4_COMP1_OUT: TIM2  TI4 connected to COMP1 output
  *           @arg TIM2_TI4_COMP2_OUT: TIM2  TI4 connected to COMP2 output
  @endif
  @if STM32L011xx
  *         For TIM2, the parameter is a combination of 2 fields (field1 | field2):
  *
  *                   field1 can have the following values:
  *           @arg TIM2_ETR_GPIO:      TIM2  ETR connected to GPIO (default):
  *                                    PA0(AF5) or PA5(AF2) or PA15(AF2)
  *           @arg TIM2_ETR_HSI16:     TIM2  ETR connected to HS16 (HSIOUT)
  *           @arg TIM2_ETR_LSE:       TIM2  ETR connected to LSE
  *           @arg TIM2_ETR_COMP2_OUT: TIM2  ETR connected to COMP2 output
  *           @arg TIM2_ETR_COMP1_OUT: TIM2  ETR connected to COMP1 output
  *
  *                   field2 can have the following values:
  *           @arg TIM2_TI4_GPIO :     TIM2  TI4 connected to GPIO (default):
  *                                    PA3(AF2) or PB11(AF2) or PB1(AF5)
  *           @arg TIM2_TI4_COMP1_OUT: TIM2  TI4 connected to COMP1 output
  *           @arg TIM2_TI4_COMP2_OUT: TIM2  TI4 connected to COMP2 output
  @endif
  @if STM32L051xx
  *         For TIM2, the parameter is a combination of 2 fields (field1 | field2):
  *
  *                   field1 can have the following values:
  *           @arg TIM2_ETR_GPIO:      TIM2  ETR connected to GPIO (default):
  *                                    PA0(AF5) or PA5(AF2) or PA15(AF2) or PE9(AF2)
  *           @arg TIM2_ETR_HSI48:     TIM2  ETR connected to HSI48
  *           @arg TIM2_ETR_LSE:       TIM2  ETR connected to LSE
  *           @arg TIM2_ETR_COMP2_OUT: TIM2  ETR connected to COMP2 output
  *           @arg TIM2_ETR_COMP1_OUT: TIM2  ETR connected to COMP1 output
  *
  *                   field2 can have the following values:
  *           @arg TIM2_TI4_GPIO:      TIM2  TI4 connected to GPIO1(default):
  *                                    PA3(AF2) or PB11(AF2) or PE12(AF0)
  *           @arg TIM2_TI4_COMP1:     TIM2  TI4 connected to COMP1
  *           @arg TIM2_TI4_COMP2:     TIM2  TI4 connected to COMP2
  *           @arg TIM2_TI4_GPIO2:     TIM2  TI4 connected to GPIO2 :
  *                                    PA3(AF2) or PB11(AF2) or PE12(AF0)
  @endif
  @if STM32L073xx
  *
  *         For TIM3, the parameter is a combination of 4 fields (field1 | field2 | field3 | field4):
  *
  *                   field1 can have the following values:
  *           @arg TIM3_ETR_GPIO:      TIM3  ETR connected to GPIO (default):
  *                                    PE2(AF2) or PD2(AF2) or PE2(AF2)
  *           @arg TIM3_ETR_HSI:       TIM3 ETR connected to HSI
  *
  *                   field2 can have the following values:
  *           @arg TIM3_TI1_USB_SOF:   TIM3 TI1 connected to USB_SOF (default)
  *           @arg TIM3_TI1_GPIO:      TIM3 TI1 connected to GPIO :
  *                                    PE3(AF2) or PA6(AF2) or PC6(AF2) or PB4(AF2)
  *
  *                   field3 can have the following values:
  *           @arg TIM3_TI2_GPIOB5_AF4:TIM3 TI3 connected to P5(AF4)
  *                                    (refer to note)
  *           @arg TIM3_TI2_GPIO_DEF:  TIM3 TI3 connected to GPIO (default):
  *                                    PA7(AF2) or PB5(AF4) or PC7(AF2) or PE7(AF2)
  *
  *                   field4 can have the following values:
  *           @arg TIM3_TI4_GPIO_DEF:  TIM3 TI4 connected to GPIO:
  *                                    PB1(AF2) or PE6(AF2)
  *           @arg TIM3_TI4_GPIOC9_AF2:TIM3 TI4 connected to PC9(AF)2
  @endif
  @if STM32L073xx
  *         For TIM21, the parameter is a combination of 3 fields (field1 | field2 | field3):
  *
  *                   field1 can have the following values:
  *           @arg TIM21_ETR_GPIO:     TIM21 ETR connected to GPIO(default) :
  *                                    PC9(AF0) or PA1(AF5)
  *           @arg TIM21_ETR_COMP2_OUT:TIM21 ETR connected to COMP2 output
  *           @arg TIM21_ETR_COMP1_OUT:TIM21 ETR connected to COMP1 output
  *           @arg TIM21_ETR_LSE:      TIM21 ETR connected to LSE
  *
  *                   field2 can have the following values:
  *           @arg TIM21_TI1_MCO:      TIM21 TI1 connected to MCO
  *           @arg TIM21_TI1_RTC_WKUT_IT: TIM21 TI1 connected to RTC WAKEUP interrupt
  *           @arg TIM21_TI1_HSE_RTC:  TIM21 TI1 connected to HSE_RTC
  *           @arg TIM21_TI1_MSI:      TIM21 TI1 connected to MSI clock
  *           @arg TIM21_TI1_LSE:      TIM21 TI1 connected to LSE
  *           @arg TIM21_TI1_LSI:      TIM21 TI1 connected to LSI
  *           @arg TIM21_TI1_COMP1_OUT:TIM21 TI1 connected to COMP1_OUT
  *           @arg TIM21_TI1_GPIO:     TIM21 TI1 connected to GPIO(default):
  *                                    PA2(AF0) or PB13(AF6) or PE5(AF0) or PD0(AF0)
  *
  *                   field3 can have the following values:
  *           @arg TIM21_TI2_GPIO:     TIM21 TI2 connected to GPIO(default):
  *                                    PA3(AF0) or PB14(AF6) or PE6(AF0) or PD7(AF1)
  *           @arg TIM21_TI2_COMP2_OUT:TIM21 TI2 connected to COMP2 output
  @endif
  @if STM32L031xx
  *         For TIM21, the parameter is a combination of 3 fields (field1 | field2 | field3):
  *
  *                   field1 can have the following values:
  *           @arg TIM21_ETR_GPIO:     TIM21 ETR connected to GPIO(default) :
  *                                    PA1(AF5)
  *           @arg TIM21_ETR_COMP2_OUT:TIM21 ETR connected to COMP2 output
  *           @arg TIM21_ETR_COMP1_OUT:TIM21 ETR connected to COMP1 output
  *           @arg TIM21_ETR_LSE:      TIM21 ETR connected to LSE
  *
  *                   field2 can have the following values:
  *           @arg TIM21_TI1_MCO:      TIM21 TI1 connected to MCO
  *           @arg TIM21_TI1_RTC_WKUT_IT: TIM21 TI1 connected to RTC WAKEUP interrupt
  *           @arg TIM21_TI1_HSE_RTC:  TIM21 TI1 connected to HSE_RTC
  *           @arg TIM21_TI1_MSI:      TIM21 TI1 connected to MSI clock
  *           @arg TIM21_TI1_LSE:      TIM21 TI1 connected to LSE
  *           @arg TIM21_TI1_LSI:      TIM21 TI1 connected to LSI
  *           @arg TIM21_TI1_COMP1_OUT:TIM21 TI1 connected to COMP1_OUT
  *
  *                   field3 can have the following values:
  *           @arg TIM21_TI2_GPIO:     TIM21 TI2 connected to GPIO(default):
  *                                    PA3(AF0) or PB14(AF6)
  *           @arg TIM21_TI2_COMP2_OUT:TIM21 TI2 connected to COMP2 output
  @endif
  @if STM32L011xx
  *         For TIM21, the parameter is a combination of 3 fields (field1 | field2 | field3):
  *
  *                   field1 can have the following values:
  *           @arg TIM21_ETR_GPIO:     TIM21 ETR connected to GPIO(default) :
  *                                    PA1(AF5)
  *           @arg TIM21_ETR_COMP2_OUT:TIM21 ETR connected to COMP2 output
  *           @arg TIM21_ETR_COMP1_OUT:TIM21 ETR connected to COMP1 output
  *           @arg TIM21_ETR_LSE:      TIM21 ETR connected to LSE
  *
  *                   field2 can have the following values:
  *           @arg TIM21_TI1_MCO:      TIM21 TI1 connected to MCO
  *           @arg TIM21_TI1_RTC_WKUT_IT: TIM21 TI1 connected to RTC WAKEUP interrupt
  *           @arg TIM21_TI1_HSE_RTC:  TIM21 TI1 connected to HSE_RTC
  *           @arg TIM21_TI1_MSI:      TIM21 TI1 connected to MSI clock
  *           @arg TIM21_TI1_LSE:      TIM21 TI1 connected to LSE
  *           @arg TIM21_TI1_LSI:      TIM21 TI1 connected to LSI
  *           @arg TIM21_TI1_COMP1_OUT:TIM21 TI1 connected to COMP1_OUT
  *
  *                   field3 can have the following values:
  *           @arg TIM21_TI2_GPIO:     TIM21 TI2 connected to GPIO(default):
  *                                    PA3(AF0) or PB14(AF6)
  *           @arg TIM21_TI2_COMP2_OUT:TIM21 TI2 connected to COMP2 output
  @endif
  @if STM32L051xx
  *         For TIM21, the parameter is a combination of 3 fields (field1 | field2 | field3):
  *
  *                   field1 can have the following values:
  *           @arg TIM21_ETR_GPIO:     TIM21 ETR connected to GPIO(default) :
  *                                    PC9(AF0) or PA1(AF5)
  *           @arg TIM21_ETR_COMP2_OUT:TIM21 ETR connected to COMP2 output
  *           @arg TIM21_ETR_COMP1_OUT:TIM21 ETR connected to COMP1 output
  *           @arg TIM21_ETR_LSE:      TIM21 ETR connected to LSE
  *
  *                   field2 can have the following values:
  *           @arg TIM21_TI1_MCO:      TIM21 TI1 connected to MCO
  *           @arg TIM21_TI1_RTC_WKUT_IT: TIM21 TI1 connected to RTC WAKEUP interrupt
  *           @arg TIM21_TI1_HSE_RTC:  TIM21 TI1 connected to HSE_RTC
  *           @arg TIM21_TI1_MSI:      TIM21 TI1 connected to MSI clock
  *           @arg TIM21_TI1_LSE:      TIM21 TI1 connected to LSE
  *           @arg TIM21_TI1_LSI:      TIM21 TI1 connected to LSI
  *           @arg TIM21_TI1_COMP1_OUT:TIM21 TI1 connected to COMP1_OUT
  *           @arg TIM21_TI1_GPIO:     TIM21 TI1 connected to GPIO(default):
  *                                    PA2(AF0) or PB13(AF6) or PE5(AF0) or PD0(AF0)
  *
  *                   field3 can have the following values:
  *           @arg TIM21_TI2_GPIO:     TIM21 TI2 connected to GPIO(default):
  *                                    PA3(AF0) or PB14(AF6) or PE6(AF0) or PD7(AF1)
  *           @arg TIM21_TI2_COMP2_OUT:TIM21 TI2 connected to COMP2 output
  @endif
  @if STM32L073xx
  *
  *         For TIM22, the parameter can have the following values:
  *           @arg TIM22_ETR_LSE:      TIM22 ETR connected to LSE
  *           @arg TIM22_ETR_COMP2_OUT:TIM22 ETR connected to COMP2 output
  *           @arg TIM22_ETR_COMP1_OUT:TIM22 ETR connected to COMP1 output
  *           @arg TIM22_ETR_GPIO:     TIM22 ETR connected to GPIO(default):
  *                                    PC8(AF0) or PA4(AF5)
  *           @arg TIM22_TI1_GPIO:     TIM22 TI1 connected to GPIO(default):
  *                                    PC6(AF0) or PA6(AF5) or PB4(AF4) or PE0(AF3)
  *           @arg TIM22_TI1_COMP2_OUT:TIM22 TI1 connected to COMP2 output
  *           @arg TIM22_TI1_COMP1_OUT:TIM22 TI1 connected to COMP1 output
  @endif
  @if STM32L031xx
  *
  *         For TIM22, the parameter is a combination of 2 fields (field1 | field2):
  *
  *                   field1 can have the following values:
  *           @arg TIM22_ETR_LSE:      TIM22 ETR connected to LSE
  *           @arg TIM22_ETR_COMP2_OUT:TIM22 ETR connected to COMP2 output
  *           @arg TIM22_ETR_COMP1_OUT:TIM22 ETR connected to COMP1 output
  *           @arg TIM22_ETR_GPIO:     TIM22 ETR connected to GPIO(default):
  *                                    PA4(AF5)
  *
  *                   field2 can have the following values:
  *           @arg TIM22_TI1_GPIO:     TIM22 TI1 connected to GPIO(default):
  *                                    PC0(AF6) or PA5(AF6) or PB4(AF4)
  *           @arg TIM22_TI1_COMP2_OUT:TIM22 TI1 connected to COMP2 output
  *           @arg TIM22_TI1_COMP1_OUT:TIM22 TI1 connected to COMP1 output
  *
  @endif
  @if STM32L051xx
  *
  *         For TIM22, the parameter is a combination of 2 fields (field1 | field2):
  *
  *                   field1 can have the following values:
  *           @arg TIM22_ETR_LSE:      TIM22 ETR connected to LSE
  *           @arg TIM22_ETR_COMP2_OUT:TIM22 ETR connected to COMP2 output
  *           @arg TIM22_ETR_COMP1_OUT:TIM22 ETR connected to COMP1 output
  *           @arg TIM22_ETR_GPIO:     TIM22 ETR connected to GPIO(default):
  *                                    PC8(AF0) or PA4(AF5)
  *
  *                   field2 can have the following values:
  *           @arg TIM22_TI1_GPIO:     TIM22 TI1 connected to GPIO(default):
  *                                    PC6(AF0) or PA6(AF5) or PB4(AF4) or PE0(AF3)
  *           @arg TIM22_TI1_COMP2_OUT:TIM22 TI1 connected to COMP2 output
  *           @arg TIM22_TI1_COMP1_OUT:TIM22 TI1 connected to COMP1 output
  @endif
  *
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_TIMEx_RemapConfig(TIM_HandleTypeDef *htim, uint32_t Remap)
{
  __HAL_LOCK(htim);

  /* Check parameters */
  assert_param(IS_TIM_REMAP(htim->Instance, Remap));

  /* Set the Timer remapping configuration */
  WRITE_REG(htim->Instance->OR, Remap);

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

/**
  * @}
  */

/**
  * @}
  */


#endif /* HAL_TIM_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
