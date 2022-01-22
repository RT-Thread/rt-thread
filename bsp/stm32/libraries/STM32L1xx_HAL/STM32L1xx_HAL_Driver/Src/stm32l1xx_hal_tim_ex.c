/**
  ******************************************************************************
  * @file    stm32l1xx_hal_tim_ex.c
  * @author  MCD Application Team
  * @brief   TIM HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Timer Extended peripheral:
  *           + Time Master and Slave synchronization configuration
  *           + Time OCRef clear configuration
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
#include "stm32l1xx_hal.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @defgroup TIMEx TIMEx
  * @brief TIM Extended HAL module driver
  * @{
  */

#ifdef HAL_TIM_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
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
  assert_param(IS_TIM_MASTER_INSTANCE(htim->Instance));
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

  /* Update TIMx CR2 */
  htim->Instance->CR2 = tmpcr2;

  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    /* Reset the MSM Bit */
    tmpsmcr &= ~TIM_SMCR_MSM;
    /* Set master mode */
    tmpsmcr |= sMasterConfig->MasterSlaveMode;

    /* Update TIMx SMCR */
    htim->Instance->SMCR = tmpsmcr;
  }

  /* Change the htim state */
  htim->State = HAL_TIM_STATE_READY;

  __HAL_UNLOCK(htim);

  return HAL_OK;
}

/**
  * @brief  Configures the TIMx Remapping input capabilities.
  * @param  htim TIM handle.
  * @param  Remap specifies the TIM remapping source.
  *
  *         For TIM2, the parameter can have the following values:(see note)
  *            @arg TIM_TIM2_ITR1_TIM10_OC:      TIM2 ITR1 input is connected to TIM10 OC
  *            @arg TIM_TIM2_ITR1_TIM5_TGO:      TIM2 ITR1 input is connected to TIM5 TGO
  *
  *         For TIM3, the parameter can have the following values:(see note)
  *            @arg TIM_TIM3_ITR2_TIM11_OC:      TIM3 ITR2 input is connected to TIM11 OC
  *            @arg TIM_TIM3_ITR2_TIM5_TGO:      TIM3 ITR2 input is connected to TIM5 TGO
  *
  *         For TIM9, the parameter is a combination of 2 fields (field1 | field2):
  *
  *                   field1 can have the following values:(see note)
  *            @arg TIM_TIM9_ITR1_TIM3_TGO:      TIM9 ITR1 input is connected to TIM3 TGO
  *            @arg TIM_TIM9_ITR1_TS:            TIM9 ITR1 input is connected to touch sensing I/O
  *
  *                   field2 can have the following values:
  *            @arg TIM_TIM9_GPIO:               TIM9 Channel1 is connected to GPIO
  *            @arg TIM_TIM9_LSE:                TIM9 Channel1 is connected to LSE internal clock
  *            @arg TIM_TIM9_GPIO1:              TIM9 Channel1 is connected to GPIO
  *            @arg TIM_TIM9_GPIO2:              TIM9 Channel1 is connected to GPIO
  *
  *         For TIM10, the parameter is a combination of 3 fields (field1 | field2 | field3):
  *
  *                   field1 can have the following values:(see note)
  *            @arg TIM_TIM10_TI1RMP:            TIM10 Channel 1 depends on TI1_RMP
  *            @arg TIM_TIM10_RI:                TIM10 Channel 1 is connected to RI
  *
  *                   field2 can have the following values:(see note)
  *            @arg TIM_TIM10_ETR_LSE:           TIM10 ETR input is connected to LSE clock
  *            @arg TIM_TIM10_ETR_TIM9_TGO:      TIM10 ETR input is connected to TIM9 TGO
  *
  *                   field3 can have the following values:
  *            @arg TIM_TIM10_GPIO:              TIM10 Channel1 is connected to GPIO
  *            @arg TIM_TIM10_LSI:               TIM10 Channel1 is connected to LSI internal clock
  *            @arg TIM_TIM10_LSE:               TIM10 Channel1 is connected to LSE internal clock
  *            @arg TIM_TIM10_RTC:               TIM10 Channel1 is connected to RTC wakeup interrupt
  *
  *         For TIM11, the parameter is a combination of 3 fields (field1 | field2 | field3):
  *
  *                   field1 can have the following values:(see note)
  *            @arg TIM_TIM11_TI1RMP:            TIM11 Channel 1 depends on TI1_RMP
  *            @arg TIM_TIM11_RI:                TIM11 Channel 1 is connected to RI
  *
  *                   field2 can have the following values:(see note)
  *            @arg TIM_TIM11_ETR_LSE:           TIM11 ETR input is connected to LSE clock
  *            @arg TIM_TIM11_ETR_TIM9_TGO:      TIM11 ETR input is connected to TIM9 TGO
  *
  *                   field3 can have the following values:
  *            @arg TIM_TIM11_GPIO:     TIM11 Channel1 is connected to GPIO
  *            @arg TIM_TIM11_MSI:      TIM11 Channel1 is connected to MSI internal clock
  *            @arg TIM_TIM11_HSE_RTC:  TIM11 Channel1 is connected to HSE_RTC clock
  *            @arg TIM_TIM11_GPIO1:    TIM11 Channel1 is connected to GPIO
  *
  * @note   Available only in Cat.3, Cat.4,Cat.5 and Cat.6 devices.
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
