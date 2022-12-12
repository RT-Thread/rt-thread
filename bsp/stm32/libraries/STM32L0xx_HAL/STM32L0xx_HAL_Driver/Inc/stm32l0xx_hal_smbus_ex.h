/**
  ******************************************************************************
  * @file    stm32l0xx_hal_smbus_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SMBUS HAL Extended module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32L0xx_HAL_SMBUS_EX_H
#define STM32L0xx_HAL_SMBUS_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal_def.h"

/** @addtogroup STM32L0xx_HAL_Driver
  * @{
  */

/** @addtogroup SMBUSEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SMBUSEx_Exported_Constants SMBUS Extended Exported Constants
  * @{
  */

/** @defgroup SMBUSEx_FastModePlus SMBUS Extended Fast Mode Plus
  * @{
  */
#define SMBUS_FMP_NOT_SUPPORTED           0xAAAA0000U                                     /*!< Fast Mode Plus not supported       */
#if defined(SYSCFG_CFGR2_I2C_PB6_FMP)
#define SMBUS_FASTMODEPLUS_PB6            SYSCFG_CFGR2_I2C_PB6_FMP                        /*!< Enable Fast Mode Plus on PB6       */
#define SMBUS_FASTMODEPLUS_PB7            SYSCFG_CFGR2_I2C_PB7_FMP                        /*!< Enable Fast Mode Plus on PB7       */
#else
#define SMBUS_FASTMODEPLUS_PB6            (uint32_t)(0x00000004U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus PB6 not supported   */
#define SMBUS_FASTMODEPLUS_PB7            (uint32_t)(0x00000008U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus PB7 not supported   */
#endif /* SYSCFG_CFGR2_I2C_PB6_FMP */
#if defined(SYSCFG_CFGR2_I2C_PB8_FMP)
#define SMBUS_FASTMODEPLUS_PB8            SYSCFG_CFGR2_I2C_PB8_FMP                        /*!< Enable Fast Mode Plus on PB8       */
#define SMBUS_FASTMODEPLUS_PB9            SYSCFG_CFGR2_I2C_PB9_FMP                        /*!< Enable Fast Mode Plus on PB9       */
#else
#define SMBUS_FASTMODEPLUS_PB8            (uint32_t)(0x00000010U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus PB8 not supported   */
#define SMBUS_FASTMODEPLUS_PB9            (uint32_t)(0x00000012U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus PB9 not supported   */
#endif /* SYSCFG_CFGR2_I2C_PB8_FMP */
#if defined(SYSCFG_CFGR2_I2C1_FMP)
#define SMBUS_FASTMODEPLUS_I2C1           SYSCFG_CFGR2_I2C1_FMP                           /*!< Enable Fast Mode Plus on I2C1 pins */
#else
#define SMBUS_FASTMODEPLUS_I2C1           (uint32_t)(0x00000100U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus I2C1 not supported  */
#endif /* SYSCFG_CFGR2_I2C1_FMP */
#if defined(SYSCFG_CFGR2_I2C2_FMP)
#define SMBUS_FASTMODEPLUS_I2C2           SYSCFG_CFGR2_I2C2_FMP                           /*!< Enable Fast Mode Plus on I2C2 pins */
#else
#define SMBUS_FASTMODEPLUS_I2C2           (uint32_t)(0x00000200U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus I2C2 not supported  */
#endif /* SYSCFG_CFGR2_I2C2_FMP */
#if defined(SYSCFG_CFGR2_I2C3_FMP)
#define SMBUS_FASTMODEPLUS_I2C3           SYSCFG_CFGR2_I2C3_FMP                           /*!< Enable Fast Mode Plus on I2C3 pins */
#else
#define SMBUS_FASTMODEPLUS_I2C3           (uint32_t)(0x00000400U | SMBUS_FMP_NOT_SUPPORTED) /*!< Fast Mode Plus I2C3 not supported  */
#endif /* SYSCFG_CFGR2_I2C3_FMP */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup SMBUSEx_Exported_Macros SMBUS Extended Exported Macros
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup SMBUSEx_Exported_Functions SMBUS Extended Exported Functions
  * @{
  */

/** @addtogroup SMBUSEx_Exported_Functions_Group2 WakeUp Mode Functions
  * @{
  */
/* Peripheral Control functions  ************************************************/
HAL_StatusTypeDef HAL_SMBUSEx_EnableWakeUp(SMBUS_HandleTypeDef *hsmbus);
HAL_StatusTypeDef HAL_SMBUSEx_DisableWakeUp(SMBUS_HandleTypeDef *hsmbus);
/**
  * @}
  */

/** @addtogroup SMBUSEx_Exported_Functions_Group3 Fast Mode Plus Functions
  * @{
  */
#if  (defined(SYSCFG_CFGR2_I2C_PB6_FMP) || defined(SYSCFG_CFGR2_I2C_PB7_FMP)) || (defined(SYSCFG_CFGR2_I2C_PB8_FMP) || defined(SYSCFG_CFGR2_I2C_PB9_FMP)) || (defined(SYSCFG_CFGR2_I2C1_FMP)) || defined(SYSCFG_CFGR2_I2C2_FMP) || defined(SYSCFG_CFGR2_I2C3_FMP)
void HAL_SMBUSEx_EnableFastModePlus(uint32_t ConfigFastModePlus);
void HAL_SMBUSEx_DisableFastModePlus(uint32_t ConfigFastModePlus);
#endif /* Fast Mode Plus Availability */
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Constants SMBUS Extended Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Macro SMBUS Extended Private Macros
  * @{
  */
#define IS_SMBUS_FASTMODEPLUS(__CONFIG__) ((((__CONFIG__) & SMBUS_FMP_NOT_SUPPORTED) != SMBUS_FMP_NOT_SUPPORTED) && \
                                           ((((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB6))  == SMBUS_FASTMODEPLUS_PB6)  || \
                                            (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB7))  == SMBUS_FASTMODEPLUS_PB7)  || \
                                            (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB8))  == SMBUS_FASTMODEPLUS_PB8)  || \
                                            (((__CONFIG__) & (SMBUS_FASTMODEPLUS_PB9))  == SMBUS_FASTMODEPLUS_PB9)  || \
                                            (((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C1)) == SMBUS_FASTMODEPLUS_I2C1) || \
                                            (((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C2)) == SMBUS_FASTMODEPLUS_I2C2) || \
                                            (((__CONFIG__) & (SMBUS_FASTMODEPLUS_I2C3)) == SMBUS_FASTMODEPLUS_I2C3)))
/**
  * @}
  */

/* Private Functions ---------------------------------------------------------*/
/** @defgroup SMBUSEx_Private_Functions SMBUS Extended Private Functions
  * @{
  */
/* Private functions are defined in stm32l0xx_hal_smbus_ex.c file */
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

#endif /* STM32L0xx_HAL_SMBUS_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
