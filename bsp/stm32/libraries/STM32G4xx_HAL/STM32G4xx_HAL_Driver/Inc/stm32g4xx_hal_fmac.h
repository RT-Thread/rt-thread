/**
  ******************************************************************************
  * @file    stm32g4xx_hal_fmac.h
  * @author  MCD Application Team
  * @brief   Header for stm32g4xx_hal_fmac.c module
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
#ifndef STM32G4xx_HAL_FMAC_H
#define STM32G4xx_HAL_FMAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @addtogroup FMAC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup FMAC_Exported_Types FMAC Exported Types
  * @{
  */

/**
  * @brief  FMAC HAL State Structure definition
  */
typedef enum
{
  HAL_FMAC_STATE_RESET       = 0x00U,            /*!< FMAC not yet initialized or disabled                           */
  HAL_FMAC_STATE_READY       = 0x20U,            /*!< FMAC initialized and ready for use                             */
  HAL_FMAC_STATE_BUSY        = 0x24U,            /*!< FMAC internal process is ongoing                               */
  HAL_FMAC_STATE_BUSY_RD     = 0x25U,            /*!< FMAC reading configuration is ongoing                          */
  HAL_FMAC_STATE_BUSY_WR     = 0x26U,            /*!< FMAC writing configuration is ongoing                          */
  HAL_FMAC_STATE_TIMEOUT     = 0xA0U,            /*!< FMAC in Timeout state                                          */
  HAL_FMAC_STATE_ERROR       = 0xE0U             /*!< FMAC in Error state                                            */
} HAL_FMAC_StateTypeDef;

/**
  * @brief  FMAC Handle Structure definition
  */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
typedef struct __FMAC_HandleTypeDef
#else
typedef struct
#endif  /* USE_HAL_FMAC_REGISTER_CALLBACKS */
{
  FMAC_TypeDef               *Instance;          /*!< Register base address */

  uint32_t                   FilterParam;        /*!< Filter configuration (operation and parameters).
                                                      Set to 0 if no valid configuration was applied. */

  uint8_t                    InputAccess;       /*!< Access to the input buffer (internal memory area): DMA, IT, Polling, None.
                                                     This parameter can be a value of @ref FMAC_Buffer_Access. */

  uint8_t                    OutputAccess;      /*!< Access to the output buffer (internal memory area): DMA, IT, Polling, None.
                                                     This parameter can be a value of @ref FMAC_Buffer_Access. */

  int16_t                    *pInput;            /*!< Pointer to FMAC input data buffer */

  uint16_t                   InputCurrentSize;   /*!< Number of the input elements already written into FMAC */

  uint16_t                   *pInputSize;        /*!< Number of input elements to write (memory allocated to pInput).
                                                      In case of early interruption of the filter operation, its value will be updated. */

  int16_t                    *pOutput;           /*!< Pointer to FMAC output data buffer */

  uint16_t                   OutputCurrentSize;  /*!< Number of the output elements already read from FMAC */

  uint16_t                   *pOutputSize;       /*!< Number of output elements to read (memory allocated to pOutput).
                                                      In case of early interruption of the filter operation, its value will be updated. */

  DMA_HandleTypeDef          *hdmaIn;            /*!< FMAC peripheral input data DMA handle parameters */

  DMA_HandleTypeDef          *hdmaOut;           /*!< FMAC peripheral output data DMA handle parameters */

  DMA_HandleTypeDef          *hdmaPreload;       /*!< FMAC peripheral preloaded data (X1, X2 and Y) DMA handle parameters */

#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
  void (* ErrorCallback)(struct __FMAC_HandleTypeDef *hfmac);               /*!< FMAC error callback                  */

  void (* HalfGetDataCallback)(struct __FMAC_HandleTypeDef *hfmac);         /*!< FMAC get half data callback          */

  void (* GetDataCallback)(struct __FMAC_HandleTypeDef *hfmac);             /*!< FMAC get data callback               */

  void (* HalfOutputDataReadyCallback)(struct __FMAC_HandleTypeDef *hfmac); /*!< FMAC half output data ready callback */

  void (* OutputDataReadyCallback)(struct __FMAC_HandleTypeDef *hfmac);     /*!< FMAC output data ready callback      */

  void (* FilterConfigCallback)(struct __FMAC_HandleTypeDef *hfmac);        /*!< FMAC filter configuration callback   */

  void (* FilterPreloadCallback)(struct __FMAC_HandleTypeDef *hfmac);       /*!< FMAC filter preload callback         */

  void (* MspInitCallback)(struct __FMAC_HandleTypeDef *hfmac);             /*!< FMAC Msp Init callback               */

  void (* MspDeInitCallback)(struct __FMAC_HandleTypeDef *hfmac);           /*!< FMAC Msp DeInit callback             */

#endif /* (USE_HAL_FMAC_REGISTER_CALLBACKS) */

  HAL_LockTypeDef            Lock;               /*!< FMAC locking object */

  __IO HAL_FMAC_StateTypeDef State;              /*!< FMAC state related to global handle management
                                                      This parameter can be a value of @ref HAL_FMAC_StateTypeDef */

  __IO HAL_FMAC_StateTypeDef RdState;            /*!< FMAC state related to read operations (access to Y buffer)
                                                      This parameter can be a value of @ref HAL_FMAC_StateTypeDef */

  __IO HAL_FMAC_StateTypeDef WrState;            /*!< FMAC state related to write operations (access to X1 buffer)
                                                      This parameter can be a value of @ref HAL_FMAC_StateTypeDef */

  __IO uint32_t              ErrorCode;          /*!< FMAC peripheral error code
                                                      This parameter can be a value of @ref FMAC_Error_Code */

} FMAC_HandleTypeDef;

#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
/**
  * @brief  FMAC Callback ID enumeration definition
  */
typedef enum
{
  HAL_FMAC_ERROR_CB_ID                  = 0x00U, /*!< FMAC error callback ID                  */
  HAL_FMAC_HALF_GET_DATA_CB_ID          = 0x01U, /*!< FMAC get half data callback ID          */
  HAL_FMAC_GET_DATA_CB_ID               = 0x02U, /*!< FMAC get data callback ID               */
  HAL_FMAC_HALF_OUTPUT_DATA_READY_CB_ID = 0x03U, /*!< FMAC half output data ready callback ID */
  HAL_FMAC_OUTPUT_DATA_READY_CB_ID      = 0x04U, /*!< FMAC output data ready callback ID      */
  HAL_FMAC_FILTER_CONFIG_CB_ID          = 0x05U, /*!< FMAC filter configuration callback ID   */
  HAL_FMAC_FILTER_PRELOAD_CB_ID         = 0x06U, /*!< FMAC filter preload callback ID         */

  HAL_FMAC_MSPINIT_CB_ID                = 0x07U, /*!< FMAC MspInit callback ID                */
  HAL_FMAC_MSPDEINIT_CB_ID              = 0x08U, /*!< FMAC MspDeInit callback ID              */
} HAL_FMAC_CallbackIDTypeDef;

/**
  * @brief  HAL FMAC Callback pointer definition
  */
typedef  void (*pFMAC_CallbackTypeDef)(FMAC_HandleTypeDef *hfmac);  /*!< pointer to an FMAC callback function */

#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */

/**
  * @brief  FMAC Filter Configuration Structure definition
  */
typedef struct
{
  uint8_t                    InputBaseAddress;  /*!< Base address of the input buffer (X1) within the internal memory (0x00 to 0xFF).
                                                     Ignored if InputBufferSize is set to 0 (previous configuration kept).
                                                     Note: the buffers can overlap or even coincide exactly. */

  uint8_t                    InputBufferSize;   /*!< Number of 16-bit words allocated to the input buffer (including the optional "headroom").
                                                     0 if a previous configuration should be kept. */

  uint32_t                   InputThreshold;    /*!< Input threshold: the buffer full flag will be set if the number of free spaces
                                                     in the buffer is lower than this threshold.
                                                     This parameter can be a value of @ref FMAC_Data_Buffer_Threshold. */

  uint8_t                    CoeffBaseAddress;  /*!< Base address of the coefficient buffer (X2) within the internal memory (0x00 to 0xFF).
                                                     Ignored if CoeffBufferSize is set to 0 (previous configuration kept).
                                                     Note: the buffers can overlap or even coincide exactly. */

  uint8_t                    CoeffBufferSize;   /*!< Number of 16-bit words allocated to the coefficient buffer.
                                                     0 if a previous configuration should be kept. */

  uint8_t                    OutputBaseAddress; /*!< Base address of the output buffer (Y) within the internal memory (0x00 to 0xFF).
                                                     Ignored if OuputBufferSize is set to 0 (previous configuration kept).
                                                     Note: the buffers can overlap or even coincide exactly. */

  uint8_t                    OutputBufferSize;  /*!< Number of 16-bit words allocated to the output buffer (including the optional "headroom").
                                                     0 if a previous configuration should be kept. */

  uint32_t                   OutputThreshold;   /*!< Output threshold: the buffer empty flag will be set if the number of unread values
                                                     in the buffer is lower than this threshold.
                                                     This parameter can be a value of @ref FMAC_Data_Buffer_Threshold. */

  int16_t                    *pCoeffA;          /*!< [IIR only] Initialization of the coefficient vector A.
                                                     If not needed, it should be set to NULL. */

  uint8_t                    CoeffASize;        /*!< Size of the coefficient vector A. */

  int16_t                    *pCoeffB;          /*!< Initialization of the coefficient vector B.
                                                     If not needed (re-use of a previously loaded buffer), it should be set to NULL. */

  uint8_t                    CoeffBSize;        /*!< Size of the coefficient vector B. */

  uint8_t                    InputAccess;       /*!< Access to the input buffer (internal memory area): DMA, IT, Polling, None.
                                                     This parameter can be a value of @ref FMAC_Buffer_Access. */

  uint8_t                    OutputAccess;      /*!< Access to the output buffer (internal memory area): DMA, IT, Polling, None.
                                                     This parameter can be a value of @ref FMAC_Buffer_Access. */

  uint32_t                   Clip;              /*!< Enable or disable the clipping feature. If the q1.15 range is exceeded, wrapping
                                                     is done when the clipping feature is disabled and saturation is done when the
                                                     clipping feature is enabled.
                                                     This parameter can be a value of @ref FMAC_Clip_State. */

  uint32_t                   Filter;            /*!< Filter type.
                                                     This parameter can be a value of @ref FMAC_Functions (filter related values). */

  uint8_t                    P;                 /*!< Parameter P (vector length, number of filter taps, etc.). */

  uint8_t                    Q;                 /*!< Parameter Q (vector length, etc.). Ignored if not needed. */

  uint8_t                    R;                 /*!< Parameter R (gain, etc.). Ignored if not needed. */

} FMAC_FilterConfigTypeDef;

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/


/** @defgroup FMAC_Exported_Constants FMAC Exported Constants
  * @{
  */

/** @defgroup FMAC_Error_Code FMAC Error code
  * @{
  */
#define HAL_FMAC_ERROR_NONE                0x00000000U /*!< No error               */
#define HAL_FMAC_ERROR_SAT                 0x00000001U /*!< Saturation error       */
#define HAL_FMAC_ERROR_UNFL                0x00000002U /*!< Underflow error        */
#define HAL_FMAC_ERROR_OVFL                0x00000004U /*!< Overflow error         */
#define HAL_FMAC_ERROR_DMA                 0x00000008U /*!< DMA error              */
#define HAL_FMAC_ERROR_RESET               0x00000010U /*!< Reset error            */
#define HAL_FMAC_ERROR_PARAM               0x00000020U /*!< Parameter error        */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
#define HAL_FMAC_ERROR_INVALID_CALLBACK    0x00000040U /*!< Invalid Callback error */
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
#define HAL_FMAC_ERROR_TIMEOUT             0x00000080U /*!< Timeout error          */

/**
  * @}
  */

/** @defgroup FMAC_Functions FMAC Functions
  * @{
  */
#define FMAC_FUNC_LOAD_X1                  (FMAC_PARAM_FUNC_0)                                        /*!< Load X1 buffer                            */
#define FMAC_FUNC_LOAD_X2                  (FMAC_PARAM_FUNC_1)                                        /*!< Load X2 buffer                            */
#define FMAC_FUNC_LOAD_Y                   (FMAC_PARAM_FUNC_1 | FMAC_PARAM_FUNC_0)                    /*!< Load Y buffer                             */
#define FMAC_FUNC_CONVO_FIR                (FMAC_PARAM_FUNC_3)                                        /*!< Convolution (FIR filter)                  */
#define FMAC_FUNC_IIR_DIRECT_FORM_1        (FMAC_PARAM_FUNC_3 | FMAC_PARAM_FUNC_0)                    /*!< IIR filter (direct form 1)                */
/**
  * @}
  */

/** @defgroup FMAC_Data_Buffer_Threshold FMAC Data Buffer Threshold
  * @{
  * @note     This parameter sets a watermark for buffer full (input) or buffer empty (output).
  */
#define FMAC_THRESHOLD_1                   0x00000000U    /*!< Input: Buffer full flag set if the number of free spaces in the buffer is less than 1.
                                                                Output: Buffer empty flag set if the number of unread values in the buffer is less than 1. */
#define FMAC_THRESHOLD_2                   0x01000000U    /*!< Input: Buffer full flag set if the number of free spaces in the buffer is less than 2.
                                                                Output: Buffer empty flag set if the number of unread values in the buffer is less than 2. */
#define FMAC_THRESHOLD_4                   0x02000000U    /*!< Input: Buffer full flag set if the number of free spaces in the buffer is less than 4.
                                                                Output: Buffer empty flag set if the number of unread values in the buffer is less than 4. */
#define FMAC_THRESHOLD_8                   0x03000000U    /*!< Input: Buffer full flag set if the number of free spaces in the buffer is less than 8.
                                                                Output: Buffer empty flag set if the number of unread values in the buffer is less than 8. */
#define FMAC_THRESHOLD_NO_VALUE            0xFFFFFFFFU    /*!< The configured threshold value shouldn't be changed */
/**
  * @}
  */

/** @defgroup FMAC_Buffer_Access FMAC Buffer Access
  * @{
  */
#define FMAC_BUFFER_ACCESS_NONE            0x00U           /*!< Buffer handled by an external IP (ADC for instance) */
#define FMAC_BUFFER_ACCESS_DMA             0x01U           /*!< Buffer accessed through DMA */
#define FMAC_BUFFER_ACCESS_POLLING         0x02U           /*!< Buffer accessed through polling */
#define FMAC_BUFFER_ACCESS_IT              0x03U           /*!< Buffer accessed through interruptions */
/**
  * @}
  */

/** @defgroup FMAC_Clip_State FMAC Clip State
  * @{
  */
#define FMAC_CLIP_DISABLED                 0x00000000U     /*!< Clipping disabled */
#define FMAC_CLIP_ENABLED                  FMAC_CR_CLIPEN  /*!< Clipping enabled */
/**
  * @}
  */

/** @defgroup FMAC_Flags  FMAC status flags
  * @{
  */
#define FMAC_FLAG_YEMPTY                   FMAC_SR_YEMPTY  /*!< Y Buffer Empty Flag */
#define FMAC_FLAG_X1FULL                   FMAC_SR_X1FULL  /*!< X1 Buffer Full Flag */
#define FMAC_FLAG_OVFL                     FMAC_SR_OVFL    /*!< Overflow Error Flag */
#define FMAC_FLAG_UNFL                     FMAC_SR_UNFL    /*!< Underflow Error Flag */
#define FMAC_FLAG_SAT                      FMAC_SR_SAT     /*!< Saturation Error Flag (this helps in debugging a filter) */
/**
  * @}
  */

/** @defgroup FMAC_Interrupts_Enable FMAC Interrupts Enable bit
  * @{
  */
#define FMAC_IT_RIEN                       FMAC_CR_RIEN    /*!< Read Interrupt Enable */
#define FMAC_IT_WIEN                       FMAC_CR_WIEN    /*!< Write Interrupt Enable */
#define FMAC_IT_OVFLIEN                    FMAC_CR_OVFLIEN /*!< Overflow Error Interrupt Enable */
#define FMAC_IT_UNFLIEN                    FMAC_CR_UNFLIEN /*!< Underflow Error Interrupt Enable */
#define FMAC_IT_SATIEN                     FMAC_CR_SATIEN  /*!< Saturation Error Interrupt Enable (this helps in debugging a filter) */
/**
  * @}
  */

/**
  * @}
  */


/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/** @defgroup FMAC_Exported_Macros FMAC Exported Macros
  * @{
  */

/** @brief  Reset FMAC handle state.
  * @param  __HANDLE__ FMAC handle.
  * @retval None
  */
#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
#define __HAL_FMAC_RESET_HANDLE_STATE(__HANDLE__) do{                                           \
                                                      (__HANDLE__)->State = HAL_FMAC_STATE_RESET; \
                                                      (__HANDLE__)->MspInitCallback = NULL;       \
                                                      (__HANDLE__)->MspDeInitCallback = NULL;     \
                                                    } while(0U)
#else
#define __HAL_FMAC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_FMAC_STATE_RESET)
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */

/**
  * @brief  Enable the specified FMAC interrupt
  * @param  __HANDLE__ FMAC handle.
  * @param  __INTERRUPT__ FMAC Interrupt.
  *         This parameter can be any combination of the following values:
  *            @arg @ref FMAC_IT_RIEN    Read interrupt enable
  *            @arg @ref FMAC_IT_WIEN    Write interrupt enable
  *            @arg @ref FMAC_IT_OVFLIEN Overflow error interrupt enable
  *            @arg @ref FMAC_IT_UNFLIEN Underflow error interrupt enable
  *            @arg @ref FMAC_IT_SATIEN  Saturation error interrupt enable (this helps in debugging a filter)
  * @retval None
  */
#define __HAL_FMAC_ENABLE_IT(__HANDLE__, __INTERRUPT__) \
  (((__HANDLE__)->Instance->CR) |= (__INTERRUPT__))

/**
  * @brief  Disable the FMAC interrupt
  * @param  __HANDLE__ FMAC handle.
  * @param  __INTERRUPT__ FMAC Interrupt.
  *         This parameter can be any combination of the following values:
  *            @arg @ref FMAC_IT_RIEN    Read interrupt enable
  *            @arg @ref FMAC_IT_WIEN    Write interrupt enable
  *            @arg @ref FMAC_IT_OVFLIEN Overflow error interrupt enable
  *            @arg @ref FMAC_IT_UNFLIEN Underflow error interrupt enable
  *            @arg @ref FMAC_IT_SATIEN  Saturation error interrupt enable (this helps in debugging a filter)
  * @retval None
  */
#define __HAL_FMAC_DISABLE_IT(__HANDLE__, __INTERRUPT__) \
  (((__HANDLE__)->Instance->CR) &= ~(__INTERRUPT__))

/** @brief  Check whether the specified FMAC interrupt occurred or not.
  * @param  __HANDLE__ FMAC handle.
  * @param  __INTERRUPT__ FMAC interrupt to check.
  *         This parameter can be any combination of the following values:
  *            @arg @ref FMAC_FLAG_YEMPTY Y Buffer Empty Flag
  *            @arg @ref FMAC_FLAG_X1FULL X1 Buffer Full Flag
  *            @arg @ref FMAC_FLAG_OVFL   Overflow Error Flag
  *            @arg @ref FMAC_FLAG_UNFL   Underflow Error Flag
  *            @arg @ref FMAC_FLAG_SAT    Saturation Error Flag
  * @retval SET (interrupt occurred) or RESET (interrupt did not occurred)
  */
#define __HAL_FMAC_GET_IT(__HANDLE__, __INTERRUPT__) \
  (((__HANDLE__)->Instance->SR) &= ~(__INTERRUPT__))

/** @brief  Clear specified FMAC interrupt status. Dummy macro as the
            interrupt status flags are read-only.
  * @param  __HANDLE__ FMAC handle.
  * @param  __INTERRUPT__ FMAC interrupt to clear.
  * @retval None
  */
#define __HAL_FMAC_CLEAR_IT(__HANDLE__, __INTERRUPT__)   /* Dummy macro */

/** @brief  Check whether the specified FMAC status flag is set or not.
  * @param  __HANDLE__ FMAC handle.
  * @param  __FLAG__ FMAC flag to check.
  *         This parameter can be any combination of the following values:
  *            @arg @ref FMAC_FLAG_YEMPTY Y Buffer Empty Flag
  *            @arg @ref FMAC_FLAG_X1FULL X1 Buffer Full Flag
  *            @arg @ref FMAC_FLAG_OVFL   Overflow Error Flag
  *            @arg @ref FMAC_FLAG_UNFL   Underflow Error Flag
  *            @arg @ref FMAC_FLAG_SAT    Saturation error Flag
  * @retval SET (flag is set) or RESET (flag is reset)
  */
#define __HAL_FMAC_GET_FLAG(__HANDLE__, __FLAG__) \
  ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))

/** @brief  Clear specified FMAC status flag. Dummy macro as no
            flag can be cleared.
  * @param  __HANDLE__ FMAC handle.
  * @param  __FLAG__ FMAC flag to clear.
  * @retval None
  */
#define __HAL_FMAC_CLEAR_FLAG(__HANDLE__, __FLAG__)     /* Dummy macro */

/** @brief  Check whether the specified FMAC interrupt is enabled or not.
  * @param  __HANDLE__ FMAC handle.
  * @param  __INTERRUPT__ FMAC interrupt to check.
  *         This parameter can be one of the following values:
  *            @arg @ref FMAC_IT_RIEN    Read interrupt enable
  *            @arg @ref FMAC_IT_WIEN    Write interrupt enable
  *            @arg @ref FMAC_IT_OVFLIEN Overflow error interrupt enable
  *            @arg @ref FMAC_IT_UNFLIEN Underflow error interrupt enable
  *            @arg @ref FMAC_IT_SATIEN  Saturation error interrupt enable (this helps in debugging a filter)
  * @retval FlagStatus
  */
#define __HAL_FMAC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__) \
  (((__HANDLE__)->Instance->CR) & (__INTERRUPT__))

/**
  * @}
  */

/** @addtogroup  FMAC_Private_Macros
  * @{
  */

/**
  * @brief  Verify the FMAC function.
  * @param  __FUNCTION__ ID of the function.
  * @retval SET (__FUNCTION__ is a valid value) or RESET (__FUNCTION__ is invalid)
  */
#define IS_FMAC_FUNCTION(__FUNCTION__) (((__FUNCTION__) == FMAC_FUNC_LOAD_X1)                         || \
                                        ((__FUNCTION__) == FMAC_FUNC_LOAD_X2)                         || \
                                        ((__FUNCTION__) == FMAC_FUNC_LOAD_Y)                          || \
                                        ((__FUNCTION__) == FMAC_FUNC_CONVO_FIR)                       || \
                                        ((__FUNCTION__) == FMAC_FUNC_IIR_DIRECT_FORM_1))

/**
  * @brief  Verify the FMAC load function used for input data, output data or coefficients.
  * @param  __FUNCTION__ ID of the load function.
  * @retval SET (__FUNCTION__ is a valid value) or RESET (__FUNCTION__ is invalid)
  */
#define IS_FMAC_LOAD_FUNCTION(__FUNCTION__) (((__FUNCTION__) == FMAC_FUNC_LOAD_X1)                    || \
                                             ((__FUNCTION__) == FMAC_FUNC_LOAD_X2)                    || \
                                             ((__FUNCTION__) == FMAC_FUNC_LOAD_Y))

/**
  * @brief  Verify the FMAC load function used with N values as input or output data.
  * @param  __FUNCTION__ ID of the load function.
  * @retval SET (__FUNCTION__ is a valid value) or RESET (__FUNCTION__ is invalid)
  */
#define IS_FMAC_N_LOAD_FUNCTION(__FUNCTION__) (((__FUNCTION__) == FMAC_FUNC_LOAD_X1)                  || \
                                               ((__FUNCTION__) == FMAC_FUNC_LOAD_Y))

/**
  * @brief  Verify the FMAC load function used with N + M values as coefficients.
  * @param  __FUNCTION__ ID of the load function.
  * @retval SET (__FUNCTION__ is a valid value) or RESET (__FUNCTION__ is invalid)
  */
#define IS_FMAC_N_M_LOAD_FUNCTION(__FUNCTION__) ((__FUNCTION__) == FMAC_FUNC_LOAD_X2)

/**
  * @brief  Verify the FMAC filter function.
  * @param  __FUNCTION__ ID of the filter function.
  * @retval SET (__FUNCTION__ is a valid value) or RESET (__FUNCTION__ is invalid)
  */
#define IS_FMAC_FILTER_FUNCTION(__FUNCTION__) (((__FUNCTION__) == FMAC_FUNC_CONVO_FIR)                || \
                                               ((__FUNCTION__) == FMAC_FUNC_IIR_DIRECT_FORM_1))


/**
  * @brief  Verify the FMAC threshold.
  * @param  __THRESHOLD__ Value of the threshold.
  * @retval SET (__THRESHOLD__ is a valid value) or RESET (__THRESHOLD__ is invalid)
  */
#define IS_FMAC_THRESHOLD(__THRESHOLD__) (((__THRESHOLD__) == FMAC_THRESHOLD_1)                       || \
                                          ((__THRESHOLD__) == FMAC_THRESHOLD_2)                       || \
                                          ((__THRESHOLD__) == FMAC_THRESHOLD_4)                       || \
                                          ((__THRESHOLD__) == FMAC_THRESHOLD_NO_VALUE)                || \
                                          ((__THRESHOLD__) == FMAC_THRESHOLD_8))

/**
  * @brief  Verify the FMAC filter parameter P.
  * @param  __P__ Value of the filter parameter P.
  * @param  __FUNCTION__ ID of the filter function.
  * @retval SET (__P__ is a valid value) or RESET (__P__ is invalid)
  */
#define IS_FMAC_PARAM_P(__FUNCTION__, __P__) ( (((__FUNCTION__) == FMAC_FUNC_CONVO_FIR)               && \
                                                (((__P__) >= 2U) && ((__P__) <= 127U)))               || \
                                               (((__FUNCTION__) == FMAC_FUNC_IIR_DIRECT_FORM_1)       && \
                                                (((__P__) >= 2U) && ((__P__) <= 64U))) )

/**
  * @brief  Verify the FMAC filter parameter Q.
  * @param  __Q__ Value of the filter parameter Q.
  * @param  __FUNCTION__ ID of the filter function.
  * @retval SET (__Q__ is a valid value) or RESET (__Q__ is invalid)
  */
#define IS_FMAC_PARAM_Q(__FUNCTION__, __Q__) ( ((__FUNCTION__) == FMAC_FUNC_CONVO_FIR)                || \
                                               (((__FUNCTION__) == FMAC_FUNC_IIR_DIRECT_FORM_1)       && \
                                                (((__Q__) >= 1U) && ((__Q__) <= 63U))) )

/**
  * @brief  Verify the FMAC filter parameter R.
  * @param  __R__ Value of the filter parameter.
  * @param  __FUNCTION__ ID of the filter function.
  * @retval SET (__R__ is a valid value) or RESET (__R__ is invalid)
  */
#define IS_FMAC_PARAM_R(__FUNCTION__, __R__) ( (((__FUNCTION__) == FMAC_FUNC_CONVO_FIR)               || \
                                                ((__FUNCTION__) == FMAC_FUNC_IIR_DIRECT_FORM_1))      && \
                                               ((__R__) <= 7U))

/**
  * @brief  Verify the FMAC buffer access.
  * @param  __BUFFER_ACCESS__ Type of access.
  * @retval SET (__BUFFER_ACCESS__ is a valid value) or RESET (__BUFFER_ACCESS__ is invalid)
  */
#define IS_FMAC_BUFFER_ACCESS(__BUFFER_ACCESS__) (((__BUFFER_ACCESS__) == FMAC_BUFFER_ACCESS_NONE)    || \
                                                  ((__BUFFER_ACCESS__) == FMAC_BUFFER_ACCESS_DMA)     || \
                                                  ((__BUFFER_ACCESS__) == FMAC_BUFFER_ACCESS_POLLING) || \
                                                  ((__BUFFER_ACCESS__) == FMAC_BUFFER_ACCESS_IT))

/**
  * @brief  Verify the FMAC clip feature.
  * @param  __CLIP_STATE__ Clip state.
  * @retval SET (__CLIP_STATE__ is a valid value) or RESET (__CLIP_STATE__ is invalid)
  */
#define IS_FMAC_CLIP_STATE(__CLIP_STATE__) (((__CLIP_STATE__) == FMAC_CLIP_DISABLED)                  || \
                                            ((__CLIP_STATE__) == FMAC_CLIP_ENABLED))

/**
  * @brief  Check whether the threshold is applicable.
  * @param  __SIZE__ Size of the matching buffer.
  * @param  __WM__ Watermark value.
  * @param  __ACCESS__ Access to the buffer (polling, it, dma, none).
  * @retval THRESHOLD
  */
#define IS_FMAC_THRESHOLD_APPLICABLE(__SIZE__, __WM__, __ACCESS__) (( (__SIZE__) >= (((__WM__) == FMAC_THRESHOLD_1)? 1U: \
                                                                      ((__WM__) == FMAC_THRESHOLD_2)? 2U: \
                                                                      ((__WM__) == FMAC_THRESHOLD_4)? 4U:8U))&& \
                                                                    ((((__ACCESS__) == FMAC_BUFFER_ACCESS_DMA)&&((__WM__) == FMAC_THRESHOLD_1))|| \
                                                                     ((__ACCESS__ )!= FMAC_BUFFER_ACCESS_DMA)))

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */
/** @addtogroup FMAC_Exported_Functions
  * @{
  */

/** @addtogroup FMAC_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions  ****************************/
HAL_StatusTypeDef HAL_FMAC_Init(FMAC_HandleTypeDef *hfmac);
HAL_StatusTypeDef HAL_FMAC_DeInit(FMAC_HandleTypeDef *hfmac);
void HAL_FMAC_MspInit(FMAC_HandleTypeDef *hfmac);
void HAL_FMAC_MspDeInit(FMAC_HandleTypeDef *hfmac);

#if (USE_HAL_FMAC_REGISTER_CALLBACKS == 1)
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_FMAC_RegisterCallback(FMAC_HandleTypeDef *hfmac, HAL_FMAC_CallbackIDTypeDef CallbackID,
                                            pFMAC_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_FMAC_UnRegisterCallback(FMAC_HandleTypeDef *hfmac, HAL_FMAC_CallbackIDTypeDef CallbackID);
#endif /* USE_HAL_FMAC_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_FMAC_FilterConfig(FMAC_HandleTypeDef *hfmac, FMAC_FilterConfigTypeDef *pConfig);
HAL_StatusTypeDef HAL_FMAC_FilterConfig_DMA(FMAC_HandleTypeDef *hfmac, FMAC_FilterConfigTypeDef *pConfig);
HAL_StatusTypeDef HAL_FMAC_FilterPreload(FMAC_HandleTypeDef *hfmac, int16_t *pInput, uint8_t InputSize,
                                         int16_t *pOutput, uint8_t OutputSize);
HAL_StatusTypeDef HAL_FMAC_FilterPreload_DMA(FMAC_HandleTypeDef *hfmac, int16_t *pInput, uint8_t InputSize,
                                             int16_t *pOutput, uint8_t OutputSize);
HAL_StatusTypeDef HAL_FMAC_FilterStart(FMAC_HandleTypeDef *hfmac, int16_t *pOutput, uint16_t *pOutputSize);
HAL_StatusTypeDef HAL_FMAC_AppendFilterData(FMAC_HandleTypeDef *hfmac, int16_t *pInput, uint16_t *pInputSize);
HAL_StatusTypeDef HAL_FMAC_ConfigFilterOutputBuffer(FMAC_HandleTypeDef *hfmac, int16_t *pOutput, uint16_t *pOutputSize);
HAL_StatusTypeDef HAL_FMAC_PollFilterData(FMAC_HandleTypeDef *hfmac, uint32_t Timeout);
HAL_StatusTypeDef HAL_FMAC_FilterStop(FMAC_HandleTypeDef  *hfmac);
/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group3
  * @{
  */
/* Callback functions *********************************************************/
void HAL_FMAC_ErrorCallback(FMAC_HandleTypeDef *hfmac);
void HAL_FMAC_HalfGetDataCallback(FMAC_HandleTypeDef *hfmac);
void HAL_FMAC_GetDataCallback(FMAC_HandleTypeDef *hfmac);
void HAL_FMAC_HalfOutputDataReadyCallback(FMAC_HandleTypeDef *hfmac);
void HAL_FMAC_OutputDataReadyCallback(FMAC_HandleTypeDef *hfmac);
void HAL_FMAC_FilterConfigCallback(FMAC_HandleTypeDef *hfmac);
void HAL_FMAC_FilterPreloadCallback(FMAC_HandleTypeDef *hfmac);
/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group4
  * @{
  */
/* IRQ handler management *****************************************************/
void HAL_FMAC_IRQHandler(FMAC_HandleTypeDef *hfmac);
/**
  * @}
  */

/** @addtogroup FMAC_Exported_Functions_Group5
  * @{
  */
/* Peripheral State functions *************************************************/
HAL_FMAC_StateTypeDef HAL_FMAC_GetState(FMAC_HandleTypeDef *hfmac);
uint32_t HAL_FMAC_GetError(FMAC_HandleTypeDef *hfmac);
/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G4xx_HAL_FMAC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
