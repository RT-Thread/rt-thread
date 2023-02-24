/**
  ******************************************************************************
  * @file    stm32f4xx_hal_fmpsmbus_ex.h
  * @author  MCD Application Team
  * @brief   Header file of FMPSMBUS HAL Extended module.
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
#ifndef STM32F4xx_HAL_FMPSMBUS_EX_H
#define STM32F4xx_HAL_FMPSMBUS_EX_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(FMPI2C_CR1_PE)
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup FMPSMBUSEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup FMPSMBUSEx_Exported_Constants FMPSMBUS Extended Exported Constants
  * @{
  */

/** @defgroup FMPSMBUSEx_FastModePlus FMPSMBUS Extended Fast Mode Plus
  * @{
  */
#define FMPSMBUS_FASTMODEPLUS_SCL            SYSCFG_CFGR_FMPI2C1_SCL  /*!< Enable Fast Mode Plus on FMPI2C1 SCL pins       */
#define FMPSMBUS_FASTMODEPLUS_SDA            SYSCFG_CFGR_FMPI2C1_SDA  /*!< Enable Fast Mode Plus on FMPI2C1 SDA pins       */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup FMPSMBUSEx_Exported_Macros FMPSMBUS Extended Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FMPSMBUSEx_Exported_Functions FMPSMBUS Extended Exported Functions
  * @{
  */

/** @addtogroup FMPSMBUSEx_Exported_Functions_Group2 WakeUp Mode Functions
  * @{
  */
/* Peripheral Control functions  ************************************************/
/**
  * @}
  */

/** @addtogroup FMPSMBUSEx_Exported_Functions_Group3 Fast Mode Plus Functions
  * @{
  */
void HAL_FMPSMBUSEx_EnableFastModePlus(uint32_t ConfigFastModePlus);
void HAL_FMPSMBUSEx_DisableFastModePlus(uint32_t ConfigFastModePlus);
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup FMPSMBUSEx_Private_Constants FMPSMBUS Extended Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FMPSMBUSEx_Private_Macro FMPSMBUS Extended Private Macros
  * @{
  */
#define IS_FMPSMBUS_FASTMODEPLUS(__CONFIG__) ((((__CONFIG__) & (FMPSMBUS_FASTMODEPLUS_SCL)) == \
                                            FMPSMBUS_FASTMODEPLUS_SCL) || \
                                           (((__CONFIG__) & (FMPSMBUS_FASTMODEPLUS_SDA)) == \
                                            FMPSMBUS_FASTMODEPLUS_SDA))
/**
  * @}
  */

/* Private Functions ---------------------------------------------------------*/
/** @defgroup FMPSMBUSEx_Private_Functions FMPSMBUS Extended Private Functions
  * @{
  */
/* Private functions are defined in stm32f4xx_hal_fmpsmbus_ex.c file */
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
#ifdef __cplusplus
}
#endif

#endif /* STM32F4xx_HAL_FMPSMBUS_EX_H */
