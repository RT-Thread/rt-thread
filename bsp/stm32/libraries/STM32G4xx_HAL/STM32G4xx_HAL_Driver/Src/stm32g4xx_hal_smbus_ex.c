/**
  ******************************************************************************
  * @file    stm32g4xx_hal_smbus_ex.c
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

  [..] Comparing to other previous devices, the SMBUS interface for STM32G4xx
       devices contains the following additional features

       (+) Disable or enable Fast Mode Plus

                     ##### How to use this driver #####
  ==============================================================================
    (#) Configure the enable or disable of fast mode plus driving capability using the functions :
          (++) HAL_SMBUSEx_EnableFastModePlus()
          (++) HAL_SMBUSEx_DisableFastModePlus()
  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "stm32g4xx_hal.h"

/** @addtogroup STM32G4xx_HAL_Driver
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

/** @defgroup SMBUSEx_Exported_Functions_Group1 Extended features functions
  * @brief    Extended features functions
 *
@verbatim
 ===============================================================================
                      ##### Extended features functions #####
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
  *        I2C1 pins using I2C_FASTMODEPLUS_I2C1 parameter or independently
  *        on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note  For remaining I2C1 pins (PA14, PA15...) fast mode plus driving capability
  *        can be enabled only by using I2C_FASTMODEPLUS_I2C1 parameter.
  * @note  For all I2C2 pins fast mode plus driving capability can be enabled
  *        only by using I2C_FASTMODEPLUS_I2C2 parameter.
  * @note  For all I2C3 pins fast mode plus driving capability can be enabled
  *        only by using I2C_FASTMODEPLUS_I2C3 parameter.
  * @note  For all I2C4 pins fast mode plus driving capability can be enabled
  *        only by using I2C_FASTMODEPLUS_I2C4 parameter.
  * @retval None
  */
void HAL_SMBUSEx_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  /* Check the parameter */
  assert_param(IS_SMBUS_FASTMODEPLUS(ConfigFastModePlus));

  /* Enable SYSCFG clock */
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* Enable fast mode plus driving capability for selected pin */
  SET_BIT(SYSCFG->CFGR1, (uint32_t)ConfigFastModePlus);
}

/**
  * @brief Disable the SMBUS fast mode plus driving capability.
  * @param ConfigFastModePlus Selects the pin.
  *   This parameter can be one of the @ref SMBUSEx_FastModePlus values
  * @note  For I2C1, fast mode plus driving capability can be disabled on all selected
  *        I2C1 pins using I2C_FASTMODEPLUS_I2C1 parameter or independently
  *        on each one of the following pins PB6, PB7, PB8 and PB9.
  * @note  For remaining I2C1 pins (PA14, PA15...) fast mode plus driving capability
  *        can be disabled only by using I2C_FASTMODEPLUS_I2C1 parameter.
  * @note  For all I2C2 pins fast mode plus driving capability can be disabled
  *        only by using I2C_FASTMODEPLUS_I2C2 parameter.
  * @note  For all I2C3 pins fast mode plus driving capability can be disabled
  *        only by using I2C_FASTMODEPLUS_I2C3 parameter.
  * @note  For all I2C4 pins fast mode plus driving capability can be disabled
  *        only by using I2C_FASTMODEPLUS_I2C4 parameter.
  * @retval None
  */
void HAL_SMBUSEx_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  /* Check the parameter */
  assert_param(IS_SMBUS_FASTMODEPLUS(ConfigFastModePlus));

  /* Enable SYSCFG clock */
  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* Disable fast mode plus driving capability for selected pin */
  CLEAR_BIT(SYSCFG->CFGR1, (uint32_t)ConfigFastModePlus);
}


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
