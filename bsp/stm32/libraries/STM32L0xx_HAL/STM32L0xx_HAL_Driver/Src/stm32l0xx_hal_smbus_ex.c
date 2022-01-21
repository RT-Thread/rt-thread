/**
  ******************************************************************************
  * @file    stm32l0xx_hal_smbus_ex.c
  * @author  MCD Application Team
  * @brief   SMBUS Extended HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of SMBUS Extended peripheral:
  *           + Extended features functions
  *
  @verbatim
  ==============================================================================
               ##### SMBUS peripheral Extended features  #####
  ==============================================================================

  [..] Comparing to other previous devices, the SMBUS interface for STM32L0xx
       devices contains the following additional features

       (+) Disable or enable wakeup from Stop mode(s)
       (+) Disable or enable Fast Mode Plus

                     ##### How to use this driver #####
  ==============================================================================
    (#) Configure the enable or disable of SMBUS Wake Up Mode using the functions :
          (++) HAL_SMBUSEx_EnableWakeUp()
          (++) HAL_SMBUSEx_DisableWakeUp()
    (#) Configure the enable or disable of fast mode plus driving capability using the functions :
          (++) HAL_SMBUSEx_EnableFastModePlus()
          (++) HAL_SMBUSEx_DisableFastModePlus()
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

/** @defgroup SMBUSEx SMBUSEx
  * @brief SMBUS Extended HAL module driver
  * @{
  */

#ifdef HAL_SMBUS_MODULE_ENABLED

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup SMBUSEx_Exported_Functions SMBUS Extended Exported Functions
  * @{
  */

/** @defgroup SMBUSEx_Exported_Functions_Group2 WakeUp Mode Functions
  * @brief    WakeUp Mode Functions
  *
@verbatim
 ===============================================================================
                      ##### WakeUp Mode Functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
      (+) Configure Wake Up Feature

@endverbatim
  * @{
  */

/**
  * @brief  Enable SMBUS wakeup from Stop mode(s).
  * @param  hsmbus Pointer to a SMBUS_HandleTypeDef structure that contains
  *                the configuration information for the specified SMBUSx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMBUSEx_EnableWakeUp(SMBUS_HandleTypeDef *hsmbus)
{
  /* Check the parameters */
  assert_param(IS_I2C_WAKEUP_FROMSTOP_INSTANCE(hsmbus->Instance));

  if (hsmbus->State == HAL_SMBUS_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsmbus);

    hsmbus->State = HAL_SMBUS_STATE_BUSY;

    /* Disable the selected SMBUS peripheral */
    __HAL_SMBUS_DISABLE(hsmbus);

    /* Enable wakeup from stop mode */
    hsmbus->Instance->CR1 |= I2C_CR1_WUPEN;

    __HAL_SMBUS_ENABLE(hsmbus);

    hsmbus->State = HAL_SMBUS_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsmbus);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
  * @brief  Disable SMBUS wakeup from Stop mode(s).
  * @param  hsmbus Pointer to a SMBUS_HandleTypeDef structure that contains
  *                the configuration information for the specified SMBUSx peripheral.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_SMBUSEx_DisableWakeUp(SMBUS_HandleTypeDef *hsmbus)
{
  /* Check the parameters */
  assert_param(IS_I2C_WAKEUP_FROMSTOP_INSTANCE(hsmbus->Instance));

  if (hsmbus->State == HAL_SMBUS_STATE_READY)
  {
    /* Process Locked */
    __HAL_LOCK(hsmbus);

    hsmbus->State = HAL_SMBUS_STATE_BUSY;

    /* Disable the selected SMBUS peripheral */
    __HAL_SMBUS_DISABLE(hsmbus);

    /* Disable wakeup from stop mode */
    hsmbus->Instance->CR1 &= ~(I2C_CR1_WUPEN);

    __HAL_SMBUS_ENABLE(hsmbus);

    hsmbus->State = HAL_SMBUS_STATE_READY;

    /* Process Unlocked */
    __HAL_UNLOCK(hsmbus);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}
/**
  * @}
  */
#if  (defined(SYSCFG_CFGR2_I2C_PB6_FMP) || defined(SYSCFG_CFGR2_I2C_PB7_FMP)) || (defined(SYSCFG_CFGR2_I2C_PB8_FMP) || defined(SYSCFG_CFGR2_I2C_PB9_FMP)) || (defined(SYSCFG_CFGR2_I2C1_FMP)) || defined(SYSCFG_CFGR2_I2C2_FMP) || defined(SYSCFG_CFGR2_I2C3_FMP)

/** @defgroup SMBUSEx_Exported_Functions_Group3 Fast Mode Plus Functions
  * @brief    Fast Mode Plus Functions
  *
@verbatim
 ===============================================================================
                      ##### Fast Mode Plus Functions #####
 ===============================================================================
    [..] This section provides functions allowing to:
      (+) Configure Fast Mode Plus

@endverbatim
  * @{
  */

/**
  * @brief Enable the SMBUS fast mode plus driving capability.
  * @param ConfigFastModePlus Selects the pin.
  *   This parameter can be one of the @ref SMBUSEx_FastModePlus values
  * @note  For I2C1, fast mode plus driving capability can be enabled on all selected
  *        I2C1 pins using SMBUS_FASTMODEPLUS_I2C1 parameter or independently
  *        on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note  For remaining I2C1 pins (PA14, PA15...) fast mode plus driving capability
  *        can be enabled only by using SMBUS_FASTMODEPLUS_I2C1 parameter.
  * @note  For all I2C2 pins fast mode plus driving capability can be enabled
  *        only by using SMBUS_FASTMODEPLUS_I2C2 parameter.
  * @note  For all I2C3 pins fast mode plus driving capability can be enabled
  *        only by using SMBUS_FASTMODEPLUS_I2C3 parameter.
  * @retval None
  */
void HAL_SMBUSEx_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  /* Check the parameter */
  assert_param(IS_SMBUS_FASTMODEPLUS(ConfigFastModePlus));

  /* Enable SYSCFG clock */
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* Enable fast mode plus driving capability for selected pin */
  SET_BIT(SYSCFG->CFGR2, (uint32_t)ConfigFastModePlus);
}

/**
  * @brief Disable the SMBUS fast mode plus driving capability.
  * @param ConfigFastModePlus Selects the pin.
  *   This parameter can be one of the @ref SMBUSEx_FastModePlus values
  * @note  For I2C1, fast mode plus driving capability can be disabled on all selected
  *        I2C1 pins using SMBUS_FASTMODEPLUS_I2C1 parameter or independently
  *        on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note  For remaining I2C1 pins (PA14, PA15...) fast mode plus driving capability
  *        can be disabled only by using SMBUS_FASTMODEPLUS_I2C1 parameter.
  * @note  For all I2C2 pins fast mode plus driving capability can be disabled
  *        only by using SMBUS_FASTMODEPLUS_I2C2 parameter.
  * @note  For all I2C3 pins fast mode plus driving capability can be disabled
  *        only by using SMBUS_FASTMODEPLUS_I2C3 parameter.
  * @retval None
  */
void HAL_SMBUSEx_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  /* Check the parameter */
  assert_param(IS_SMBUS_FASTMODEPLUS(ConfigFastModePlus));

  /* Enable SYSCFG clock */
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* Disable fast mode plus driving capability for selected pin */
  CLEAR_BIT(SYSCFG->CFGR2, (uint32_t)ConfigFastModePlus);
}

/**
  * @}
  */

#endif /* Fast Mode Plus Availability */
/**
  * @}
  */

/**
  * @}
  */

#endif /* HAL_SMBUS_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
