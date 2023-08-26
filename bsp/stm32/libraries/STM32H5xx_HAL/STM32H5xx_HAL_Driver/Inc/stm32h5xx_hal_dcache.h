/**
  ******************************************************************************
  * @file    stm32h5xx_hal_dcache.h
  * @author  MCD Application Team
  * @brief   Header file of DCACHE HAL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef STM32H5xx_HAL_DCACHE_H
#define STM32H5xx_HAL_DCACHE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes -----------------------------------------------------------------*/
#include "stm32h5xx_hal_def.h"

/** @addtogroup STM32H5xx_HAL_Driver
  * @{
  */

#if defined (DCACHE1)

/** @addtogroup DCACHE
  * @{
  */
/* Exported types ------------------------------------------------------------*/

/** @defgroup DCACHE_Exported_Types DCACHE Exported Types
  * @{
  */

/**
  * @brief DCACHE Init structure definition
  */
typedef struct
{
  uint32_t ReadBurstType; /*!< Burst type to be applied for Data Cache
                               This parameter can be a value of @ref DCACHE_Read_Burst_Type*/
} DCACHE_InitTypeDef;

/**
  * @brief  HAL State structures definition
  */
typedef enum
{
  HAL_DCACHE_STATE_RESET   = 0x00U, /*!< DCACHE not yet initialized or disabled     */
  HAL_DCACHE_STATE_READY   = 0x01U, /*!< Peripheral initialized and ready for use   */
  HAL_DCACHE_STATE_BUSY    = 0x02U, /*!< An internal process is ongoing             */
  HAL_DCACHE_STATE_TIMEOUT = 0x05U, /*!< Timeout state                              */
  HAL_DCACHE_STATE_ERROR   = 0x06U, /*!< DCACHE state error                         */
} HAL_DCACHE_StateTypeDef;

/** @defgroup DCACHE_Configuration_Structure_definition DCACHE Configuration Structure definition
  * @brief  DCACHE Configuration Structure definition
  * @{
  */
typedef struct __DCACHE_HandleTypeDef
{
  DCACHE_TypeDef         *Instance;    /*!< DCACHE register base address.    */
  DCACHE_InitTypeDef      Init;        /*!< DCACHE Initialization Structure. */

  void (* ErrorCallback)(struct __DCACHE_HandleTypeDef *hdcache);
  void (* CleanByAddrCallback)(struct __DCACHE_HandleTypeDef *hdcache);
  void (* InvalidateByAddrCallback)(struct __DCACHE_HandleTypeDef *hdcache);
  void (* InvalidateCompleteCallback)(struct __DCACHE_HandleTypeDef *hdcache);
  void (* CleanAndInvalidateByAddrCallback)(struct __DCACHE_HandleTypeDef *hdcache);

  void (* MspInitCallback)(struct __DCACHE_HandleTypeDef *hdcache);
  void (* MspDeInitCallback)(struct __DCACHE_HandleTypeDef *hdcache);

  __IO HAL_DCACHE_StateTypeDef State;
  __IO uint32_t               ErrorCode;
} DCACHE_HandleTypeDef;

/**
  * @brief  HAL DCACHE Callback pointer definition
  */
/*!< Pointer to a DCACHE common callback function */
typedef  void (*pDCACHE_CallbackTypeDef)(DCACHE_HandleTypeDef *hdcache);

/**
  * @brief  HAL DCACHE Callback ID enumeration definition
  */
typedef enum
{
  HAL_DCACHE_CLEAN_BY_ADDRESS_CB_ID                 = 0x00U, /*!< DCACHE Clean By Address callback ID                */
  HAL_DCACHE_INVALIDATE_BY_ADDRESS_CB_ID            = 0x01U, /*!< DCACHE Invalidate By Address callback ID           */
  HAL_DCACHE_CLEAN_AND_INVALIDATE_BY_ADDRESS_CB_ID  = 0x02U, /*!< DCACHE Clean And Invalidate By Address callback ID */
  HAL_DCACHE_INVALIDATE_COMPLETE_CB_ID              = 0x03U, /*!< DCACHE Invalidate Complete ID                      */
  HAL_DCACHE_ERROR_CB_ID                            = 0x04U, /*!< DCACHE Error callback ID                           */

  HAL_DCACHE_MSPINIT_CB_ID                          = 0x05U, /*!< DCACHE Msp Init callback ID                        */
  HAL_DCACHE_MSPDEINIT_CB_ID                        = 0x06U  /*!< DCACHE Msp DeInit callback ID                      */
} HAL_DCACHE_CallbackIDTypeDef;

/**
  * @}
  */

/**
  * @}
  */

/* Exported constants -------------------------------------------------------*/
/** @defgroup DCACHE_Exported_Constants DCACHE Exported Constants
  * @{
  */

/** @defgroup DCACHE_Error_Code DCACHE Error Code
  * @{
  */
#define HAL_DCACHE_ERROR_NONE              0x00000000U /*!< No error                */
#define HAL_DCACHE_ERROR_TIMEOUT           0x00000010U /*!< Timeout error           */
#define HAL_DCACHE_ERROR_INVALID_CALLBACK  0x00000020U /*!< Invalid callback error  */
#define HAL_DCACHE_ERROR_EVICTION_CLEAN    0x00000040U /*!< Eviction or clean operation write-back error */
#define HAL_DCACHE_ERROR_INVALID_OPERATION 0x00000080U /*!< Invalid operation       */

/**
  * @}
  */

/** @defgroup DCACHE_Monitor_Type Monitor type
  * @{
  */
#define DCACHE_MONITOR_READ_HIT        DCACHE_CR_RHITMEN   /*!< Read Hit monitoring */
#define DCACHE_MONITOR_READ_MISS       DCACHE_CR_RMISSMEN  /*!< Read Miss monitoring */
#define DCACHE_MONITOR_WRITE_HIT       DCACHE_CR_WHITMEN   /*!< Write Hit monitoring */
#define DCACHE_MONITOR_WRITE_MISS      DCACHE_CR_WMISSMEN  /*!< Write Miss monitoring */
#define DCACHE_MONITOR_ALL             (DCACHE_CR_RHITMEN | DCACHE_CR_RMISSMEN | \
                                        DCACHE_CR_WHITMEN | DCACHE_CR_WMISSMEN)
/**
  * @}
  */

/** @defgroup DCACHE_Read_Burst_Type Remapped Output burst type
  * @{
  */
#define DCACHE_READ_BURST_WRAP         0U                  /*!< WRAP */
#define DCACHE_READ_BURST_INCR         DCACHE_CR_HBURST    /*!< INCR */
/**
  * @}
  */

/** @defgroup DCACHE_Interrupts Interrupts
  * @{
  */
#define DCACHE_IT_BUSYEND              DCACHE_IER_BSYENDIE /*!< Busy end interrupt */
#define DCACHE_IT_ERROR                DCACHE_IER_ERRIE    /*!< Cache error interrupt */
#define DCACHE_IT_CMDEND               DCACHE_IER_CMDENDIE /*!< Command end interrupt */
/**
  * @}
  */

/** @defgroup DCACHE_Flags Flags
  * @{
  */
#define DCACHE_FLAG_BUSY               DCACHE_SR_BUSYF     /*!< Busy flag */
#define DCACHE_FLAG_BUSYEND            DCACHE_SR_BSYENDF   /*!< Busy end flag */
#define DCACHE_FLAG_ERROR              DCACHE_SR_ERRF      /*!< Cache error flag */
#define DCACHE_FLAG_BUSYCMD            DCACHE_SR_BUSYCMDF  /*!< Busy command flag */
#define DCACHE_FLAG_CMDEND             DCACHE_SR_CMDENDF   /*!< Command end flag */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros ----------------------------------------------------------*/
/** @defgroup DCACHE_Exported_Macros DCACHE Exported Macros
  * @{
  */

/** @brief  Enable DCACHE interrupts.
  * @param  __HANDLE__ specifies the DCACHE handle.
  * @param  __INTERRUPT__ specifies the DCACHE interrupt sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref DCACHE_IT_BUSYEND  Busy end interrupt
  *            @arg @ref DCACHE_IT_ERROR    Cache error interrupt
  *            @arg @ref DCACHE_IT_CMDEND   Cache Command end interrupt
  * @retval None
  */
#define __HAL_DCACHE_ENABLE_IT(__HANDLE__, __INTERRUPT__) SET_BIT((__HANDLE__)->Instance->IER, (__INTERRUPT__))

/** @brief  Disable DCACHE interrupts.
  * @param  __HANDLE__ specifies the DCACHE handle.
  * @param  __INTERRUPT__ specifies the DCACHE interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg @ref DCACHE_IT_BUSYEND  Busy end interrupt
  *            @arg @ref DCACHE_IT_ERROR    Cache error interrupt
  *            @arg @ref DCACHE_IT_CMDEND   Cache Command end interrupt
  * @retval None
  */
#define __HAL_DCACHE_DISABLE_IT(__HANDLE__, __INTERRUPT__) CLEAR_BIT((__HANDLE__)->Instance->IER, (__INTERRUPT__))

/** @brief  Check whether the specified DCACHE interrupt source is enabled or not.
  * @param  __HANDLE__ specifies the DCACHE handle.
  * @param  __INTERRUPT__ specifies the DCACHE interrupt source to check.
  *         This parameter can be any combination of the following values:
  *            @arg @ref DCACHE_IT_BUSYEND  Busy end interrupt
  *            @arg @ref DCACHE_IT_ERROR    Cache error interrupt
  *            @arg @ref DCACHE_IT_CMDEND   Cache Command end interrupt
  *
  * @retval The state of __INTERRUPT__ (SET or RESET).
  */
#define __HAL_DCACHE_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  \
  ((READ_BIT((__HANDLE__)->Instance->IER, (__INTERRUPT__)) == (__INTERRUPT__)) ? SET : RESET)

/** @brief  Check whether the selected DCACHE flag is set or not.
  * @param  __HANDLE__ specifies the DCACHE handle.
  * @param  __FLAG__   specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref DCACHE_FLAG_BUSY     Busy flag
  *            @arg @ref DCACHE_FLAG_BUSYEND  Busy end flag
  *            @arg @ref DCACHE_FLAG_ERROR    Cache error flag
  *            @arg @ref DCACHE_FLAG_BUSYCMD  Cache Busy command flag
  *            @arg @ref DCACHE_FLAG_CMDEND   Cache command end flag
  * @retval The state of __FLAG__ (0 or 1).
  */
#define __HAL_DCACHE_GET_FLAG(__HANDLE__, __FLAG__) ((READ_BIT((__HANDLE__)->Instance->SR, (__FLAG__)) != 0U) ? 1U : 0U)

/** @brief  Clear the selected DCACHE flags.
  * @param  __HANDLE__ specifies the DCACHE handle.
  * @param  __FLAG__   specifies the DCACHE flags to clear.
  *         This parameter can be any combination of the following values:
  *            @arg @ref DCACHE_FLAG_BUSYEND  Busy end flag
  *            @arg @ref DCACHE_FLAG_ERROR    Cache error flag
  *            @arg @ref DCACHE_FLAG_CMDEND   Cache command end flag
  */
#define __HAL_DCACHE_CLEAR_FLAG(__HANDLE__, __FLAG__) WRITE_REG((__HANDLE__)->Instance->FCR, (__FLAG__))

/**
  * @}
  */

/* Exported functions -------------------------------------------------------*/
/** @defgroup DCACHE_Exported_Functions DCACHE Exported Functions
  * @brief    DCACHE Exported functions
  * @{
  */

/** @defgroup DCACHE_Exported_Functions_Group1 Initialization and De-Initialization Functions
  * @brief    Initialization and De-Initialization Functions
  * @{
  */
HAL_StatusTypeDef HAL_DCACHE_Init(DCACHE_HandleTypeDef *hdcache);
HAL_StatusTypeDef HAL_DCACHE_DeInit(DCACHE_HandleTypeDef *hdcache);
void              HAL_DCACHE_MspInit(DCACHE_HandleTypeDef *hdcache);
void              HAL_DCACHE_MspDeInit(DCACHE_HandleTypeDef *hdcache);
/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group2 I/O Operation Functions
  * @brief    I/O Operation Functions
  * @{
  */
/* Peripheral Control functions ***/
HAL_StatusTypeDef HAL_DCACHE_Enable(DCACHE_HandleTypeDef *hdcache);
HAL_StatusTypeDef HAL_DCACHE_Disable(DCACHE_HandleTypeDef *hdcache);
uint32_t          HAL_DCACHE_IsEnabled(const DCACHE_HandleTypeDef *hdcache);
HAL_StatusTypeDef HAL_DCACHE_SetReadBurstType(DCACHE_HandleTypeDef *hdcache, uint32_t ReadBurstType);

/*** Cache maintenance in blocking mode (Polling) ***/
HAL_StatusTypeDef HAL_DCACHE_Invalidate(DCACHE_HandleTypeDef *hdcache);
HAL_StatusTypeDef HAL_DCACHE_InvalidateByAddr(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                              uint32_t dSize);
HAL_StatusTypeDef HAL_DCACHE_CleanByAddr(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr, uint32_t dSize);
HAL_StatusTypeDef HAL_DCACHE_CleanInvalidByAddr(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                                uint32_t dSize);

/*** Cache maintenance in non-blocking mode (Interrupt) ***/
HAL_StatusTypeDef HAL_DCACHE_Invalidate_IT(DCACHE_HandleTypeDef *hdcache);
HAL_StatusTypeDef HAL_DCACHE_InvalidateByAddr_IT(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                                 uint32_t dSize);
HAL_StatusTypeDef HAL_DCACHE_CleanByAddr_IT(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                            uint32_t dSize);
HAL_StatusTypeDef HAL_DCACHE_CleanInvalidByAddr_IT(DCACHE_HandleTypeDef *hdcache, const uint32_t *const pAddr,
                                                   uint32_t dSize);

/*** IRQHandler and Callbacks ***/
void HAL_DCACHE_IRQHandler(DCACHE_HandleTypeDef *hdcache);
void HAL_DCACHE_ErrorCallback(DCACHE_HandleTypeDef *hdcache);
void HAL_DCACHE_CleanByAddrCallback(DCACHE_HandleTypeDef *hdcache);
void HAL_DCACHE_InvalidateByAddrCallback(DCACHE_HandleTypeDef *hdcache);
void HAL_DCACHE_InvalidateCompleteCallback(DCACHE_HandleTypeDef *hdcache);
void HAL_DCACHE_CleanAndInvalidateByAddrCallback(DCACHE_HandleTypeDef *hdcache);

/* Callbacks Register/UnRegister functions ***/
HAL_StatusTypeDef HAL_DCACHE_RegisterCallback(DCACHE_HandleTypeDef *hdcache, HAL_DCACHE_CallbackIDTypeDef CallbackID,
                                              pDCACHE_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_DCACHE_UnRegisterCallback(DCACHE_HandleTypeDef *hdcache, HAL_DCACHE_CallbackIDTypeDef CallbackID);

/*** Performance instruction cache monitoring functions ***/
uint32_t HAL_DCACHE_Monitor_GetReadHitValue(const DCACHE_HandleTypeDef *hdcache);
uint32_t HAL_DCACHE_Monitor_GetReadMissValue(const DCACHE_HandleTypeDef *hdcache);
uint32_t HAL_DCACHE_Monitor_GetWriteHitValue(const DCACHE_HandleTypeDef *hdcache);
uint32_t HAL_DCACHE_Monitor_GetWriteMissValue(const DCACHE_HandleTypeDef *hdcache);
HAL_StatusTypeDef HAL_DCACHE_Monitor_Reset(DCACHE_HandleTypeDef *hdcache, uint32_t MonitorType);
HAL_StatusTypeDef HAL_DCACHE_Monitor_Start(DCACHE_HandleTypeDef *hdcache, uint32_t MonitorType);
HAL_StatusTypeDef HAL_DCACHE_Monitor_Stop(DCACHE_HandleTypeDef *hdcache, uint32_t MonitorType);
/**
  * @}
  */

/** @defgroup DCACHE_Exported_Functions_Group3 State and Error Functions
  * @brief    State and Error Functions
  * @{
  */
HAL_DCACHE_StateTypeDef HAL_DCACHE_GetState(const DCACHE_HandleTypeDef *hdcache);
uint32_t HAL_DCACHE_GetError(const DCACHE_HandleTypeDef *hdcache);
/**
  * @}
  */

/**
  * @}
  */


/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @}
  */

#endif /* DCACHE1 */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_HAL_DCACHE_H */
