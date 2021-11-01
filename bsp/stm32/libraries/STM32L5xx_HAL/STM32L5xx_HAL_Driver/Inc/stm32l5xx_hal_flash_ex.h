/**
  ******************************************************************************
  * @file    stm32l5xx_hal_flash_ex.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL Extended module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32L5xx_HAL_FLASH_EX_H
#define STM32L5xx_HAL_FLASH_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal_def.h"

/** @addtogroup STM32L5xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @{
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/* Private constants ---------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Constants FLASH Extended Private Constants
  * @{
  */
#define FLASH_BLOCKBASED_NB_REG (4U) /*!< Number of block-based registers available */
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Types FLASH Exported Types
  * @{
  */

/**
  * @brief  FLASH Block-based security structure definition
  */
typedef struct
{
  uint32_t Bank;                                        /*!< Configuration of the associated bank of Block-based Secure Area.
                                                            This parameter must be a value of @ref FLASH_Banks */
  uint32_t BBAttributesType;                            /*!< Block-Based Attributes type.
                                                             This parameter must be a value of @ref FLASHEx_BB_Attributes */     
  uint32_t BBAttributes_array[FLASH_BLOCKBASED_NB_REG]; /*!< Each bit specifies the block-based attribute configuration of a page.
                                                             0 means non-secure, 1 means secure */
} FLASH_BBAttributesTypeDef;
/**
  * @}
  */
#endif

/* Exported constants --------------------------------------------------------*/
/** @defgroup FLASHEx_Exported_Constants FLASH Extended Exported Constants
  * @{
  */

/** @defgroup FLASHEx_PRIV_MODE_CFG FLASH privilege mode configuration
  * @{
  */
#define FLASH_PRIV_GRANTED   0x00000000U          /*!< access to Flash registers is granted */
#define FLASH_PRIV_DENIED    FLASH_PRIVCFGR_PRIV /*!< access to Flash registers is denied to non-privilege access */
/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup FLASHEx_SEC_INVERSION_CFG FLASH security inversion configuration
  * @{
  */
#define FLASH_INV_DISABLE    0x00000000U        /*!< Security state of Flash is not inverted */
#define FLASH_INV_ENABLE     FLASH_SECCR_SECINV /*!< Security state of Flash is inverted */
/**
  * @}
  */
#endif

/** @defgroup FLASHEx_LVE_PIN_CFG FLASH LVE pin configuration
  * @{
  */
#define FLASH_LVE_PIN_CTRL   0x00000000U       /*!< LVEA/B FLASH pin controlled by power controller */
#define FLASH_LVE_PIN_FORCED FLASH_ACR_LVEN    /*!< LVEA/B FLASH pin enforced to low */
/**
  * @}
  */

/** @defgroup FLASHEx_BB_Attributes FLASH Block-Based Attributes
  * @{
  */
#define FLASH_BB_SEC         0x00000001U       /*!< Flash Block-Based Security Attributes */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Functions
  * @{
  */

/* Extended Program operation functions  *************************************/
/** @addtogroup FLASHEx_Exported_Functions_Group1
  * @{
  */
HAL_StatusTypeDef HAL_FLASHEx_Erase(FLASH_EraseInitTypeDef *pEraseInit, uint32_t *PageError);
HAL_StatusTypeDef HAL_FLASHEx_Erase_IT(FLASH_EraseInitTypeDef *pEraseInit);
HAL_StatusTypeDef HAL_FLASHEx_OBProgram(FLASH_OBProgramInitTypeDef *pOBInit);
void              HAL_FLASHEx_OBGetConfig(FLASH_OBProgramInitTypeDef *pOBInit);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
HAL_StatusTypeDef HAL_FLASHEx_ConfigBBAttributes(FLASH_BBAttributesTypeDef *pBBAttributes);
void              HAL_FLASHEx_GetConfigBBAttributes(FLASH_BBAttributesTypeDef *pBBAttributes);
void              HAL_FLASHEx_EnableSecHideProtection(uint32_t Banks);
#endif
/**
  * @}
  */

/* Extended Peripheral Control functions  ************************************/
/** @addtogroup FLASHEx_Exported_Functions_Group2
  * @{
  */
void              HAL_FLASHEx_ConfigPrivMode(uint32_t PrivMode);
uint32_t          HAL_FLASHEx_GetPrivMode(void);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
HAL_StatusTypeDef HAL_FLASHEx_ConfigSecInversion(uint32_t SecInvState);
uint32_t          HAL_FLASHEx_GetSecInversion(void);
#endif
HAL_StatusTypeDef HAL_FLASHEx_ConfigLVEPin(uint32_t ConfigLVE);
uint32_t          HAL_FLASHEx_GetLVEPin(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private function ----------------------------------------------------------*/
/** @addtogroup FLASHEx_Private_Functions FLASHEx Private Functions
 * @{
 */
void FLASH_PageErase(uint32_t Page, uint32_t Banks);
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FLASHEx_Private_Macros FLASH Extended Private Macros
 *  @{
 */
#define IS_FLASH_CFGPRIVMODE(CFG)          (((CFG) == FLASH_PRIV_GRANTED) || \
                                            ((CFG) == FLASH_PRIV_DENIED))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_CFGSECINV(CFG)            (((CFG) == FLASH_INV_DISABLE) || \
                                            ((CFG) == FLASH_INV_ENABLE))
#endif

#define IS_FLASH_CFGLVEPIN(CFG)            (((CFG) == FLASH_LVE_PIN_CTRL) || \
                                            ((CFG) == FLASH_LVE_PIN_FORCED))

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

#endif /* STM32L5xx_HAL_FLASH_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
