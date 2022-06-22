/**
  ******************************************************************************
  * @file    stm32u5xx_hal_ramcfg.h
  * @author  MCD Application Team
  * @brief   Header file of RAMCFG HAL module.
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
#ifndef STM32U5xx_HAL_RAMCFG_H
#define STM32U5xx_HAL_RAMCFG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32u5xx_hal_def.h"

/** @addtogroup STM32U5xx_HAL_Driver
  * @{
  */

/** @addtogroup RAMCFG
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RAMCFG_Exported_Types RAMCFG Exported Types
  * @brief    RAMCFG Exported Types
  * @{
  */

/**
  * @brief  HAL RAMCFG State Enumeration Definition
  */
typedef enum
{
  HAL_RAMCFG_STATE_RESET             = 0x00U,  /*!< RAMCFG not yet initialized or disabled */
  HAL_RAMCFG_STATE_READY             = 0x01U,  /*!< RAMCFG initialized and ready for use   */
  HAL_RAMCFG_STATE_BUSY              = 0x02U,  /*!< RAMCFG process is ongoing              */
  HAL_RAMCFG_STATE_ERROR             = 0x03U,  /*!< RAMCFG error state                     */
} HAL_RAMCFG_StateTypeDef;

#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL RAMCFG Callbacks IDs Enumeration Definition
  */
typedef enum
{
  HAL_RAMCFG_MSPINIT_CB_ID           = 0x00U,  /*!< RAMCFG MSP Init Callback ID            */
  HAL_RAMCFG_MSPDEINIT_CB_ID         = 0x01U,  /*!< RAMCFG MSP DeInit Callback ID          */
  HAL_RAMCFG_SE_DETECT_CB_ID         = 0x02U,  /*!< RAMCFG Single Error Detect Callback ID */
  HAL_RAMCFG_DE_DETECT_CB_ID         = 0x03U,  /*!< RAMCFG Double Error Detect Callback ID */
  HAL_RAMCFG_ALL_CB_ID               = 0x04U,  /*!< RAMCFG All callback ID                 */
} HAL_RAMCFG_CallbackIDTypeDef;
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */

/**
  * @brief  RAMCFG Handle Structure Definition
  */
#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
typedef struct __RAMCFG_HandleTypeDef
#else
typedef struct
#endif /* (USE_HAL_RAMCFG_REGISTER_CALLBACKS) */
{
  RAMCFG_TypeDef                  *Instance;                                 /*!< RAMCFG Register Base Address        */
  __IO HAL_RAMCFG_StateTypeDef    State;                                     /*!< RAMCFG State                        */
  __IO uint32_t                   ErrorCode;                                 /*!< RAMCFG Error Code                   */
#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
  void (* MspInitCallback)(struct __RAMCFG_HandleTypeDef *hramcfg);          /*!< RAMCFG MSP Init Callback            */
  void (* MspDeInitCallback)(struct __RAMCFG_HandleTypeDef *hramcfg);        /*!< RAMCFG MSP DeInit Callback          */
  void (* DetectSingleErrorCallback)(struct __RAMCFG_HandleTypeDef *hramcfg);/*!< RAMCFG Single Error Detect Callback */
  void (* DetectDoubleErrorCallback)(struct __RAMCFG_HandleTypeDef *hramcfg);/*!< RAMCFG Double Error Detect Callback */
#endif  /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */
} RAMCFG_HandleTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RAMCFG_Exported_Constants RAMCFG Exported Constants
  * @brief    RAMCFG Exported Constants
  * @{
  */

/** @defgroup RAMCFG_Error_Codes RAMCFG Error Codes
  * @brief    RAMCFG Error Codes
  * @{
  */
#define HAL_RAMCFG_ERROR_NONE             0x00000000U  /*!< RAMCFG No Error         */
#define HAL_RAMCFG_ERROR_TIMEOUT          0x00000001U  /*!< RAMCFG Timeout Error    */
#define HAL_RAMCFG_ERROR_BUSY             0x00000002U  /*!< RAMCFG Busy Error       */
#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
#define HAL_RAMCFG_ERROR_INVALID_CALLBACK 0x00000003U  /*!< Invalid Callback error  */
#endif  /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup RAMCFG_Interrupt RAMCFG Interrupts
  * @brief    RAMCFG Interrupts
  * @{
  */
#define RAMCFG_IT_SINGLEERR   RAMCFG_IER_SEIE      /* RAMCFG Single Error Interrupt                   */
#define RAMCFG_IT_DOUBLEERR   RAMCFG_IER_DEIE      /* RAMCFG Double Error Interrupt                   */
#define RAMCFG_IT_NMIERR      RAMCFG_IER_ECCNMI    /* RAMCFG Double Error redirected to NMI Interrupt */
#define RAMCFG_IT_ALL         (RAMCFG_IER_SEIE | \
                               RAMCFG_IER_DEIE | \
                               RAMCFG_IER_ECCNMI)  /* RAMCFG All RAMCFG interrupt                    */
/**
  * @}
  */

/** @defgroup RAMCFG_FLAG RAMCFG Monitor Flags
  * @brief    RAMCFG Monitor Flags
  * @{
  */
#define RAMCFG_FLAG_SINGLEERR   RAMCFG_ISR_SEDC        /* RAMCFG Single Error Detected and Corrected Flag */
#define RAMCFG_FLAG_DOUBLEERR   RAMCFG_ISR_DED         /* RAMCFG Double Error Detected Flag               */
#define RAMCFG_FLAG_SRAMBUSY    RAMCFG_ISR_SRAMBUSY    /* RAMCFG SRAM busy Flag                           */
#define RAMCFG_FLAGS_ALL        (RAMCFG_ISR_SEDC | \
                                 RAMCFG_ISR_DED  | \
                                 RAMCFG_ISR_SRAMBUSY)  /* RAMCFG All Flags                                */
/**
  * @}
  */

/** @defgroup RAMCFG_WaitState RAMCFG Wait State
  * @brief    RAMCFG Wait State
  * @{
  */
#define RAMCFG_WAITSTATE_0   (0U)                                                  /* RAMCFG 0 Wait State */
#define RAMCFG_WAITSTATE_1   (RAMCFG_CR_WSC_0)                                     /* RAMCFG 1 Wait State */
#define RAMCFG_WAITSTATE_2   (RAMCFG_CR_WSC_1)                                     /* RAMCFG 2 Wait State */
#define RAMCFG_WAITSTATE_3   (RAMCFG_CR_WSC_0 | RAMCFG_CR_WSC_1)                   /* RAMCFG 3 Wait State */
#define RAMCFG_WAITSTATE_4   (RAMCFG_CR_WSC_2)                                     /* RAMCFG 4 Wait State */
#define RAMCFG_WAITSTATE_5   (RAMCFG_CR_WSC_0 | RAMCFG_CR_WSC_2)                   /* RAMCFG 5 Wait State */
#define RAMCFG_WAITSTATE_6   (RAMCFG_CR_WSC_1 | RAMCFG_CR_WSC_2)                   /* RAMCFG 6 Wait State */
#define RAMCFG_WAITSTATE_7   (RAMCFG_CR_WSC_0 | RAMCFG_CR_WSC_1 | RAMCFG_CR_WSC_2) /* RAMCFG 7 Wait State */
/**
  * @}
  */

/** @defgroup RAMCFG_Keys RAMCFG Keys
  * @brief    RAMCFG Keys
  * @{
  */
#define RAMCFG_ERASE_KEY1  (0xCAU) /* RAMCFG launch Erase Key 1 */
#define RAMCFG_ERASE_KEY2  (0x53U) /* RAMCFG launch Erase Key 2 */

#define RAMCFG_ECC_KEY1    (0xAEU) /* RAMCFG launch ECC Key 1 */
#define RAMCFG_ECC_KEY2    (0x75U) /* RAMCFG launch ECC Key 2 */
/**
  * @}
  */


/**
  * @}
  */





/* Exported macro ------------------------------------------------------------*/

/** @defgroup RAMCFG_Exported_Macros RAMCFG Exported Macros
  * @brief    RAMCFG Exported Macros
  * @{
  */

/**
  * @brief  Enable the specified RAMCFG interrupts.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __INTERRUPT__: Specifies the RAMCFG interrupt sources to be enabled.
  *         This parameter can be one of the following values:
  *           @arg RAMCFG_IT_SINGLEERR    : Single Error Interrupt Mask.
  *           @arg RAMCFG_IT_DOUBLEERR    : Double Error Interrupt Mask.
  *           @arg RAMCFG_IT_NMIERR       : Double Error Interrupt redirection to NMI Mask.
  *           @arg RAMCFG_IT_ALL          : All Interrupt Mask.
  * @retval None
  */
#define __HAL_RAMCFG_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
  ((__HANDLE__)->Instance->IER |= (__INTERRUPT__))

/**
  * @brief  Disable the specified RAMCFG interrupts.
  * @note   This macros is used only to disable RAMCFG_IT_SINGLEERR and RAMCFG_IT_DOUBLEERR
  *         interrupts. RAMCFG_IT_NMIERR interrupt can only be disabled by global  peripheral reset or system reset.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __INTERRUPT__: Specifies the RAMCFG interrupt sources to be disabled.
  *         This parameter can be one of the following values:
  *           @arg RAMCFG_IT_SINGLEERR    : Single Error Interrupt Mask.
  *           @arg RAMCFG_IT_DOUBLEERR    : Double Error Interrupt Mask.
  * @retval None
  */
#define __HAL_RAMCFG_DISABLE_IT(__HANDLE__, __INTERRUPT__) \
  ((__HANDLE__)->Instance->IER &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified RAMCFG interrupt source is enabled or not.
  * @param  __HANDLE__    : Specifies the RAMCFG Handle.
  * @param  __INTERRUPT__ : Specifies the RAMCFG interrupt source to check.
  *          This parameter can be one of the following values:
  *           @arg RAMCFG_IT_SINGLEERR    : Single Error Interrupt Mask.
  *           @arg RAMCFG_IT_DOUBLEERR    : Double Error Interrupt Mask.
  *           @arg RAMCFG_IT_NMIERR       : Double Error Interrupt Redirection to NMI Mask.
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_RAMCFG_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) \
  ((((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__)) ? 1U : 0U)

/**
  * @brief  Get the RAMCFG pending flags.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __FLAG__     : Specifies the flag to be checked.
  *         This parameter can be one of the following values:
  *            @arg RAMCFG_FLAG_SINGLEERR  : Single Error Detected and Corrected Flag.
  *            @arg RAMCFG_FLAG_DOUBLEERR  : Double Error Detected Flag.
  *            @arg RAMCFG_FLAG_SRAMBUSY   : SRAM Busy Flag.
  * @retval The state of FLAG (SET or RESET).
  */
#define __HAL_RAMCFG_GET_FLAG(__HANDLE__, __FLAG__) \
  (READ_BIT((__HANDLE__)->Instance->ISR, (__FLAG__)) == (__FLAG__))

/**
  * @brief  Clear the RAMCFG pending flags.
  * @param  __HANDLE__   : Specifies RAMCFG handle.
  * @param  __FLAG__     : Specifies the flag to be cleared.
  *          This parameter can be any combination of the following values:
  *            @arg RAMCFG_FLAG_SINGLEERR  : Single Error Detected and Corrected Flag.
  *            @arg RAMCFG_FLAG_DOUBLEERR  : Double Error Detected Flag.
  * @retval None.
  */
#define __HAL_RAMCFG_CLEAR_FLAG(__HANDLE__, __FLAG__) \
  ((__HANDLE__)->Instance->ICR |= (__FLAG__))

/** @brief  Reset the RAMCFG handle state.
  * @param  __HANDLE__    : Specifies the RAMCFG Handle.
  * @retval None.
  */
#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
#define __HAL_RAMCFG_RESET_HANDLE_STATE(__HANDLE__) \
  do{\
    (__HANDLE__)->State = HAL_RAMCFG_STATE_RESET; \
    (__HANDLE__)->MspInitCallback   = NULL;       \
    (__HANDLE__)->MspDeInitCallback = NULL;       \
  }while(0)
#else
#define __HAL_RAMCFG_RESET_HANDLE_STATE(__HANDLE__) \
  do{\
    (__HANDLE__)->State = HAL_RAMCFG_STATE_RESET; \
  }while(0)
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup RAMCFG_Exported_Functions RAMCFG Exported Functions
  * @brief    RAMCFG Exported Functions
  * @{
  */

/** @defgroup RAMCFG_Exported_Functions_Group1 Initialization and De-Initialization Functions
  * @brief    Initialization and De-Initialization Functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMCFG_Init(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_DeInit(RAMCFG_HandleTypeDef *hramcfg);
void HAL_RAMCFG_MspInit(RAMCFG_HandleTypeDef *hramcfg);
void HAL_RAMCFG_MspDeInit(RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group2 ECC Operation Functions
  * @brief    ECC Operation Functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMCFG_StartECC(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_StopECC(RAMCFG_HandleTypeDef *hramcfg);
HAL_StatusTypeDef HAL_RAMCFG_EnableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications);
HAL_StatusTypeDef HAL_RAMCFG_DisableNotification(RAMCFG_HandleTypeDef *hramcfg, uint32_t Notifications);
uint32_t HAL_RAMCFG_IsECCSingleErrorDetected(RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_IsECCDoubleErrorDetected(RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_GetSingleErrorAddress(RAMCFG_HandleTypeDef *hramcfg);
uint32_t HAL_RAMCFG_GetDoubleErrorAddress(RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group3 Configure Wait State Functions
  * @brief    Configure Wait State Functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMCFG_ConfigWaitState(RAMCFG_HandleTypeDef *hramcfg, uint32_t WaitState);
uint32_t HAL_RAMCFG_GetWaitState(RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group4 Write Protection Functions
  * @brief    Write Protection Functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMCFG_EnableWriteProtection(RAMCFG_HandleTypeDef *hramcfg, uint32_t StartPage, uint32_t NbPage);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group5 Erase Operation Functions
  * @brief    Erase Operation Functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMCFG_Erase(RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group6 Handle Interrupt and Callbacks Functions
  * @brief    Handle Interrupt and Callbacks Functions
  * @{
  */
void              HAL_RAMCFG_IRQHandler(RAMCFG_HandleTypeDef *hramcfg);
void              HAL_RAMCFG_DetectSingleErrorCallback(RAMCFG_HandleTypeDef *hramcfg);
void              HAL_RAMCFG_DetectDoubleErrorCallback(RAMCFG_HandleTypeDef *hramcfg);
#if (USE_HAL_RAMCFG_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_RAMCFG_RegisterCallback(RAMCFG_HandleTypeDef *hramcfg,
                                              HAL_RAMCFG_CallbackIDTypeDef CallbackID,
                                              void (* pCallback)(RAMCFG_HandleTypeDef *_hramcfg));
HAL_StatusTypeDef HAL_RAMCFG_UnRegisterCallback(RAMCFG_HandleTypeDef *hramcfg, HAL_RAMCFG_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_RAMCFG_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup RAMCFG_Exported_Functions_Group7 State and Error Functions
  * @brief    State and Error Functions
  * @{
  */
uint32_t HAL_RAMCFG_GetError(RAMCFG_HandleTypeDef *hramcfg);
HAL_RAMCFG_StateTypeDef HAL_RAMCFG_GetState(RAMCFG_HandleTypeDef *hramcfg);
/**
  * @}
  */

/**
  * @}
  */

/* Private Constants ---------------------------------------------------------*/

/** @defgroup RAMCFG_Private_Constants RAMCFG Private Defines and Constants
  * @brief    RAMCFG Private Defines and Constants
  * @{
  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup RAMCFG_Private_Macros RAMCFG Private Macros
  * @brief    RAMCFG Private Macros
  * @{
  */
#define IS_RAMCFG_INTERRUPT(INTERRUPT) \
  (((INTERRUPT) != 0U) && (((INTERRUPT) & ~(RAMCFG_IT_SINGLEERR | RAMCFG_IT_DOUBLEERR | RAMCFG_IT_NMIERR)) == 0U))


#define IS_RAMCFG_WAITSTATE(WAITSTATE) \
  (((WAITSTATE) == RAMCFG_WAITSTATE_0) || ((WAITSTATE) == RAMCFG_WAITSTATE_1) || \
   ((WAITSTATE) == RAMCFG_WAITSTATE_2) || ((WAITSTATE) == RAMCFG_WAITSTATE_3) || \
   ((WAITSTATE) == RAMCFG_WAITSTATE_4) || ((WAITSTATE) == RAMCFG_WAITSTATE_5) || \
   ((WAITSTATE) == RAMCFG_WAITSTATE_6) || ((WAITSTATE) == RAMCFG_WAITSTATE_7))

#define IS_RAMCFG_WRITEPROTECTION_PAGE(PAGE)   ((PAGE) <= 64U)



/**
  * @}
  */





/* Private functions ---------------------------------------------------------*/

/** @defgroup RAMCFG_Private_Functions RAMCFG Private Functions
  * @brief    RAMCFG Private Functions
  * @{
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


#endif /* STM32U5xx_HAL_RAMCFG_H */
