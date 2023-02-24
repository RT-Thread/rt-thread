/**
  ******************************************************************************
  * @file    stm32f4xx_hal_i2c_ex.h
  * @author  MCD Application Team
  * @brief   Header file of I2C HAL Extension module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_HAL_I2C_EX_H
#define __STM32F4xx_HAL_I2C_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#if  defined(I2C_FLTR_ANOFF)&&defined(I2C_FLTR_DNF)
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup I2CEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup I2CEx_Exported_Constants I2C Exported Constants
  * @{
  */

/** @defgroup I2CEx_Analog_Filter I2C Analog Filter
  * @{
  */
#define I2C_ANALOGFILTER_ENABLE        0x00000000U
#define I2C_ANALOGFILTER_DISABLE       I2C_FLTR_ANOFF
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup I2CEx_Exported_Functions
  * @{
  */

/** @addtogroup I2CEx_Exported_Functions_Group1
  * @{
  */
/* Peripheral Control functions  ************************************************/
HAL_StatusTypeDef HAL_I2CEx_ConfigAnalogFilter(I2C_HandleTypeDef *hi2c, uint32_t AnalogFilter);
HAL_StatusTypeDef HAL_I2CEx_ConfigDigitalFilter(I2C_HandleTypeDef *hi2c, uint32_t DigitalFilter);
/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup I2CEx_Private_Constants I2C Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup I2CEx_Private_Macros I2C Private Macros
  * @{
  */
#define IS_I2C_ANALOG_FILTER(FILTER) (((FILTER) == I2C_ANALOGFILTER_ENABLE) || \
                                      ((FILTER) == I2C_ANALOGFILTER_DISABLE))
#define IS_I2C_DIGITAL_FILTER(FILTER)   ((FILTER) <= 0x0000000FU)
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_I2C_EX_H */


