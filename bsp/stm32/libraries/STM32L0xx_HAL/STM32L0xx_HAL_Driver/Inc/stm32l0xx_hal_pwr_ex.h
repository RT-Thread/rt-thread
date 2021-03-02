/**
  ******************************************************************************
  * @file    stm32l0xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extension module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright(c) 2016 STMicroelectronics.
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
#ifndef __STM32L0xx_HAL_PWR_EX_H
#define __STM32L0xx_HAL_PWR_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @{
  */

/** @defgroup PWREx_Exported_Macros PWREx Exported Macros
 * @{
 */

/** @brief  Macros to enable the Deep-sleep mode with Flash memory kept off.
  * @note   When entering low power mode (stop or standby only), if DS_EE_KOFF and RUN_PD of
  *         FLASH_ACR register are both set , the Flash memory will not be woken up
  *         when exiting from deep-sleep mode.
  */
#define __HAL_PWR_FLASHWAKEUP_ENABLE()      CLEAR_BIT(PWR->CR, PWR_CR_DSEEKOFF)

/** @brief  Macros to disable the Deep-sleep mode with Flash memory kept off.
  * @note   When entering low power mode (stop or standby only), if DS_EE_KOFF and RUN_PD of
  *         FLASH_ACR register are both set , the Flash memory will not be woken up
  *         when exiting from deep-sleep mode.
  */
#define __HAL_PWR_FLASHWAKEUP_DISABLE()     SET_BIT(PWR->CR, PWR_CR_DSEEKOFF)
/**
  * @}
  */

/** @defgroup PWREx_Exported_Functions PWREx Exported Functions
 * @{
 */
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

/* Define the private group ***********************************/
/**************************************************************/
/** @defgroup PWREx_Private PWREx Private
  * @{
  */
/**
  * @}
  */
/**************************************************************/

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32L0xx_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

