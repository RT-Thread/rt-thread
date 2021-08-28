/**
  ******************************************************************************
  * @file    stm32g4xx_hal_cordic.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the CORDIC firmware
  *          library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
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
#ifndef STM32G4xx_HAL_CORDIC_H
#define STM32G4xx_HAL_CORDIC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @addtogroup CORDIC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Types CORDIC Exported Types
  * @{
  */

/**
  * @brief  CORDIC HAL State Structure definition
  */
typedef enum
{
  HAL_CORDIC_STATE_RESET     = 0x00U,  /*!< CORDIC not yet initialized or disabled */
  HAL_CORDIC_STATE_READY     = 0x01U,  /*!< CORDIC initialized and ready for use   */
  HAL_CORDIC_STATE_BUSY      = 0x02U,  /*!< CORDIC internal process is ongoing     */
  HAL_CORDIC_STATE_ERROR     = 0x03U   /*!< CORDIC error state                     */
} HAL_CORDIC_StateTypeDef;

/**
  * @brief  CORDIC Handle Structure definition
  */
#if USE_HAL_CORDIC_REGISTER_CALLBACKS == 1
typedef struct __CORDIC_HandleTypeDef
#else
typedef struct
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
{
  CORDIC_TypeDef                *Instance;   /*!< Register base address */

  int32_t                       *pInBuff;    /*!< Pointer to CORDIC input data buffer */

  int32_t                       *pOutBuff;   /*!< Pointer to CORDIC output data buffer */

  uint32_t                      NbCalcToOrder; /*!< Remaining number of calculation to order */

  uint32_t                      NbCalcToGet; /*!< Remaining number of calculation result to get */

  uint32_t                      DMADirection; /*!< Direction of CORDIC DMA transfers */

  DMA_HandleTypeDef             *hdmaIn;     /*!< CORDIC peripheral input data DMA handle parameters */

  DMA_HandleTypeDef             *hdmaOut;    /*!< CORDIC peripheral output data DMA handle parameters */

  HAL_LockTypeDef               Lock;        /*!< CORDIC locking object */

  __IO HAL_CORDIC_StateTypeDef  State;       /*!< CORDIC state */

  __IO uint32_t                 ErrorCode;   /*!< CORDIC peripheral error code
                                                  This parameter can be a value of @ref CORDIC_Error_Code */

#if USE_HAL_CORDIC_REGISTER_CALLBACKS == 1
  void (* ErrorCallback)(struct __CORDIC_HandleTypeDef *hcordic);          /*!< CORDIC error callback */
  void (* CalculateCpltCallback)(struct __CORDIC_HandleTypeDef *hcordic);  /*!< CORDIC calculate complete callback */

  void (* MspInitCallback)(struct __CORDIC_HandleTypeDef *hcordic);        /*!< CORDIC Msp Init callback */
  void (* MspDeInitCallback)(struct __CORDIC_HandleTypeDef *hcordic);      /*!< CORDIC Msp DeInit callback */

#endif /* (USE_HAL_CORDIC_REGISTER_CALLBACKS) */

} CORDIC_HandleTypeDef;

/**
  * @brief  CORDIC Config Structure definition
  */
typedef struct
{
  uint32_t   Function;     /*!< Function
                                This parameter can be a value of @ref CORDIC_Function */

  uint32_t   Scale;        /*!< Scaling factor
                                This parameter can be a value of @ref CORDIC_Scale */

  uint32_t   InSize;       /*!< Width of input data
                                This parameter can be a value of @ref CORDIC_In_Size */

  uint32_t   OutSize;      /*!< Width of output data
                                This parameter can be a value of @ref CORDIC_Out_Size */

  uint32_t   NbWrite;      /*!< Number of 32-bit write expected for one calculation
                                This parameter can be a value of @ref CORDIC_Nb_Write */

  uint32_t   NbRead;       /*!< Number of 32-bit read expected after one calculation
                                This parameter can be a value of @ref CORDIC_Nb_Read */

  uint32_t   Precision;    /*!< Number of cycles for calculation
                                This parameter can be a value of @ref CORDIC_Precision_In_Cycles_Number */

} CORDIC_ConfigTypeDef;

#if USE_HAL_CORDIC_REGISTER_CALLBACKS == 1
/**
  * @brief  HAL CORDIC Callback ID enumeration definition
  */
typedef enum
{
  HAL_CORDIC_ERROR_CB_ID             = 0x00U,    /*!< CORDIC error callback ID */
  HAL_CORDIC_CALCULATE_CPLT_CB_ID    = 0x01U,    /*!< CORDIC calculate complete callback ID */

  HAL_CORDIC_MSPINIT_CB_ID           = 0x02U,    /*!< CORDIC MspInit callback ID */
  HAL_CORDIC_MSPDEINIT_CB_ID         = 0x03U,    /*!< CORDIC MspDeInit callback ID */

} HAL_CORDIC_CallbackIDTypeDef;

/**
  * @brief  HAL CORDIC Callback pointer definition
  */
typedef  void (*pCORDIC_CallbackTypeDef)(CORDIC_HandleTypeDef *hcordic);  /*!< pointer to a CORDIC callback function */

#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Constants CORDIC Exported Constants
  * @{
  */

/** @defgroup CORDIC_Error_Code CORDIC Error code
  * @{
  */
#define HAL_CORDIC_ERROR_NONE              ((uint32_t)0x00000000U)   /*!< No error                */
#define HAL_CORDIC_ERROR_PARAM             ((uint32_t)0x00000001U)   /*!< Wrong parameter error   */
#define HAL_CORDIC_ERROR_NOT_READY         ((uint32_t)0x00000002U)   /*!< Peripheral not ready    */
#define HAL_CORDIC_ERROR_TIMEOUT           ((uint32_t)0x00000004U)   /*!< Timeout error           */
#define HAL_CORDIC_ERROR_DMA               ((uint32_t)0x00000008U)   /*!< DMA error               */
#if USE_HAL_CORDIC_REGISTER_CALLBACKS == 1
#define HAL_CORDIC_ERROR_INVALID_CALLBACK  ((uint32_t)0x00000010U)   /*!< Invalid Callback error  */
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
/**
  * @}
  */

/** @defgroup CORDIC_Function CORDIC Function
  * @{
  */
#define CORDIC_FUNCTION_COSINE      (0x00000000U)                                                          /*!< Cosine */
#define CORDIC_FUNCTION_SINE        ((uint32_t)(CORDIC_CSR_FUNC_0))                                        /*!< Sine */
#define CORDIC_FUNCTION_PHASE       ((uint32_t)(CORDIC_CSR_FUNC_1))                                        /*!< Phase */
#define CORDIC_FUNCTION_MODULUS     ((uint32_t)(CORDIC_CSR_FUNC_1 | CORDIC_CSR_FUNC_0))                    /*!< Modulus */
#define CORDIC_FUNCTION_ARCTANGENT  ((uint32_t)(CORDIC_CSR_FUNC_2))                                        /*!< Arctangent */
#define CORDIC_FUNCTION_HCOSINE     ((uint32_t)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_0))                    /*!< Hyperbolic Cosine */
#define CORDIC_FUNCTION_HSINE       ((uint32_t)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_1))                    /*!< Hyperbolic Sine */
#define CORDIC_FUNCTION_HARCTANGENT ((uint32_t)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_1 | CORDIC_CSR_FUNC_0))/*!< Hyperbolic Arctangent */
#define CORDIC_FUNCTION_NATURALLOG  ((uint32_t)(CORDIC_CSR_FUNC_3))                                        /*!< Natural Logarithm */
#define CORDIC_FUNCTION_SQUAREROOT  ((uint32_t)(CORDIC_CSR_FUNC_3 | CORDIC_CSR_FUNC_0))                    /*!< Square Root */
/**
  * @}
  */

/** @defgroup CORDIC_Precision_In_Cycles_Number CORDIC Precision in Cycles Number
  * @{
  */
/* Note: 1 cycle corresponds to 4 algorithm iterations */
#define CORDIC_PRECISION_1CYCLE     ((uint32_t)(CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_2CYCLES    ((uint32_t)(CORDIC_CSR_PRECISION_1))
#define CORDIC_PRECISION_3CYCLES    ((uint32_t)(CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_4CYCLES    ((uint32_t)(CORDIC_CSR_PRECISION_2))
#define CORDIC_PRECISION_5CYCLES    ((uint32_t)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_6CYCLES    ((uint32_t)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1))
#define CORDIC_PRECISION_7CYCLES    ((uint32_t)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_8CYCLES    ((uint32_t)(CORDIC_CSR_PRECISION_3))
#define CORDIC_PRECISION_9CYCLES    ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_10CYCLES   ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_1))
#define CORDIC_PRECISION_11CYCLES   ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_12CYCLES   ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2))
#define CORDIC_PRECISION_13CYCLES   ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_0))
#define CORDIC_PRECISION_14CYCLES   ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1))
#define CORDIC_PRECISION_15CYCLES   ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
/**
  * @}
  */

/** @defgroup CORDIC_Scale CORDIC Scaling factor
  * @{
  */
/* Scale factor value 'n' implies that the input data have been multiplied
   by a factor 2exp(-n), and/or the output data need to be multiplied by 2exp(n). */
#define CORDIC_SCALE_0              (0x00000000U)
#define CORDIC_SCALE_1              ((uint32_t)(CORDIC_CSR_SCALE_0))
#define CORDIC_SCALE_2              ((uint32_t)(CORDIC_CSR_SCALE_1))
#define CORDIC_SCALE_3              ((uint32_t)(CORDIC_CSR_SCALE_1 | CORDIC_CSR_SCALE_0))
#define CORDIC_SCALE_4              ((uint32_t)(CORDIC_CSR_SCALE_2))
#define CORDIC_SCALE_5              ((uint32_t)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_0))
#define CORDIC_SCALE_6              ((uint32_t)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_1))
#define CORDIC_SCALE_7              ((uint32_t)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_1 | CORDIC_CSR_SCALE_0))
/**
  * @}
  */

/** @defgroup CORDIC_Interrupts_Enable CORDIC Interrupts Enable bit
  * @{
  */
#define CORDIC_IT_IEN              CORDIC_CSR_IEN            /*!< Result ready interrupt enable */
/**
  * @}
  */

/** @defgroup CORDIC_DMAR DMA Read Request Enable bit
  * @{
  */
#define CORDIC_DMA_REN             CORDIC_CSR_DMAREN         /*!< DMA Read requests enable */
/**
  * @}
  */

/** @defgroup CORDIC_DMAW DMA Write Request Enable bit
  * @{
  */
#define CORDIC_DMA_WEN             CORDIC_CSR_DMAWEN         /*!< DMA Write channel enable */
/**
  * @}
  */

/** @defgroup CORDIC_Nb_Write CORDIC Number of 32-bit write required for one calculation
  * @{
  */
#define CORDIC_NBWRITE_1           (0x00000000U)             /*!< One 32-bits write containing either only one
                                                                  32-bit data input (Q1.31 format), or two 16-bit
                                                                  data input (Q1.15 format) packed in one 32 bits Data */
#define CORDIC_NBWRITE_2           CORDIC_CSR_NARGS          /*!< Two 32-bit write containing two 32-bits data input
                                                                  (Q1.31 format) */
/**
  * @}
  */

/** @defgroup CORDIC_Nb_Read CORDIC Number of 32-bit read required after one calculation
  * @{
  */
#define CORDIC_NBREAD_1            (0x00000000U)             /*!< One 32-bits read containing either only one
                                                                  32-bit data ouput (Q1.31 format), or two 16-bit
                                                                  data output (Q1.15 format) packed in one 32 bits Data */
#define CORDIC_NBREAD_2            CORDIC_CSR_NRES           /*!< Two 32-bit Data containing two 32-bits data output
                                                                  (Q1.31 format) */
/**
  * @}
  */

/** @defgroup CORDIC_In_Size CORDIC input data size
  * @{
  */
#define CORDIC_INSIZE_32BITS       (0x00000000U)             /*!< 32 bits input data size (Q1.31 format) */
#define CORDIC_INSIZE_16BITS       CORDIC_CSR_ARGSIZE        /*!< 16 bits input data size (Q1.15 format) */
/**
  * @}
  */

/** @defgroup CORDIC_Out_Size CORDIC Results Size
  * @{
  */
#define CORDIC_OUTSIZE_32BITS      (0x00000000U)             /*!< 32 bits output data size (Q1.31 format) */
#define CORDIC_OUTSIZE_16BITS      CORDIC_CSR_RESSIZE        /*!< 16 bits output data size (Q1.15 format) */
/**
  * @}
  */

/** @defgroup CORDIC_Flags  CORDIC status flags
  * @{
  */
#define CORDIC_FLAG_RRDY           CORDIC_CSR_RRDY           /*!< Result Ready Flag */
/**
  * @}
  */

/** @defgroup CORDIC_DMA_Direction CORDIC DMA direction
  * @{
  */
#define CORDIC_DMA_DIR_NONE        ((uint32_t)0x00000000U)   /*!< DMA direction : none */
#define CORDIC_DMA_DIR_IN          ((uint32_t)0x00000001U)   /*!< DMA direction : Input of CORDIC */
#define CORDIC_DMA_DIR_OUT         ((uint32_t)0x00000002U)   /*!< DMA direction : Output of CORDIC */
#define CORDIC_DMA_DIR_IN_OUT      ((uint32_t)0x00000003U)   /*!< DMA direction : Input and Output of CORDIC */
/**
  * @}
  */

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/
/** @defgroup CORDIC_Exported_Macros CORDIC Exported Macros
  * @{
  */

/** @brief  Reset CORDIC handle state.
  * @param  __HANDLE__ CORDIC handle
  * @retval None
  */
#if USE_HAL_CORDIC_REGISTER_CALLBACKS == 1
#define __HAL_CORDIC_RESET_HANDLE_STATE(__HANDLE__) do{                                                \
                                                       (__HANDLE__)->State = HAL_CORDIC_STATE_RESET;   \
                                                       (__HANDLE__)->MspInitCallback = NULL;           \
                                                       (__HANDLE__)->MspDeInitCallback = NULL;         \
                                                      } while(0)
#else
#define __HAL_CORDIC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_CORDIC_STATE_RESET)
#endif /*USE_HAL_CORDIC_REGISTER_CALLBACKS */

/**
  * @brief  Enable the CORDIC interrupt when result is ready
  * @param  __HANDLE__ CORDIC handle.
  * @param  __INTERRUPT__ CORDIC Interrupt.
  *         This parameter can be one of the following values:
  *            @arg @ref CORDIC_IT_IEN Enable Interrupt
  * @retval None
  */
#define __HAL_CORDIC_ENABLE_IT(__HANDLE__, __INTERRUPT__)                     \
                  (((__HANDLE__)->Instance->CSR) |= (__INTERRUPT__))

/**
  * @brief  Disable the CORDIC interrupt
  * @param  __HANDLE__ CORDIC handle.
  * @param  __INTERRUPT__ CORDIC Interrupt.
  *         This parameter can be one of the following values:
  *            @arg @ref CORDIC_IT_IEN Enable Interrupt
  * @retval None
  */
#define __HAL_CORDIC_DISABLE_IT(__HANDLE__, __INTERRUPT__)                    \
                 (((__HANDLE__)->Instance->CSR) &= ~(__INTERRUPT__))

/** @brief  Check whether the specified CORDIC interrupt occurred or not.
            Dummy macro as no interrupt status flag.
  * @param  __HANDLE__ CORDIC handle.
  * @param  __INTERRUPT__ CORDIC interrupt to check
  * @retval SET (interrupt occurred) or RESET (interrupt did not occurred)
  */
#define __HAL_CORDIC_GET_IT(__HANDLE__, __INTERRUPT__)     /* Dummy macro */

/** @brief  Clear specified CORDIC interrupt status. Dummy macro as no
            interrupt status flag.
  * @param  __HANDLE__ CORDIC handle.
  * @param  __INTERRUPT__ CORDIC interrupt to clear
  * @retval None
  */
#define __HAL_CORDIC_CLEAR_IT(__HANDLE__, __INTERRUPT__)   /* Dummy macro */

/** @brief  Check whether the specified CORDIC status flag is set or not.
  * @param  __HANDLE__ CORDIC handle.
  * @param  __FLAG__ CORDIC flag to check
  *         This parameter can be one of the following values:
  *            @arg @ref CORDIC_FLAG_RRDY Result Ready Flag
  * @retval SET (flag is set) or RESET (flag is reset)
  */
#define __HAL_CORDIC_GET_FLAG(__HANDLE__, __FLAG__)                           \
        ((((__HANDLE__)->Instance->CSR) & (__FLAG__)) == (__FLAG__))

/** @brief  Clear specified CORDIC status flag. Dummy macro as no
            flag can be cleared.
  * @param  __HANDLE__ CORDIC handle.
  * @param  __FLAG__ CORDIC flag to clear
  *         This parameter can be one of the following values:
  *            @arg @ref CORDIC_FLAG_RRDY Result Ready Flag
  * @retval None
  */
#define __HAL_CORDIC_CLEAR_FLAG(__HANDLE__, __FLAG__)     /* Dummy macro */

/** @brief  Check whether the specified CORDIC interrupt is enabled or not.
  * @param  __HANDLE__ CORDIC handle.
  * @param  __INTERRUPT__ CORDIC interrupt to check
  *         This parameter can be one of the following values:
  *            @arg @ref CORDIC_IT_IEN Enable Interrupt
  * @retval FlagStatus
  */
#define __HAL_CORDIC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                 \
        (((__HANDLE__)->Instance->CSR) & (__INTERRUPT__))

/**
  * @}
  */

/* Private macros --------------------------------------------------------*/
/** @defgroup  CORDIC_Private_Macros   CORDIC Private Macros
  * @{
  */

/**
  * @brief  Verify the CORDIC function.
  * @param  __FUNCTION__ Name of the function.
  * @retval SET (__FUNCTION__ is a valid value) or RESET (__FUNCTION__ is invalid)
  */
#define IS_CORDIC_FUNCTION(__FUNCTION__) (((__FUNCTION__) == CORDIC_FUNCTION_COSINE)       || \
                                          ((__FUNCTION__) == CORDIC_FUNCTION_SINE)         || \
                                          ((__FUNCTION__) == CORDIC_FUNCTION_PHASE)        || \
                                          ((__FUNCTION__) == CORDIC_FUNCTION_MODULUS)      || \
                                          ((__FUNCTION__) == CORDIC_FUNCTION_ARCTANGENT)   || \
                                          ((__FUNCTION__) == CORDIC_FUNCTION_HCOSINE)      || \
                                          ((__FUNCTION__) == CORDIC_FUNCTION_HSINE)        || \
                                          ((__FUNCTION__) == CORDIC_FUNCTION_HARCTANGENT)  || \
                                          ((__FUNCTION__) == CORDIC_FUNCTION_NATURALLOG)   || \
                                          ((__FUNCTION__) == CORDIC_FUNCTION_SQUAREROOT))


/**
  * @brief  Verify the CORDIC precision.
  * @param  __PRECISION__ CORDIC Precision in Cycles Number.
  * @retval SET (__PRECISION__ is a valid value) or RESET (__PRECISION__ is invalid)
  */
#define IS_CORDIC_PRECISION(__PRECISION__) (((__PRECISION__) == CORDIC_PRECISION_1CYCLE)   || \
                                            ((__PRECISION__) == CORDIC_PRECISION_2CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_3CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_4CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_5CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_6CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_7CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_8CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_9CYCLES)  || \
                                            ((__PRECISION__) == CORDIC_PRECISION_10CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_11CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_12CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_13CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_14CYCLES) || \
                                            ((__PRECISION__) == CORDIC_PRECISION_15CYCLES))

/**
  * @brief  Verify the CORDIC scaling factor.
  * @param  __SCALE__ Number of cycles for calculation, 1 cycle corresponding to 4 algorithm iterations.
  * @retval SET (__SCALE__ is a valid value) or RESET (__SCALE__ is invalid)
  */
#define IS_CORDIC_SCALE(__SCALE__) (((__SCALE__) == CORDIC_SCALE_0)  || \
                                    ((__SCALE__) == CORDIC_SCALE_1)  || \
                                    ((__SCALE__) == CORDIC_SCALE_2)  || \
                                    ((__SCALE__) == CORDIC_SCALE_3)  || \
                                    ((__SCALE__) == CORDIC_SCALE_4)  || \
                                    ((__SCALE__) == CORDIC_SCALE_5)  || \
                                    ((__SCALE__) == CORDIC_SCALE_6)  || \
                                    ((__SCALE__) == CORDIC_SCALE_7))

/**
  * @brief  Verify the CORDIC number of 32-bits write expected for one calculation.
  * @param  __NBWRITE__ Number of 32-bits write expected for one calculation.
  * @retval SET (__NBWRITE__ is a valid value) or RESET (__NBWRITE__ is invalid)
  */
#define IS_CORDIC_NBWRITE(__NBWRITE__) (((__NBWRITE__) == CORDIC_NBWRITE_1)  || \
                                        ((__NBWRITE__) == CORDIC_NBWRITE_2))

/**
  * @brief  Verify the CORDIC number of 32-bits read expected after one calculation.
  * @param  __NBREAD__ Number of 32-bits read expected after one calculation.
  * @retval SET (__NBREAD__ is a valid value) or RESET (__NBREAD__ is invalid)
  */
#define IS_CORDIC_NBREAD(__NBREAD__) (((__NBREAD__) == CORDIC_NBREAD_1)  || \
                                      ((__NBREAD__) == CORDIC_NBREAD_2))

/**
  * @brief  Verify the CORDIC input data size for one calculation.
  * @param  __INSIZE__ input data size for one calculation.
  * @retval SET (__INSIZE__ is a valid value) or RESET (__INSIZE__ is invalid)
  */
#define IS_CORDIC_INSIZE(__INSIZE__) (((__INSIZE__) == CORDIC_INSIZE_32BITS)  || \
                                      ((__INSIZE__) == CORDIC_INSIZE_16BITS))

/**
  * @brief  Verify the CORDIC output data size for one calculation.
  * @param  __OUTSIZE__ output data size for one calculation.
  * @retval SET (__OUTSIZE__ is a valid value) or RESET (__OUTSIZE__ is invalid)
  */
#define IS_CORDIC_OUTSIZE(__OUTSIZE__) (((__OUTSIZE__) == CORDIC_OUTSIZE_32BITS)  || \
                                        ((__OUTSIZE__) == CORDIC_OUTSIZE_16BITS))

/**
  * @brief  Verify the CORDIC DMA transfer Direction.
  * @param  __DMADIR__ DMA transfer direction.
  * @retval SET (__DMADIR__ is a valid value) or RESET (__DMADIR__ is invalid)
  */
#define IS_CORDIC_DMA_DIRECTION(__DMADIR__) (((__DMADIR__) == CORDIC_DMA_DIR_IN)  || \
                                             ((__DMADIR__) == CORDIC_DMA_DIR_OUT) || \
                                             ((__DMADIR__) == CORDIC_DMA_DIR_IN_OUT))

/**
  * @}
  */

/** @addtogroup CORDIC_Exported_Functions
  * @{
  */
/* Exported functions ------------------------------------------------------- */

/** @addtogroup CORDIC_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions ******************************/
HAL_StatusTypeDef HAL_CORDIC_Init(CORDIC_HandleTypeDef *hcordic);
HAL_StatusTypeDef HAL_CORDIC_DeInit(CORDIC_HandleTypeDef *hcordic);
void HAL_CORDIC_MspInit(CORDIC_HandleTypeDef *hcordic);
void HAL_CORDIC_MspDeInit(CORDIC_HandleTypeDef *hcordic);

#if USE_HAL_CORDIC_REGISTER_CALLBACKS == 1
/* Callbacks Register/UnRegister functions  ***********************************/
HAL_StatusTypeDef HAL_CORDIC_RegisterCallback(CORDIC_HandleTypeDef *hcordic, HAL_CORDIC_CallbackIDTypeDef CallbackID, pCORDIC_CallbackTypeDef pCallback);
HAL_StatusTypeDef HAL_CORDIC_UnRegisterCallback(CORDIC_HandleTypeDef *hcordic, HAL_CORDIC_CallbackIDTypeDef CallbackID);
/**
  * @}
  */

/** @addtogroup CORDIC_Exported_Functions_Group2
  * @{
  */
#endif /* USE_HAL_CORDIC_REGISTER_CALLBACKS */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef HAL_CORDIC_Configure(CORDIC_HandleTypeDef *hcordic, CORDIC_ConfigTypeDef *sConfig);
HAL_StatusTypeDef HAL_CORDIC_Calculate(CORDIC_HandleTypeDef *hcordic, int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc, uint32_t Timeout);
HAL_StatusTypeDef HAL_CORDIC_CalculateZO(CORDIC_HandleTypeDef *hcordic, int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc, uint32_t Timeout);
HAL_StatusTypeDef HAL_CORDIC_Calculate_IT(CORDIC_HandleTypeDef *hcordic, int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc);
HAL_StatusTypeDef HAL_CORDIC_Calculate_DMA(CORDIC_HandleTypeDef *hcordic, int32_t *pInBuff, int32_t *pOutBuff, uint32_t NbCalc, uint32_t DMADirection);
/**
  * @}
  */

/** @addtogroup CORDIC_Exported_Functions_Group3
  * @{
  */
/* Callback functions *********************************************************/
void HAL_CORDIC_ErrorCallback(CORDIC_HandleTypeDef *hcordic);
void HAL_CORDIC_CalculateCpltCallback(CORDIC_HandleTypeDef *hcordic);
/**
  * @}
  */

/** @addtogroup CORDIC_Exported_Functions_Group4
  * @{
  */
/* IRQ handler management *****************************************************/
void HAL_CORDIC_IRQHandler(CORDIC_HandleTypeDef *hcordic);
/**
  * @}
  */

/** @addtogroup CORDIC_Exported_Functions_Group5
  * @{
  */
/* Peripheral State functions *************************************************/
HAL_CORDIC_StateTypeDef HAL_CORDIC_GetState(CORDIC_HandleTypeDef *hcordic);
uint32_t HAL_CORDIC_GetError(CORDIC_HandleTypeDef *hcordic);
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

#endif /* STM32G4xx_HAL_CORDIC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
