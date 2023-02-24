/**
  ******************************************************************************
  * @file    stm32f4xx_hal_cryp_ex.h
  * @author  MCD Application Team
  * @brief   Header file of CRYP HAL Extension module.
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
#ifndef __STM32F4xx_HAL_CRYP_EX_H
#define __STM32F4xx_HAL_CRYP_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal_def.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup CRYPEx
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/** @defgroup CRYPEx_Exported_Types CRYPEx Exported types
  * @{
  */

/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup CRYPEx_Exported_Constants CRYPEx Exported constants
  * @{
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Types CRYPEx Private Types
  * @{
  */

/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Variables CRYPEx Private Variables
  * @{
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Constants CRYPEx Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Macros CRYPEx Private Macros
  * @{
  */

/**
  * @}
 */

/* Private functions ---------------------------------------------------------*/
/** @defgroup CRYPEx_Private_Functions CRYPEx Private Functions
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup CRYPEx_Exported_Functions CRYPEx Exported Functions
  * @{
  */
#if defined (CRYP) || defined (AES)
/** @addtogroup CRYPEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_CRYPEx_AESGCM_GenerateAuthTAG(CRYP_HandleTypeDef *hcryp, uint32_t *AuthTag, uint32_t Timeout);
HAL_StatusTypeDef HAL_CRYPEx_AESCCM_GenerateAuthTAG(CRYP_HandleTypeDef *hcryp, uint32_t *AuthTag, uint32_t Timeout);
/**
  * @}
  */
#endif /* CRYP||AES */

#if defined (AES)
/** @addtogroup CRYPEx_Exported_Functions_Group2
  * @{
  */
void  HAL_CRYPEx_EnableAutoKeyDerivation(CRYP_HandleTypeDef *hcryp);
void  HAL_CRYPEx_DisableAutoKeyDerivation(CRYP_HandleTypeDef *hcryp);
/**
  * @}
  */
#endif /* AES */

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

#endif /* __STM32F4xx_HAL_CRYP_EX_H */

