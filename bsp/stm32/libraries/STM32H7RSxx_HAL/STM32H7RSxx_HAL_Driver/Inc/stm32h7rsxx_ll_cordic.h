/**
  ******************************************************************************
  * @file    stm32h7rsxx_ll_cordic.h
  * @author  MCD Application Team
  * @brief   Header file of CORDIC LL module.
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
#ifndef STM32H7RSxx_LL_CORDIC_H
#define STM32H7RSxx_LL_CORDIC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx.h"

/** @addtogroup STM32H7RSxx_LL_Driver
  * @{
  */

#if defined(CORDIC)

/** @defgroup CORDIC_LL CORDIC
  * @{
  */

/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup CORDIC_LL_Exported_Constants CORDIC Exported Constants
  * @{
  */

/** @defgroup CORDIC_LL_EC_GET_FLAG Get Flags Defines
  * @brief    Flags defines which can be used with LL_CORDIC_ReadReg function.
  * @{
  */
#define LL_CORDIC_FLAG_RRDY                CORDIC_CSR_RRDY
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_CORDIC_ReadReg and LL_CORDIC_WriteReg functions.
  * @{
  */
#define LL_CORDIC_IT_IEN                   CORDIC_CSR_IEN            /*!< Result Ready interrupt enable */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_FUNCTION FUNCTION
  * @{
  */
#define LL_CORDIC_FUNCTION_COSINE          (0x00000000U)                                                          /*!< Cosine */
#define LL_CORDIC_FUNCTION_SINE            ((uint32_t)(CORDIC_CSR_FUNC_0))                                        /*!< Sine */
#define LL_CORDIC_FUNCTION_PHASE           ((uint32_t)(CORDIC_CSR_FUNC_1))                                        /*!< Phase */
#define LL_CORDIC_FUNCTION_MODULUS         ((uint32_t)(CORDIC_CSR_FUNC_1 | CORDIC_CSR_FUNC_0))                    /*!< Modulus */
#define LL_CORDIC_FUNCTION_ARCTANGENT      ((uint32_t)(CORDIC_CSR_FUNC_2))                                        /*!< Arctangent */
#define LL_CORDIC_FUNCTION_HCOSINE         ((uint32_t)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_0))                    /*!< Hyperbolic Cosine */
#define LL_CORDIC_FUNCTION_HSINE           ((uint32_t)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_1))                    /*!< Hyperbolic Sine */
#define LL_CORDIC_FUNCTION_HARCTANGENT     ((uint32_t)(CORDIC_CSR_FUNC_2 | CORDIC_CSR_FUNC_1 | CORDIC_CSR_FUNC_0))/*!< Hyperbolic Arctangent */
#define LL_CORDIC_FUNCTION_NATURALLOG      ((uint32_t)(CORDIC_CSR_FUNC_3))                                        /*!< Natural Logarithm */
#define LL_CORDIC_FUNCTION_SQUAREROOT      ((uint32_t)(CORDIC_CSR_FUNC_3 | CORDIC_CSR_FUNC_0))                    /*!< Square Root */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_PRECISION PRECISION
  * @{
  */
#define LL_CORDIC_PRECISION_1CYCLE         ((uint32_t)(CORDIC_CSR_PRECISION_0))
#define LL_CORDIC_PRECISION_2CYCLES        ((uint32_t)(CORDIC_CSR_PRECISION_1))
#define LL_CORDIC_PRECISION_3CYCLES        ((uint32_t)(CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
#define LL_CORDIC_PRECISION_4CYCLES        ((uint32_t)(CORDIC_CSR_PRECISION_2))
#define LL_CORDIC_PRECISION_5CYCLES        ((uint32_t)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_0))
#define LL_CORDIC_PRECISION_6CYCLES        ((uint32_t)(CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1))
#define LL_CORDIC_PRECISION_7CYCLES        ((uint32_t)(CORDIC_CSR_PRECISION_2\
                                                       | CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
#define LL_CORDIC_PRECISION_8CYCLES        ((uint32_t)(CORDIC_CSR_PRECISION_3))
#define LL_CORDIC_PRECISION_9CYCLES        ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_0))
#define LL_CORDIC_PRECISION_10CYCLES       ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_1))
#define LL_CORDIC_PRECISION_11CYCLES       ((uint32_t)(CORDIC_CSR_PRECISION_3\
                                                       | CORDIC_CSR_PRECISION_1 | CORDIC_CSR_PRECISION_0))
#define LL_CORDIC_PRECISION_12CYCLES       ((uint32_t)(CORDIC_CSR_PRECISION_3 | CORDIC_CSR_PRECISION_2))
#define LL_CORDIC_PRECISION_13CYCLES       ((uint32_t)(CORDIC_CSR_PRECISION_3\
                                                       | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_0))
#define LL_CORDIC_PRECISION_14CYCLES       ((uint32_t)(CORDIC_CSR_PRECISION_3\
                                                       | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1))
#define LL_CORDIC_PRECISION_15CYCLES       ((uint32_t)(CORDIC_CSR_PRECISION_3\
                                                       | CORDIC_CSR_PRECISION_2 | CORDIC_CSR_PRECISION_1\
                                                       | CORDIC_CSR_PRECISION_0))
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_SCALE SCALE
  * @{
  */
#define LL_CORDIC_SCALE_0                  (0x00000000U)
#define LL_CORDIC_SCALE_1                  ((uint32_t)(CORDIC_CSR_SCALE_0))
#define LL_CORDIC_SCALE_2                  ((uint32_t)(CORDIC_CSR_SCALE_1))
#define LL_CORDIC_SCALE_3                  ((uint32_t)(CORDIC_CSR_SCALE_1 | CORDIC_CSR_SCALE_0))
#define LL_CORDIC_SCALE_4                  ((uint32_t)(CORDIC_CSR_SCALE_2))
#define LL_CORDIC_SCALE_5                  ((uint32_t)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_0))
#define LL_CORDIC_SCALE_6                  ((uint32_t)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_1))
#define LL_CORDIC_SCALE_7                  ((uint32_t)(CORDIC_CSR_SCALE_2 | CORDIC_CSR_SCALE_1 | CORDIC_CSR_SCALE_0))
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_NBWRITE NBWRITE
  * @{
  */
#define LL_CORDIC_NBWRITE_1                (0x00000000U)             /*!< One 32-bits write containing either only one
                                                                          32-bit data input (Q1.31 format), or two
                                                                          16-bit data input (Q1.15 format) packed
                                                                          in one 32 bits Data */
#define LL_CORDIC_NBWRITE_2                CORDIC_CSR_NARGS          /*!< Two 32-bit write containing two 32-bits data input
                                                                          (Q1.31 format) */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_NBREAD NBREAD
  * @{
  */
#define LL_CORDIC_NBREAD_1                 (0x00000000U)             /*!< One 32-bits read containing either only one
                                                                          32-bit data output (Q1.31 format), or two
                                                                          16-bit data output (Q1.15 format) packed
                                                                          in one 32 bits Data */
#define LL_CORDIC_NBREAD_2                 CORDIC_CSR_NRES           /*!< Two 32-bit Data containing two 32-bits data output
                                                                          (Q1.31 format) */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_INSIZE INSIZE
  * @{
  */
#define LL_CORDIC_INSIZE_32BITS            (0x00000000U)             /*!< 32 bits input data size (Q1.31 format) */
#define LL_CORDIC_INSIZE_16BITS            CORDIC_CSR_ARGSIZE        /*!< 16 bits input data size (Q1.15 format) */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_OUTSIZE OUTSIZE
  * @{
  */
#define LL_CORDIC_OUTSIZE_32BITS           (0x00000000U)             /*!< 32 bits output data size (Q1.31 format) */
#define LL_CORDIC_OUTSIZE_16BITS           CORDIC_CSR_RESSIZE        /*!< 16 bits output data size (Q1.15 format) */
/**
  * @}
  */

/** @defgroup CORDIC_LL_EC_DMA_REG_DATA DMA register data
  * @{
  */
#define LL_CORDIC_DMA_REG_DATA_IN          (0x00000000U)             /*!< Get address of input data register */
#define LL_CORDIC_DMA_REG_DATA_OUT         (0x00000001U)             /*!< Get address of output data register */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup CORDIC_LL_Exported_Macros CORDIC Exported Macros
  * @{
  */

/** @defgroup CORDIC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in CORDIC register.
  * @param  __INSTANCE__ CORDIC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_CORDIC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in CORDIC register.
  * @param  __INSTANCE__ CORDIC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_CORDIC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @defgroup CORDIC_LL_Exported_Functions CORDIC Exported Functions
  * @{
  */

/** @defgroup CORDIC_LL_EF_Configuration CORDIC Configuration functions
  * @{
  */

/**
  * @brief  Configure the CORDIC processing.
  * @note   This function set all parameters of CORDIC processing.
  *         These parameters can also be set individually using
  *         dedicated functions:
  *         - @ref LL_CORDIC_SetFunction()
  *         - @ref LL_CORDIC_SetPrecision()
  *         - @ref LL_CORDIC_SetScale()
  *         - @ref LL_CORDIC_SetNbWrite()
  *         - @ref LL_CORDIC_SetNbRead()
  *         - @ref LL_CORDIC_SetInSize()
  *         - @ref LL_CORDIC_SetOutSize()
  * @rmtoll CSR          FUNC          LL_CORDIC_Config\n
  *         CSR          PRECISION     LL_CORDIC_Config\n
  *         CSR          SCALE         LL_CORDIC_Config\n
  *         CSR          NARGS         LL_CORDIC_Config\n
  *         CSR          NRES          LL_CORDIC_Config\n
  *         CSR          ARGSIZE       LL_CORDIC_Config\n
  *         CSR          RESIZE        LL_CORDIC_Config
  * @param  CORDICx CORDIC instance
  * @param  Function parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_FUNCTION_COSINE
  *         @arg @ref LL_CORDIC_FUNCTION_SINE
  *         @arg @ref LL_CORDIC_FUNCTION_PHASE
  *         @arg @ref LL_CORDIC_FUNCTION_MODULUS
  *         @arg @ref LL_CORDIC_FUNCTION_ARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_HCOSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_NATURALLOG
  *         @arg @ref LL_CORDIC_FUNCTION_SQUAREROOT
  * @param  Precision parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_PRECISION_1CYCLE
  *         @arg @ref LL_CORDIC_PRECISION_2CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_3CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_4CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_5CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_6CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_7CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_8CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_9CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_10CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_11CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_12CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_13CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_14CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_15CYCLES
  * @param  Scale parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_SCALE_0
  *         @arg @ref LL_CORDIC_SCALE_1
  *         @arg @ref LL_CORDIC_SCALE_2
  *         @arg @ref LL_CORDIC_SCALE_3
  *         @arg @ref LL_CORDIC_SCALE_4
  *         @arg @ref LL_CORDIC_SCALE_5
  *         @arg @ref LL_CORDIC_SCALE_6
  *         @arg @ref LL_CORDIC_SCALE_7
  * @param  NbWrite parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_NBWRITE_1
  *         @arg @ref LL_CORDIC_NBWRITE_2
  * @param  NbRead parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_NBREAD_1
  *         @arg @ref LL_CORDIC_NBREAD_2
  * @param  InSize parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_INSIZE_32BITS
  *         @arg @ref LL_CORDIC_INSIZE_16BITS
  * @param  OutSize parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_OUTSIZE_32BITS
  *         @arg @ref LL_CORDIC_OUTSIZE_16BITS
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_Config(CORDIC_TypeDef *CORDICx, uint32_t Function, uint32_t Precision, uint32_t Scale,
                                      uint32_t NbWrite, uint32_t NbRead, uint32_t InSize, uint32_t OutSize)
{
  MODIFY_REG(CORDICx->CSR,
             CORDIC_CSR_FUNC | CORDIC_CSR_PRECISION | CORDIC_CSR_SCALE |
             CORDIC_CSR_NARGS | CORDIC_CSR_NRES | CORDIC_CSR_ARGSIZE | CORDIC_CSR_RESSIZE,
             Function | Precision | Scale |
             NbWrite | NbRead | InSize | OutSize);
}

/**
  * @brief  Configure function.
  * @rmtoll CSR          FUNC          LL_CORDIC_SetFunction
  * @param  CORDICx CORDIC Instance
  * @param  Function parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_FUNCTION_COSINE
  *         @arg @ref LL_CORDIC_FUNCTION_SINE
  *         @arg @ref LL_CORDIC_FUNCTION_PHASE
  *         @arg @ref LL_CORDIC_FUNCTION_MODULUS
  *         @arg @ref LL_CORDIC_FUNCTION_ARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_HCOSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_NATURALLOG
  *         @arg @ref LL_CORDIC_FUNCTION_SQUAREROOT
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_SetFunction(CORDIC_TypeDef *CORDICx, uint32_t Function)
{
  MODIFY_REG(CORDICx->CSR, CORDIC_CSR_FUNC, Function);
}

/**
  * @brief  Return function.
  * @rmtoll CSR          FUNC          LL_CORDIC_GetFunction
  * @param  CORDICx CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_FUNCTION_COSINE
  *         @arg @ref LL_CORDIC_FUNCTION_SINE
  *         @arg @ref LL_CORDIC_FUNCTION_PHASE
  *         @arg @ref LL_CORDIC_FUNCTION_MODULUS
  *         @arg @ref LL_CORDIC_FUNCTION_ARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_HCOSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HSINE
  *         @arg @ref LL_CORDIC_FUNCTION_HARCTANGENT
  *         @arg @ref LL_CORDIC_FUNCTION_NATURALLOG
  *         @arg @ref LL_CORDIC_FUNCTION_SQUAREROOT
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetFunction(const CORDIC_TypeDef *CORDICx)
{
  return (uint32_t)(READ_BIT(CORDICx->CSR, CORDIC_CSR_FUNC));
}

/**
  * @brief  Configure precision in cycles number.
  * @rmtoll CSR          PRECISION     LL_CORDIC_SetPrecision
  * @param  CORDICx CORDIC Instance
  * @param  Precision parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_PRECISION_1CYCLE
  *         @arg @ref LL_CORDIC_PRECISION_2CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_3CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_4CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_5CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_6CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_7CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_8CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_9CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_10CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_11CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_12CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_13CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_14CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_15CYCLES
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_SetPrecision(CORDIC_TypeDef *CORDICx, uint32_t Precision)
{
  MODIFY_REG(CORDICx->CSR, CORDIC_CSR_PRECISION, Precision);
}

/**
  * @brief  Return precision in cycles number.
  * @rmtoll CSR          PRECISION     LL_CORDIC_GetPrecision
  * @param  CORDICx CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_PRECISION_1CYCLE
  *         @arg @ref LL_CORDIC_PRECISION_2CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_3CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_4CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_5CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_6CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_7CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_8CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_9CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_10CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_11CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_12CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_13CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_14CYCLES
  *         @arg @ref LL_CORDIC_PRECISION_15CYCLES
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetPrecision(const CORDIC_TypeDef *CORDICx)
{
  return (uint32_t)(READ_BIT(CORDICx->CSR, CORDIC_CSR_PRECISION));
}

/**
  * @brief  Configure scaling factor.
  * @rmtoll CSR          SCALE         LL_CORDIC_SetScale
  * @param  CORDICx CORDIC Instance
  * @param  Scale parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_SCALE_0
  *         @arg @ref LL_CORDIC_SCALE_1
  *         @arg @ref LL_CORDIC_SCALE_2
  *         @arg @ref LL_CORDIC_SCALE_3
  *         @arg @ref LL_CORDIC_SCALE_4
  *         @arg @ref LL_CORDIC_SCALE_5
  *         @arg @ref LL_CORDIC_SCALE_6
  *         @arg @ref LL_CORDIC_SCALE_7
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_SetScale(CORDIC_TypeDef *CORDICx, uint32_t Scale)
{
  MODIFY_REG(CORDICx->CSR, CORDIC_CSR_SCALE, Scale);
}

/**
  * @brief  Return scaling factor.
  * @rmtoll CSR          SCALE         LL_CORDIC_GetScale
  * @param  CORDICx CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_SCALE_0
  *         @arg @ref LL_CORDIC_SCALE_1
  *         @arg @ref LL_CORDIC_SCALE_2
  *         @arg @ref LL_CORDIC_SCALE_3
  *         @arg @ref LL_CORDIC_SCALE_4
  *         @arg @ref LL_CORDIC_SCALE_5
  *         @arg @ref LL_CORDIC_SCALE_6
  *         @arg @ref LL_CORDIC_SCALE_7
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetScale(const CORDIC_TypeDef *CORDICx)
{
  return (uint32_t)(READ_BIT(CORDICx->CSR, CORDIC_CSR_SCALE));
}

/**
  * @brief  Configure number of 32-bit write expected for one calculation.
  * @rmtoll CSR          NARGS         LL_CORDIC_SetNbWrite
  * @param  CORDICx CORDIC Instance
  * @param  NbWrite parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_NBWRITE_1
  *         @arg @ref LL_CORDIC_NBWRITE_2
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_SetNbWrite(CORDIC_TypeDef *CORDICx, uint32_t NbWrite)
{
  MODIFY_REG(CORDICx->CSR, CORDIC_CSR_NARGS, NbWrite);
}

/**
  * @brief  Return number of 32-bit write expected for one calculation.
  * @rmtoll CSR          NARGS         LL_CORDIC_GetNbWrite
  * @param  CORDICx CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_NBWRITE_1
  *         @arg @ref LL_CORDIC_NBWRITE_2
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetNbWrite(const CORDIC_TypeDef *CORDICx)
{
  return (uint32_t)(READ_BIT(CORDICx->CSR, CORDIC_CSR_NARGS));
}

/**
  * @brief  Configure number of 32-bit read expected after one calculation.
  * @rmtoll CSR          NRES          LL_CORDIC_SetNbRead
  * @param  CORDICx CORDIC Instance
  * @param  NbRead parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_NBREAD_1
  *         @arg @ref LL_CORDIC_NBREAD_2
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_SetNbRead(CORDIC_TypeDef *CORDICx, uint32_t NbRead)
{
  MODIFY_REG(CORDICx->CSR, CORDIC_CSR_NRES, NbRead);
}

/**
  * @brief  Return number of 32-bit read expected after one calculation.
  * @rmtoll CSR          NRES          LL_CORDIC_GetNbRead
  * @param  CORDICx CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_NBREAD_1
  *         @arg @ref LL_CORDIC_NBREAD_2
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetNbRead(const CORDIC_TypeDef *CORDICx)
{
  return (uint32_t)(READ_BIT(CORDICx->CSR, CORDIC_CSR_NRES));
}

/**
  * @brief  Configure width of input data.
  * @rmtoll CSR          ARGSIZE       LL_CORDIC_SetInSize
  * @param  CORDICx CORDIC Instance
  * @param  InSize parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_INSIZE_32BITS
  *         @arg @ref LL_CORDIC_INSIZE_16BITS
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_SetInSize(CORDIC_TypeDef *CORDICx, uint32_t InSize)
{
  MODIFY_REG(CORDICx->CSR, CORDIC_CSR_ARGSIZE, InSize);
}

/**
  * @brief  Return width of input data.
  * @rmtoll CSR          ARGSIZE       LL_CORDIC_GetInSize
  * @param  CORDICx CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_INSIZE_32BITS
  *         @arg @ref LL_CORDIC_INSIZE_16BITS
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetInSize(const CORDIC_TypeDef *CORDICx)
{
  return (uint32_t)(READ_BIT(CORDICx->CSR, CORDIC_CSR_ARGSIZE));
}

/**
  * @brief  Configure width of output data.
  * @rmtoll CSR          RESIZE       LL_CORDIC_SetOutSize
  * @param  CORDICx CORDIC Instance
  * @param  OutSize parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_OUTSIZE_32BITS
  *         @arg @ref LL_CORDIC_OUTSIZE_16BITS
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_SetOutSize(CORDIC_TypeDef *CORDICx, uint32_t OutSize)
{
  MODIFY_REG(CORDICx->CSR, CORDIC_CSR_RESSIZE, OutSize);
}

/**
  * @brief  Return width of output data.
  * @rmtoll CSR          RESIZE       LL_CORDIC_GetOutSize
  * @param  CORDICx CORDIC Instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_CORDIC_OUTSIZE_32BITS
  *         @arg @ref LL_CORDIC_OUTSIZE_16BITS
  */
__STATIC_INLINE uint32_t LL_CORDIC_GetOutSize(const CORDIC_TypeDef *CORDICx)
{
  return (uint32_t)(READ_BIT(CORDICx->CSR, CORDIC_CSR_RESSIZE));
}

/**
  * @}
  */

/** @defgroup CORDIC_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable CORDIC result ready interrupt
  * @rmtoll CSR          IEN           LL_CORDIC_EnableIT
  * @param  CORDICx CORDIC Instance
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_EnableIT(CORDIC_TypeDef *CORDICx)
{
  SET_BIT(CORDICx->CSR, CORDIC_CSR_IEN);
}

/**
  * @brief  Disable CORDIC result ready interrupt
  * @rmtoll CSR          IEN           LL_CORDIC_DisableIT
  * @param  CORDICx CORDIC Instance
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_DisableIT(CORDIC_TypeDef *CORDICx)
{
  CLEAR_BIT(CORDICx->CSR, CORDIC_CSR_IEN);
}

/**
  * @brief  Check CORDIC result ready interrupt state.
  * @rmtoll CSR          IEN           LL_CORDIC_IsEnabledIT
  * @param  CORDICx CORDIC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CORDIC_IsEnabledIT(const CORDIC_TypeDef *CORDICx)
{
  return ((READ_BIT(CORDICx->CSR, CORDIC_CSR_IEN) == (CORDIC_CSR_IEN)) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup CORDIC_LL_EF_DMA_Management DMA_Management
  * @{
  */

/**
  * @brief  Enable CORDIC DMA read channel request.
  * @rmtoll CSR          DMAREN        LL_CORDIC_EnableDMAReq_RD
  * @param  CORDICx CORDIC Instance
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_EnableDMAReq_RD(CORDIC_TypeDef *CORDICx)
{
  SET_BIT(CORDICx->CSR, CORDIC_CSR_DMAREN);
}

/**
  * @brief  Disable CORDIC DMA read channel request.
  * @rmtoll CSR          DMAREN        LL_CORDIC_DisableDMAReq_RD
  * @param  CORDICx CORDIC Instance
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_DisableDMAReq_RD(CORDIC_TypeDef *CORDICx)
{
  CLEAR_BIT(CORDICx->CSR, CORDIC_CSR_DMAREN);
}

/**
  * @brief  Check CORDIC DMA read channel request state.
  * @rmtoll CSR          DMAREN        LL_CORDIC_IsEnabledDMAReq_RD
  * @param  CORDICx CORDIC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CORDIC_IsEnabledDMAReq_RD(const CORDIC_TypeDef *CORDICx)
{
  return ((READ_BIT(CORDICx->CSR, CORDIC_CSR_DMAREN) == (CORDIC_CSR_DMAREN)) ? 1U : 0U);
}

/**
  * @brief  Enable CORDIC DMA write channel request.
  * @rmtoll CSR          DMAWEN        LL_CORDIC_EnableDMAReq_WR
  * @param  CORDICx CORDIC Instance
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_EnableDMAReq_WR(CORDIC_TypeDef *CORDICx)
{
  SET_BIT(CORDICx->CSR, CORDIC_CSR_DMAWEN);
}

/**
  * @brief  Disable CORDIC DMA write channel request.
  * @rmtoll CSR          DMAWEN        LL_CORDIC_DisableDMAReq_WR
  * @param  CORDICx CORDIC Instance
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_DisableDMAReq_WR(CORDIC_TypeDef *CORDICx)
{
  CLEAR_BIT(CORDICx->CSR, CORDIC_CSR_DMAWEN);
}

/**
  * @brief  Check CORDIC DMA write channel request state.
  * @rmtoll CSR          DMAWEN        LL_CORDIC_IsEnabledDMAReq_WR
  * @param  CORDICx CORDIC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CORDIC_IsEnabledDMAReq_WR(const CORDIC_TypeDef *CORDICx)
{
  return ((READ_BIT(CORDICx->CSR, CORDIC_CSR_DMAWEN) == (CORDIC_CSR_DMAWEN)) ? 1U : 0U);
}

/**
  * @brief  Get the CORDIC data register address used for DMA transfer.
  * @rmtoll RDATA        RES           LL_CORDIC_DMA_GetRegAddr\n
  * @rmtoll WDATA        ARG           LL_CORDIC_DMA_GetRegAddr
  * @param  CORDICx CORDIC Instance
  * @param  Direction parameter can be one of the following values:
  *         @arg @ref LL_CORDIC_DMA_REG_DATA_IN
  *         @arg @ref LL_CORDIC_DMA_REG_DATA_OUT
  * @retval Address of data register
  */
__STATIC_INLINE uint32_t LL_CORDIC_DMA_GetRegAddr(const CORDIC_TypeDef *CORDICx, uint32_t Direction)
{
  uint32_t data_reg_addr;

  if (Direction == LL_CORDIC_DMA_REG_DATA_OUT)
  {
    /* return address of RDATA register */
    data_reg_addr = (uint32_t) &(CORDICx->RDATA);
  }
  else
  {
    /* return address of WDATA register */
    data_reg_addr = (uint32_t) &(CORDICx->WDATA);
  }

  return data_reg_addr;
}

/**
  * @}
  */

/** @defgroup CORDIC_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Check CORDIC result ready flag state.
  * @rmtoll CSR          RRDY          LL_CORDIC_IsActiveFlag_RRDY
  * @param  CORDICx CORDIC Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_CORDIC_IsActiveFlag_RRDY(const CORDIC_TypeDef *CORDICx)
{
  return ((READ_BIT(CORDICx->CSR, CORDIC_CSR_RRDY) == (CORDIC_CSR_RRDY)) ? 1U : 0U);
}

/**
  * @}
  */

/** @defgroup CORDIC_LL_EF_Data_Management Data_Management
  * @{
  */

/**
  * @brief  Write 32-bit input data for the CORDIC processing.
  * @rmtoll WDATA        ARG           LL_CORDIC_WriteData
  * @param  CORDICx CORDIC Instance
  * @param  InData 0 .. 0xFFFFFFFF : 32-bit value to be provided as input data for CORDIC processing.
  * @retval None
  */
__STATIC_INLINE void LL_CORDIC_WriteData(CORDIC_TypeDef *CORDICx, uint32_t InData)
{
  WRITE_REG(CORDICx->WDATA, InData);
}

/**
  * @brief  Return 32-bit output data of CORDIC processing.
  * @rmtoll RDATA        RES           LL_CORDIC_ReadData
  * @param  CORDICx CORDIC Instance
  * @retval 32-bit output data of CORDIC processing.
  */
__STATIC_INLINE uint32_t LL_CORDIC_ReadData(const CORDIC_TypeDef *CORDICx)
{
  return (uint32_t)(READ_REG(CORDICx->RDATA));
}

/**
  * @}
  */



#if defined(USE_FULL_LL_DRIVER)
/** @defgroup CORDIC_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_CORDIC_DeInit(const CORDIC_TypeDef *CORDICx);

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(CORDIC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H7RSxx_LL_CORDIC_H */
