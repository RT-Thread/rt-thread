/**
  ******************************************************************************
  * @file    stm32h7rsxx_ll_dlyb.h
  * @author  MCD Application Team
  * @brief   Header file of DelayBlock module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_LL_DLYB_H
#define STM32H7RSxx_LL_DLYB_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_LL_Driver
  * @{
  */

#if defined(HAL_SD_MODULE_ENABLED)
#if defined (DLYB_SDMMC1) || defined (DLYB_SDMMC2)

/* Exported types ------------------------------------------------------------*/
/** @defgroup DLYB_LL DLYB
  * @{
  */

/**
  * @brief  DLYB Configuration Structure definition
 */

typedef struct
{
  uint32_t Units;                  /*!< Specifies the Delay of a unit delay cell.
                                        This parameter can be a value between 0 and DLYB_MAX_UNIT               */

  uint32_t PhaseSel;               /*!< Specifies the Phase for the output clock.
                                        This parameter can be a value between 0 and DLYB_MAX_SELECT             */
} LL_DLYB_CfgTypeDef;

/* Exported constants --------------------------------------------------------*/
/** @defgroup DLYB_Exported_Constants DLYB Exported Constants
  * @{
  */

#define DLYB_MAX_UNIT   ((uint32_t)0x00000080U) /*!< Max UNIT value (128)  */
#define DLYB_MAX_SELECT ((uint32_t)0x0000000CU) /*!< Max SELECT value (12) */

/**
  * @}
  */

/** @defgroup DLYB_LL_Flags DLYB Flags
  * @{
  */

#define DLYB_FLAG_LNGF DLYB_CFGR_LNGF

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup DLYB_LL_Exported_Functions DLYB Exported Functions
  * @{
  */

/** @defgroup DLYB_LL_Configuration Configuration functions
  * @{
  */

/**
  * @brief  DLYB Enable
  * @param  DLYBx DLYB Instance
  * @retval None
  */

__STATIC_INLINE void LL_DLYB_Enable(DLYB_TypeDef *DLYBx)
{
  SET_BIT(DLYBx->CR, DLYB_CR_DEN);
}

/** @brief  Disable the DLYB.
  * @param  DLYBx DLYB Instance.
  * @retval None
  */

__STATIC_INLINE void LL_DLYB_Disable(DLYB_TypeDef *DLYBx)
{
  CLEAR_BIT(DLYBx->CR, DLYB_CR_DEN);
}

/**
  * @}
  */

/** @defgroup DLYB_Control_Functions DLYB Control functions
  * @{
  */

void LL_DLYB_SetDelay(DLYB_TypeDef *DLYBx, LL_DLYB_CfgTypeDef  *pdlyb_cfg);
void LL_DLYB_GetDelay(DLYB_TypeDef *DLYBx, LL_DLYB_CfgTypeDef *pdlyb_cfg);
uint32_t LL_DLYB_GetClockPeriod(DLYB_TypeDef *DLYBx, LL_DLYB_CfgTypeDef *pdlyb_cfg);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* DLYB_SDMMC1 || DLYB_SDMMC2 */
#endif /* HAL_SD_MODULE_ENABLED */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_LL_DLYB_H */
