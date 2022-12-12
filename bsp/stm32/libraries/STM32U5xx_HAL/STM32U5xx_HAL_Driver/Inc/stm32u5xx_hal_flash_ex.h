/**
  ******************************************************************************
  * @file    stm32u5xx_hal_flash_ex.h
  * @author  MCD Application Team
  * @brief   Header file of FLASH HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32U5xx_HAL_FLASH_EX_H
#define STM32U5xx_HAL_FLASH_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup FLASHEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Types FLASHEx Exported Types
  * @{
  */

/**
  * @brief  FLASHEx Block-based attributes structure definition
  */

typedef struct
{
  uint32_t Bank;                                        /*!< Selection of the associated bank of Block-based Area.
                                                             This parameter must be a value of @ref FLASH_Banks */
  uint32_t BBAttributesType;                            /*!< Block-Based Attributes type. This parameter must
                                                             be a value of @ref FLASH_BB_Attributes */
  uint32_t BBAttributes_array[FLASH_BLOCKBASED_NB_REG]; /*!< Each bit specifies the block-based attribute configuration
                                                             of a page: 0 means page non-protected, 1 means page
                                                             protected. Protection (secure or privilege) depends
                                                             on BBAttributesType value */
} FLASH_BBAttributesTypeDef;


/**
  * @brief  FLASHEx Operation structure definition
  */
typedef struct
{
  uint32_t OperationType;    /*!< Flash operation Type.
                                  This parameter must be a value of @ref FLASH_Operation_Type */
  uint32_t FlashArea;        /*!< Flash operation memory area.
                                  This parameter must be a value of @ref FLASH_Operation_Area */
  uint32_t Address;          /*!< Flash operation Address offset.
                                  This parameter is given by bank, and must be a value between 0x0 and 0xFFFF0 */
} FLASH_OperationTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @addtogroup FLASHEx_Exported_Constants
  * @{
  */
/** @defgroup PRIV_MODE_CFG FLASH privilege mode configuration
  * @{
  */
#define FLASH_NSPRIV_GRANTED   0x00000000U           /*!< access to non-secure Flash registers is granted
                                                          to privileged or unprivileged access */
#define FLASH_NSPRIV_DENIED    FLASH_PRIVCFGR_NSPRIV /*!< access to non-secure Flash registers is denied
                                                          to non-privilege access */
#define FLASH_SPRIV_GRANTED    0x00000000U           /*!< access to secure Flash registers is granted to privileged
                                                          or unprivileged access */
#define FLASH_SPRIV_DENIED     FLASH_PRIVCFGR_SPRIV  /*!< access to secure Flash registers is denied
                                                          to non-privilege access */
/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
/** @defgroup SEC_INVERSION_CFG FLASH security inversion configuration
  * @{
  */
#define FLASH_INV_DISABLE      0x00000000U        /*!< Security state of Flash is not inverted */
#define FLASH_INV_ENABLE       FLASH_SECCR_INV    /*!< Security state of Flash is inverted */
/**
  * @}
  */
#endif /* __ARM_FEATURE_CMSE */

/** @defgroup FLASH_LPM_CFG FLASH LPM configuration
  * @{
  */
#define FLASH_LPM_DISABLE      0x00000000U    /*!< Flash is in normal read mode */
#define FLASH_LPM_ENABLE       FLASH_ACR_LPM  /*!< Flash is in low-power read mode */
/**
  * @}
  */

/** @defgroup FLASH_BB_Attributes FLASH Block-Base Attributes
  * @{
  */
#define FLASH_BB_SEC           0x01U    /*!< Flash Block-Based Security Attributes */
#define FLASH_BB_PRIV          0x02U    /*!< Flash Block-Based Privilege Attributes */
/**
  * @}
  */

/** @defgroup FLASH_Operation_Type FLASH Operation Type
  * @{
  */
#define FLASH_OPERATION_TYPE_NONE         00000000U                                     /*!< No Flash operation      */
#define FLASH_OPERATION_TYPE_QUADWORD     FLASH_OPSR_CODE_OP_0                          /*!< Single write operation  */
#define FLASH_OPERATION_TYPE_BURST        FLASH_OPSR_CODE_OP_1                          /*!< Burst write operation   */
#define FLASH_OPERATION_TYPE_PAGEERASE    (FLASH_OPSR_CODE_OP_1 | FLASH_OPSR_CODE_OP_0) /*!< Page erase operation    */
#define FLASH_OPERATION_TYPE_BANKERASE    FLASH_OPSR_CODE_OP_2                          /*!< Bank erase operation    */
#define FLASH_OPERATION_TYPE_MASSERASE    (FLASH_OPSR_CODE_OP_2 | FLASH_OPSR_CODE_OP_0) /*!< Mass erase operation    */
#define FLASH_OPERATION_TYPE_OPTIONCHANGE (FLASH_OPSR_CODE_OP_2 | FLASH_OPSR_CODE_OP_1) /*!< Option change operation */
/**
  * @}
  */

/** @defgroup FLASH_Operation_Area FLASH Operation Area
  * @{
  */
#define FLASH_OPERATION_AREA_BANK_1        00000000U               /*!< Operation in Bank 1              */
#define FLASH_OPERATION_AREA_BANK_2        FLASH_OPSR_BK_OP        /*!< Operation in Bank 2              */
#define FLASH_OPERATION_AREA_SYSF          FLASH_OPSR_SYSF_OP      /*!< Operation in System Flash memory */
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
HAL_StatusTypeDef HAL_FLASHEx_ConfigBBAttributes(FLASH_BBAttributesTypeDef *pBBAttributes);
void              HAL_FLASHEx_GetConfigBBAttributes(FLASH_BBAttributesTypeDef *pBBAttributes);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
void              HAL_FLASHEx_EnableSecHideProtection(uint32_t Banks);
#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/** @addtogroup FLASHEx_Exported_Functions_Group2
  * @{
  */
void              HAL_FLASHEx_ConfigPrivMode(uint32_t PrivMode);
uint32_t          HAL_FLASHEx_GetPrivMode(void);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
HAL_StatusTypeDef HAL_FLASHEx_ConfigSecInversion(uint32_t SecInvState);
uint32_t          HAL_FLASHEx_GetSecInversion(void);
#endif /* __ARM_FEATURE_CMSE */
HAL_StatusTypeDef HAL_FLASHEx_EnablePowerDown(uint32_t Banks);
HAL_StatusTypeDef HAL_FLASHEx_ConfigLowPowerRead(uint32_t ConfigLPM);
uint32_t          HAL_FLASHEx_GetLowPowerRead(void);
void              HAL_FLASHEx_GetOperation(FLASH_OperationTypeDef *pFlashOperation);
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
/** @defgroup FLASHEx_Private_Macros FLASH Private Macros
  *  @{
  */
#define IS_FLASH_BB_EXCLUSIVE(CFG)         (((CFG) == FLASH_BB_SEC)  || \
                                            ((CFG) == FLASH_BB_PRIV))

#define IS_FLASH_CFGPRIVMODE(CFG)          (((CFG) & 0xFFFFFFFCU) == 0U)

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define IS_FLASH_CFGSECINV(CFG)            (((CFG) == FLASH_INV_DISABLE) || \
                                            ((CFG) == FLASH_INV_ENABLE))
#endif /* __ARM_FEATURE_CMSE */

#define IS_FLASH_CFGLPM(CFG)               (((CFG) == FLASH_LPM_DISABLE) || \
                                            ((CFG) == FLASH_LPM_ENABLE))
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

#endif /* STM32U5xx_HAL_FLASH_EX_H */

