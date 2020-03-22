/**
  ******************************************************************************
  * @file    stm32l1xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extension module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32L1xx_HAL_PWR_EX_H
#define __STM32L1xx_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal_def.h"

/** @addtogroup STM32L1xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants PWREx Exported Constants
 *  @{
 */


/** @defgroup PWREx_WakeUp_Pins PWREx Wakeup Pins
  * @{
  */

#if defined (STM32L151xCA) || defined (STM32L151xD) || defined (STM32L152xCA) || defined (STM32L152xD) || defined (STM32L162xCA) || defined (STM32L162xD) || defined (STM32L151xE) || defined (STM32L151xDX) || defined (STM32L152xE) || defined (STM32L152xDX) || defined (STM32L162xE) || defined (STM32L162xDX) || defined (STM32L151xB) || defined (STM32L151xBA) || defined (STM32L151xC) || defined (STM32L152xB) || defined (STM32L152xBA) || defined (STM32L152xC) || defined (STM32L162xC)

#define PWR_WAKEUP_PIN1                 PWR_CSR_EWUP1
#define PWR_WAKEUP_PIN2                 PWR_CSR_EWUP2
#define PWR_WAKEUP_PIN3                 PWR_CSR_EWUP3
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1) || \
                                ((PIN) == PWR_WAKEUP_PIN2) || \
                                ((PIN) == PWR_WAKEUP_PIN3))
#else
#define PWR_WAKEUP_PIN1                 PWR_CSR_EWUP1
#define PWR_WAKEUP_PIN2                 PWR_CSR_EWUP2
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1) || \
                                ((PIN) == PWR_WAKEUP_PIN2))
#endif

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Functions PWREx Exported Functions
 *  @{
 */

/** @addtogroup PWREx_Exported_Functions_Group1
  * @{
  */

/* Peripheral Control methods  ************************************************/
uint32_t HAL_PWREx_GetVoltageRange(void);
void HAL_PWREx_EnableFastWakeUp(void);
void HAL_PWREx_DisableFastWakeUp(void);
void HAL_PWREx_EnableUltraLowPower(void);
void HAL_PWREx_DisableUltraLowPower(void);
void HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* __STM32L1xx_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
