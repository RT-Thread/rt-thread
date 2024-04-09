/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_ramecc.h
  * @author  MCD Application Team
  * @brief   Header file of RAMECC HAL module.
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
#ifndef STM32H7RSxx_HAL_RAMECC_H
#define STM32H7RSxx_HAL_RAMECC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @addtogroup RAMECC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RAMECC_Exported_Types RAMECC Exported Types
  * @brief    RAMECC Exported Types
  * @{
  */

/**
  * @brief  HAL RAMECC State structures definition
  */
typedef enum
{
  HAL_RAMECC_STATE_RESET             = 0x00U,  /*!< RAMECC not yet initialized or disabled */
  HAL_RAMECC_STATE_READY             = 0x01U,  /*!< RAMECC initialized and ready for use   */
  HAL_RAMECC_STATE_BUSY              = 0x02U,  /*!< RAMECC process is ongoing              */
  HAL_RAMECC_STATE_ERROR             = 0x03U,  /*!< RAMECC error state                     */
} HAL_RAMECC_StateTypeDef;

#if (USE_HAL_RAMECC_REGISTER_CALLBACKS == 1)
/**
  * @brief  HAL RAMECC Callbacks IDs Enumeration Definition
  */
typedef enum
{
  HAL_RAMECC_MSPINIT_CB_ID           = 0x00U,  /*!< RAMECC MSP Init Callback ID            */
  HAL_RAMECC_MSPDEINIT_CB_ID         = 0x01U,  /*!< RAMECC MSP DeInit Callback ID          */
  HAL_RAMECC_SE_DETECT_CB_ID         = 0x02U,  /*!< RAMECC Single Error Detect Callback ID */
  HAL_RAMECC_DE_DETECT_CB_ID         = 0x03U,  /*!< RAMECC Double Error Detect Callback ID */
  HAL_RAMECC_ALL_CB_ID               = 0x04U,  /*!< RAMECC All callback ID                 */
} HAL_RAMECC_CallbackIDTypeDef;
#endif /* USE_HAL_RAMECC_REGISTER_CALLBACKS */

/**
  * @brief  RAMECC handle Structure definition
  */

#if (USE_HAL_RAMECC_REGISTER_CALLBACKS == 1)
typedef struct __RAMECC_HandleTypeDef
#else
typedef struct
#endif /* (USE_HAL_RAMECC_REGISTER_CALLBACKS) */
{
  RAMECC_MonitorTypeDef           *Instance;                                                            /*!< Register base address        */
  __IO HAL_RAMECC_StateTypeDef    State;                                                                /*!< RAMECC state                 */
  __IO uint32_t                   ErrorCode;                                                            /*!< RAMECC Error Code            */
#if (USE_HAL_RAMECC_REGISTER_CALLBACKS == 1)
  void (* MspInitCallback)(struct __RAMECC_HandleTypeDef *hramecc);                                     /*!< RAMECC MSP Init Callback            */
  void (* MspDeInitCallback)(struct __RAMECC_HandleTypeDef *hramecc);                                   /*!< RAMECC MSP DeInit Callback          */
  void (* DetectSingleErrorCallback)(struct __RAMECC_HandleTypeDef *hramecc);                           /*!< RAMECC Single Error Detect Callback */
  void (* DetectDoubleErrorCallback)(struct __RAMECC_HandleTypeDef *hramecc);                           /*!< RAMECC Double Error Detect Callback */
#endif  /* USE_HAL_RAMECC_REGISTER_CALLBACKS */
} RAMECC_HandleTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup RAMECC_Error_Codes RAMECC Error Codes
  * @{
  */
#define HAL_RAMECC_ERROR_NONE              0x00000000U  /*!< RAMECC No Error         */
#define HAL_RAMECC_ERROR_TIMEOUT           0x00000001U  /*!< RAMECC Timeout Error    */
#define HAL_RAMECC_ERROR_BUSY              0x00000002U  /*!< RAMECC Busy Error       */
#if (USE_HAL_RAMECC_REGISTER_CALLBACKS == 1)
#define HAL_RAMECC_ERROR_INVALID_CALLBACK  0x00000003U  /*!< Invalid Callback error  */
#endif  /* USE_HAL_RAMECC_REGISTER_CALLBACKS */

/**
  * @}
  */

/** @defgroup RAMECC_Interrupt RAMECC interrupts
  * @{
  */
#define RAMECC_IT_GLOBAL_ID                0x10000000UL
#define RAMECC_IT_MONITOR_ID               0x20000000UL

#define RAMECC_IT_GLOBAL_ALL_ENABLE        (RAMECC_IT_GLOBAL_ID | RAMECC_IER_GIE)
#define RAMECC_IT_GLOBAL_SINGLEERR_R       (RAMECC_IT_GLOBAL_ID | RAMECC_IER_GECCSEIE)
#define RAMECC_IT_GLOBAL_DOUBLEERR_R       (RAMECC_IT_GLOBAL_ID | RAMECC_IER_GECCDEIE)
#define RAMECC_IT_GLOBAL_DOUBLEERR_W       (RAMECC_IT_GLOBAL_ID | RAMECC_IER_GECCDEBWIE)

#define RAMECC_IT_MONITOR_SINGLEERR_R      (RAMECC_IT_MONITOR_ID | RAMECC_CR_ECCSEIE)
#define RAMECC_IT_MONITOR_DOUBLEERR_R      (RAMECC_IT_MONITOR_ID | RAMECC_CR_ECCDEIE)
#define RAMECC_IT_MONITOR_DOUBLEERR_W      (RAMECC_IT_MONITOR_ID | RAMECC_CR_ECCDEBWIE)
#define RAMECC_IT_MONITOR_ALL              (RAMECC_IT_MONITOR_ID | RAMECC_CR_ECCDEBWIE | RAMECC_CR_ECCDEIE | RAMECC_CR_ECCSEIE)
/**
  * @}
  */

/** @defgroup RAMECC_FLAG RAMECC Monitor flags
  * @{
  */
#define RAMECC_FLAG_SINGLEERR_R            RAMECC_SR_SEDCF
#define RAMECC_FLAG_DOUBLEERR_R            RAMECC_SR_DEDF
#define RAMECC_FLAG_DOUBLEERR_W            RAMECC_SR_DEBWDF
#define RAMECC_FLAGS_ALL                   (RAMECC_SR_SEDCF | RAMECC_SR_DEDF | RAMECC_SR_DEBWDF)

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup RAMECC_Exported_Macros RAMECC Exported Macros
  * @{
  */

#define __HAL_RAMECC_ENABLE_GLOBAL_IT(__HANDLE__, __INTERRUPT__) ((((RAMECC_TypeDef *)((uint32_t)(__HANDLE__)->Instance & 0xFFFFFF00U))->IER) |= ((__INTERRUPT__) & ~RAMECC_IT_GLOBAL_ID))
#define __HAL_RAMECC_ENABLE_MONITOR_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->CR |= ((__INTERRUPT__) & ~RAMECC_IT_MONITOR_ID))

/**
  * @brief  Enable the specified RAMECC interrupts.
  * @param  __HANDLE__   : RAMECC handle.
  * @param  __INTERRUPT__: specifies the RAMECC interrupt sources to be enabled.
  *        This parameter can be one of the following values:
  *           @arg RAMECC_IT_GLOBAL_ALL_ENABLE   : All Global ECC  interrupts enable.
  *           @arg RAMECC_IT_GLOBAL_SINGLEERR_R  : Global ECC single error interrupt enable.
  *           @arg RAMECC_IT_GLOBAL_DOUBLEERR_R  : Global ECC double error interrupt enable.
  *           @arg RAMECC_IT_GLOBAL_DOUBLEERR_W  : Global ECC double error on byte write (BW) interrupt enable.
  *           @arg RAMECC_IT_MONITOR_SINGLEERR_R : Monitor ECC single error interrupt enable.
  *           @arg RAMECC_IT_MONITOR_DOUBLEERR_R : Monitor ECC double error interrupt enable.
  *           @arg RAMECC_IT_MONITOR_DOUBLEERR_W : Monitor ECC double error on byte write (BW) interrupt enable.
  *           @arg RAMECC_IT_MONITOR_ALL         : All Monitor ECC interrupts enable.
  * @retval None
  */
#define __HAL_RAMECC_ENABLE_IT(__HANDLE__, __INTERRUPT__) ( \
(IS_RAMECC_GLOBAL_INTERRUPT(__INTERRUPT__)) ? (__HAL_RAMECC_ENABLE_GLOBAL_IT((__HANDLE__), (__INTERRUPT__))) :\
(__HAL_RAMECC_ENABLE_MONITOR_IT((__HANDLE__), (__INTERRUPT__))))


#define __HAL_RAMECC_DISABLE_GLOBAL_IT(__HANDLE__, __INTERRUPT__) ((((RAMECC_TypeDef *)((uint32_t)(__HANDLE__)->Instance & 0xFFFFFF00U))->IER) &= ~((__INTERRUPT__) & ~RAMECC_IT_GLOBAL_ID))
#define __HAL_RAMECC_DISABLE_MONITOR_IT(__HANDLE__, __INTERRUPT__) ((__HANDLE__)->Instance->CR &= ~((__INTERRUPT__) & ~RAMECC_IT_MONITOR_ID))

/**
  * @brief  Disable the specified RAMECC interrupts.
  * @param  __HANDLE__   : RAMECC handle.
  * @param  __INTERRUPT__: specifies the RAMECC interrupt sources to be disabled.
  *        This parameter can be one of the following values:
  *           @arg RAMECC_IT_GLOBAL_ALL_ENABLE   : All Global ECC  interrupts disable.
  *           @arg RAMECC_IT_GLOBAL_SINGLEERR_R  : Global ECC single error interrupt disable.
  *           @arg RAMECC_IT_GLOBAL_DOUBLEERR_R  : Global ECC double error interrupt disable.
  *           @arg RAMECC_IT_GLOBAL_DOUBLEERR_W  : Global ECC double error on byte write (BW) interrupt disable.
  *           @arg RAMECC_IT_MONITOR_SINGLEERR_R : Monitor ECC single error interrupt disable.
  *           @arg RAMECC_IT_MONITOR_DOUBLEERR_R : Monitor ECC double error interrupt disable.
  *           @arg RAMECC_IT_MONITOR_DOUBLEERR_W : Monitor ECC double error on byte write (BW) interrupt disable.
  *           @arg RAMECC_IT_MONITOR_ALL         : All Monitor ECC interrupts disable.
  * @retval None
  */
#define __HAL_RAMECC_DISABLE_IT(__HANDLE__, __INTERRUPT__) ( \
(IS_RAMECC_GLOBAL_INTERRUPT(__INTERRUPT__)) ? (__HAL_RAMECC_DISABLE_GLOBAL_IT((__HANDLE__), (__INTERRUPT__))) :\
(__HAL_RAMECC_DISABLE_MONITOR_IT((__HANDLE__), (__INTERRUPT__))))


#define __HAL_RAMECC_GET_GLOBAL_IT_SOURCE(__HANDLE__, __INTERRUPT__) (((((RAMECC_TypeDef *)((uint32_t)(__HANDLE__)->Instance & 0xFFFFFF00U))->IER) & ((__INTERRUPT__) & ~RAMECC_IT_GLOBAL_ID)) ? SET : RESET)
#define __HAL_RAMECC_GET_MONITOR_IT_SOURCE(__HANDLE__, __INTERRUPT__) ((((__HANDLE__)->Instance->CR) & ((__INTERRUPT__) & ~RAMECC_IT_MONITOR_ID)) ? SET : RESET)

/**
  * @brief  Check whether the specified RAMECC interrupt source is enabled or not.
  * @param  __HANDLE__    : Specifies the RAMECC Handle.
  * @param  __INTERRUPT__ : Specifies the RAMECC interrupt source to check.
  *          This parameter can be one of the following values:
  *           @arg RAMECC_IT_GLOBAL_ALL_ENABLE   : All Global ECC interrupts enable.
  *           @arg RAMECC_IT_GLOBAL_SINGLEERR_R  : Global ECC single error interrupt enable.
  *           @arg RAMECC_IT_GLOBAL_DOUBLEERR_R  : Global ECC double error interrupt enable.
  *           @arg RAMECC_IT_GLOBAL_DOUBLEERR_W  : Global ECC double error on byte write (BW) interrupt enable.
  *           @arg RAMECC_IT_MONITOR_SINGLEERR_R : Monitor ECC single error interrupt enable.
  *           @arg RAMECC_IT_MONITOR_DOUBLEERR_R : Monitor ECC double error interrupt enable.
  *           @arg RAMECC_IT_MONITOR_DOUBLEERR_W : Monitor ECC double error on byte write (BW) interrupt enable.
  *           @arg RAMECC_IT_MONITOR_ALL         : All Monitor ECC interrupts enable.
  * @retval The new state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_RAMECC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) (  \
(IS_RAMECC_GLOBAL_INTERRUPT(__INTERRUPT__)) ? (__HAL_RAMECC_GET_GLOBAL_IT_SOURCE((__HANDLE__), (__INTERRUPT__))) :\
(__HAL_RAMECC_GET_MONITOR_IT_SOURCE((__HANDLE__), (__INTERRUPT__))))


/**
  * @brief  Get the RAMECC pending flags.
  * @param  __HANDLE__   : RAMECC handle.
  * @param  __FLAG__     : specifies the flag to get.
  *          This parameter can be any combination of the following values:
  *            @arg RAMECC_FLAG_SINGLEERR_R : RAMECC instance ECC single error detected and corrected flag.
  *            @arg RAMECC_FLAG_DOUBLEERR_R : RAMECC instance ECC double error detected flag.
  *            @arg RAMECC_FLAG_DOUBLEERR_W : RAMECC instance ECC double error on byte write (BW) detected flag.
  *            @arg RAMECC_FLAGS_ALL        : RAMECC instance all flag.
  * @retval The state of __FLAG__ (SET or RESET).
  */
#define __HAL_RAMECC_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->SR & (__FLAG__)) != 0U) ? 1UL : 0UL)

/**
  * @brief  Clear the RAMECC pending flags.
  * @param  __HANDLE__   : RAMECC handle.
  * @param  __FLAG__     : specifies the flag to clear.
  *          This parameter can be any combination of the following values:
  *            @arg RAMECC_FLAG_SINGLEERR_R : RAMECC instance ECC single error detected and corrected flag.
  *            @arg RAMECC_FLAG_DOUBLEERR_R : RAMECC instance ECC double error detected flag.
  *            @arg RAMECC_FLAG_DOUBLEERR_W : RAMECC instance ECC double error on byte write (BW) detected flag.
  *            @arg RAMECC_FLAGS_ALL        : RAMECC instance all flag.
  * @retval None.
  */
#define __HAL_RAMECC_CLEAR_FLAG(__HANDLE__, __FLAG__) ((__HANDLE__)->Instance->SR &= ~(__FLAG__))

/**
  * @brief  Reset the RAMECC handle state.
  * @param  __HANDLE__    : Specifies the RAMECC Handle.
  * @retval None.
  */
#define __HAL_RAMECC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_RAMECC_STATE_RESET)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup RAMECC_Exported_Functions RAMECC Exported Functions
  * @brief    RAMECC Exported functions
  * @{
  */

/** @defgroup RAMECC_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and de-initialization functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMECC_Init(RAMECC_HandleTypeDef *hramecc);
HAL_StatusTypeDef HAL_RAMECC_DeInit(RAMECC_HandleTypeDef *hramecc);
void              HAL_RAMECC_MspInit(RAMECC_HandleTypeDef *hramecc);
void              HAL_RAMECC_MspDeInit(RAMECC_HandleTypeDef *hramecc);
/**
  * @}
  */

/** @defgroup RAMECC_Exported_Functions_Group2 Monitoring operation functions
  * @brief    Monitoring operation functions
  * @{
  */
HAL_StatusTypeDef HAL_RAMECC_StartMonitor(RAMECC_HandleTypeDef *hramecc);
HAL_StatusTypeDef HAL_RAMECC_StopMonitor(RAMECC_HandleTypeDef *hramecc);
HAL_StatusTypeDef HAL_RAMECC_EnableNotification(RAMECC_HandleTypeDef *hramecc, uint32_t Notifications);
HAL_StatusTypeDef HAL_RAMECC_DisableNotification(RAMECC_HandleTypeDef *hramecc, uint32_t Notifications);
/**
  * @}
  */

/** @defgroup RAMCECC_Exported_Functions_Group3 Handle Interrupt and Callbacks functions
  * @brief    Handle Interrupt and Callbacks functions
  * @{
  */
void              HAL_RAMECC_IRQHandler(RAMECC_HandleTypeDef *hramecc);
void              HAL_RAMECC_DetectSingleErrorCallback(RAMECC_HandleTypeDef *hramecc);
void              HAL_RAMECC_DetectDoubleErrorCallback(RAMECC_HandleTypeDef *hramecc);
#if (USE_HAL_RAMECC_REGISTER_CALLBACKS == 1)
HAL_StatusTypeDef HAL_RAMECC_RegisterCallback(RAMECC_HandleTypeDef *hramecc,
                                              HAL_RAMECC_CallbackIDTypeDef CallbackID,
                                              void (* pCallback)(RAMECC_HandleTypeDef *_hramecc));

HAL_StatusTypeDef HAL_RAMECC_UnRegisterCallback(RAMECC_HandleTypeDef *hramecc,
                                                HAL_RAMECC_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_RAMECC_REGISTER_CALLBACKS */


/**
  * @}
  */

/** @defgroup RAMECC_Exported_Functions_Group4 Error information functions
  * @brief    Error information functions
  * @{
  */
uint32_t HAL_RAMECC_GetFailingAddress(const RAMECC_HandleTypeDef *hramecc);
uint32_t HAL_RAMECC_GetFailingDataLow(const RAMECC_HandleTypeDef *hramecc);
uint32_t HAL_RAMECC_GetFailingDataHigh(const RAMECC_HandleTypeDef *hramecc);
uint32_t HAL_RAMECC_GetHammingErrorCode(const RAMECC_HandleTypeDef *hramecc);
uint32_t HAL_RAMECC_IsECCSingleErrorDetected(const RAMECC_HandleTypeDef *hramecc);
uint32_t HAL_RAMECC_IsECCDoubleErrorDetected(const RAMECC_HandleTypeDef *hramecc);
/**
  * @}
  */

/** @defgroup RAMECC_Exported_Functions_Group5 State and Error functions
  * @brief    State and Error functions
  * @{
  */
HAL_RAMECC_StateTypeDef HAL_RAMECC_GetState(const RAMECC_HandleTypeDef *hramecc);
uint32_t                HAL_RAMECC_GetError(const RAMECC_HandleTypeDef *hramecc);
/**
  * @}
  */

/**
  * @}
  */
/* Private Constants -------------------------------------------------------------*/
/** @defgroup RAMECC_Private_Constants RAMECC Private Constants
  * @brief    RAMECC private defines and constants
  * @{
  */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup RAMECC_Private_Macros RAMECC Private Macros
  * @brief    RAMECC private macros
  * @{
  */

#define IS_RAMECC_GLOBAL_INTERRUPT(INTERRUPT) (((INTERRUPT) == RAMECC_IT_GLOBAL_ALL_ENABLE)  || \
                                               ((INTERRUPT) == RAMECC_IT_GLOBAL_SINGLEERR_R) || \
                                               ((INTERRUPT) == RAMECC_IT_GLOBAL_DOUBLEERR_R) || \
                                               ((INTERRUPT) == RAMECC_IT_GLOBAL_DOUBLEERR_W))


#define IS_RAMECC_MONITOR_INTERRUPT(INTERRUPT) (((INTERRUPT) == RAMECC_IT_MONITOR_SINGLEERR_R) || \
                                                ((INTERRUPT) == RAMECC_IT_MONITOR_DOUBLEERR_R) || \
                                                ((INTERRUPT) == RAMECC_IT_MONITOR_DOUBLEERR_W) || \
                                                ((INTERRUPT) == RAMECC_IT_MONITOR_ALL))

#define IS_RAMECC_INTERRUPT(INTERRUPT) ((IS_RAMECC_GLOBAL_INTERRUPT(INTERRUPT)) || \
                                        (IS_RAMECC_MONITOR_INTERRUPT(INTERRUPT)))

/**
  * @}
  */

/** @defgroup RAMECC_FLAG RAMECC Monitor flags
  * @{
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup RAMECC_Private_Functions RAMECC Private Functions
  * @brief    RAMECC private  functions
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

/**
  * @}
  */
#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_HAL_RAMECC_H */

