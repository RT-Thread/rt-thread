/**
  ******************************************************************************
  * @file    stm32f4xx_hal_fmpsmbus_ex.c
  * @author  MCD Application Team
  * @brief   FMPSMBUS Extended HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of FMPSMBUS Extended peripheral:
  *           + Extended features functions
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
               ##### FMPSMBUS peripheral Extended features  #####
  ==============================================================================

  [..] Comparing to other previous devices, the FMPSMBUS interface for STM32F4xx
       devices contains the following additional features

       (+) Disable or enable Fast Mode Plus

                     ##### How to use this driver #####
  ==============================================================================
    (#) Configure the enable or disable of fast mode plus driving capability using the functions :
          (++) HAL_FMPSMBUSEx_EnableFastModePlus()
          (++) HAL_FMPSMBUSEx_DisableFastModePlus()
  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @defgroup FMPSMBUSEx FMPSMBUSEx
  * @brief FMPSMBUS Extended HAL module driver
  * @{
  */

#ifdef HAL_FMPSMBUS_MODULE_ENABLED
#if defined(FMPI2C_CR1_PE)

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup FMPSMBUSEx_Exported_Functions FMPSMBUS Extended Exported Functions
  * @{
  */

/** @defgroup FMPSMBUSEx_Exported_Functions_Group3 Fast Mode Plus Functions
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
  * @brief Enable the FMPSMBUS fast mode plus driving capability.
  * @param ConfigFastModePlus Selects the pin.
  *   This parameter can be one of the @ref FMPSMBUSEx_FastModePlus values
  * @note  For FMPI2C1, fast mode plus driving capability can be enabled on all selected
  *        FMPI2C1 pins using FMPSMBUS_FASTMODEPLUS_FMPI2C1 parameter or independently
  *        on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note  For remaining FMPI2C1 pins (PA14, PA15...) fast mode plus driving capability
  *        can be enabled only by using FMPSMBUS_FASTMODEPLUS_FMPI2C1 parameter.
  * @retval None
  */
void HAL_FMPSMBUSEx_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  /* Check the parameter */
  assert_param(IS_FMPSMBUS_FASTMODEPLUS(ConfigFastModePlus));

  /* Enable SYSCFG clock */
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* Enable fast mode plus driving capability for selected pin */
  SET_BIT(SYSCFG->CFGR, (uint32_t)ConfigFastModePlus);
}

/**
  * @brief Disable the FMPSMBUS fast mode plus driving capability.
  * @param ConfigFastModePlus Selects the pin.
  *   This parameter can be one of the @ref FMPSMBUSEx_FastModePlus values
  * @note  For FMPI2C1, fast mode plus driving capability can be disabled on all selected
  *        FMPI2C1 pins using FMPSMBUS_FASTMODEPLUS_FMPI2C1 parameter or independently
  *        on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note  For remaining FMPI2C1 pins (PA14, PA15...) fast mode plus driving capability
  *        can be disabled only by using FMPSMBUS_FASTMODEPLUS_FMPI2C1 parameter.
  * @retval None
  */
void HAL_FMPSMBUSEx_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  /* Check the parameter */
  assert_param(IS_FMPSMBUS_FASTMODEPLUS(ConfigFastModePlus));

  /* Enable SYSCFG clock */
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* Disable fast mode plus driving capability for selected pin */
  CLEAR_BIT(SYSCFG->CFGR, (uint32_t)ConfigFastModePlus);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* FMPI2C_CR1_PE */
#endif /* HAL_FMPSMBUS_MODULE_ENABLED */
/**
  * @}
  */

/**
  * @}
  */
