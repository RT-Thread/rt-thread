/**
  ******************************************************************************
  * @file    stm32g4xx_ll_fmac.h
  * @author  MCD Application Team
  * @brief   Header file of FMAC LL module.
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
#ifndef STM32G4xx_LL_FMAC_H
#define STM32G4xx_LL_FMAC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx.h"

/** @addtogroup STM32G4xx_LL_Driver
  * @{
  */

#if defined(FMAC)

/** @defgroup FMAC_LL FMAC
  * @{
  */

/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup FMAC_LL_Private_Macros FMAC Private Macros
  * @{
  */
/**
  * @}
  */
#endif /*USE_FULL_LL_DRIVER*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
/** @defgroup FMAC_LL_Exported_Constants FMAC Exported Constants
  * @{
  */

/** @defgroup FMAC_LL_EC_GET_FLAG Get Flag Defines
  * @brief    Flag defines which can be used with LL_FMAC_ReadReg function
  * @{
  */
#define LL_FMAC_SR_SAT                     FMAC_SR_SAT
#define LL_FMAC_SR_UNFL                    FMAC_SR_UNFL
#define LL_FMAC_SR_OVFL                    FMAC_SR_OVFL
#define LL_FMAC_SR_X1FULL                  FMAC_SR_X1FULL
#define LL_FMAC_SR_YEMPTY                  FMAC_SR_YEMPTY
/**
  * @}
  */

/** @defgroup FMAC_LL_EC_IT IT Defines
  * @brief    IT defines which can be used with LL_FMAC_ReadReg and LL_FMAC_WriteReg functions
  * @{
  */
#define LL_FMAC_CR_SATIEN                  FMAC_CR_SATIEN
#define LL_FMAC_CR_UNFLIEN                 FMAC_CR_UNFLIEN
#define LL_FMAC_CR_OVFLIEN                 FMAC_CR_OVFLIEN
#define LL_FMAC_CR_WIEN                    FMAC_CR_WIEN
#define LL_FMAC_CR_RIEN                    FMAC_CR_RIEN
/**
  * @}
  */

/** @defgroup FMAC_LL_EC_WM FMAC watermarks
  * @brief    Watermark defines that can be used for buffer full (input) or buffer empty (output)
  * @{
  */
#define LL_FMAC_WM_0_THRESHOLD_1           0x00000000UL /*!< Buffer full/empty flag set if there is less than 1 free/unread space. */
#define LL_FMAC_WM_1_THRESHOLD_2           0x01000000UL /*!< Buffer full/empty flag set if there are less than 2 free/unread spaces. */
#define LL_FMAC_WM_2_THRESHOLD_4           0x02000000UL /*!< Buffer full/empty flag set if there are less than 4 free/unread spaces. */
#define LL_FMAC_WM_3_THRESHOLD_8           0x03000000UL /*!< Buffer full/empty flag set if there are less than 8 free/empty spaces. */
/**
  * @}
  */

/** @defgroup FMAC_LL_EC_FUNC FMAC functions
  * @{
  */
#define LL_FMAC_FUNC_LOAD_X1               ((uint32_t)(FMAC_PARAM_FUNC_0))                                         /*!< Load X1 buffer */
#define LL_FMAC_FUNC_LOAD_X2               ((uint32_t)(FMAC_PARAM_FUNC_1))                                         /*!< Load X2 buffer */
#define LL_FMAC_FUNC_LOAD_Y                ((uint32_t)(FMAC_PARAM_FUNC_1 | FMAC_PARAM_FUNC_0))                     /*!< Load Y buffer */
#define LL_FMAC_FUNC_CONVO_FIR             ((uint32_t)(FMAC_PARAM_FUNC_3))                                         /*!< Convolution (FIR filter) */
#define LL_FMAC_FUNC_IIR_DIRECT_FORM_1     ((uint32_t)(FMAC_PARAM_FUNC_3 | FMAC_PARAM_FUNC_0))                     /*!< IIR filter (direct form 1) */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup FMAC_LL_Exported_Macros FMAC Exported Macros
  * @{
  */

/** @defgroup FMAC_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in FMAC register
  * @param  __INSTANCE__ FMAC Instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_FMAC_WriteReg(__INSTANCE__, __REG__, __VALUE__) WRITE_REG(__INSTANCE__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in FMAC register
  * @param  __INSTANCE__ FMAC Instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_FMAC_ReadReg(__INSTANCE__, __REG__) READ_REG(__INSTANCE__->__REG__)
/**
  * @}
  */

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @defgroup FMAC_LL_Exported_Functions FMAC Exported Functions
  * @{
  */

/** @defgroup FMAC_LL_EF_Configuration FMAC Configuration functions
  * @{
  */

/**
  * @brief  Configure X1 full watermark.
  * @rmtoll X1BUFCFG     FULL_WM       LL_FMAC_SetX1FullWatermark
  * @param  FMACx FMAC instance
  * @param  Watermark This parameter can be one of the following values:
  *         @arg @ref LL_FMAC_WM_0_THRESHOLD_1
  *         @arg @ref LL_FMAC_WM_1_THRESHOLD_2
  *         @arg @ref LL_FMAC_WM_2_THRESHOLD_4
  *         @arg @ref LL_FMAC_WM_3_THRESHOLD_8
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetX1FullWatermark(FMAC_TypeDef *FMACx, uint32_t Watermark)
{
  MODIFY_REG(FMACx->X1BUFCFG, FMAC_X1BUFCFG_FULL_WM, Watermark);
}

/**
  * @brief  Return X1 full watermark.
  * @rmtoll X1BUFCFG     FULL_WM       LL_FMAC_GetX1FullWatermark
  * @param  FMACx FMAC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FMAC_WM_0_THRESHOLD_1
  *         @arg @ref LL_FMAC_WM_1_THRESHOLD_2
  *         @arg @ref LL_FMAC_WM_2_THRESHOLD_4
  *         @arg @ref LL_FMAC_WM_3_THRESHOLD_8
  */
__STATIC_INLINE uint32_t LL_FMAC_GetX1FullWatermark(FMAC_TypeDef *FMACx)
{
  return (uint32_t)(READ_BIT(FMACx->X1BUFCFG, FMAC_X1BUFCFG_FULL_WM));
}

/**
  * @brief  Configure X1 buffer size.
  * @rmtoll X1BUFCFG     X1_BUF_SIZE   LL_FMAC_SetX1BufferSize
  * @param  FMACx FMAC instance
  * @param  BufferSize 0x01 .. 0xFF: Number of 16-bit addresses allocated to the input buffer (including the optional "headroom").
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetX1BufferSize(FMAC_TypeDef *FMACx, uint8_t BufferSize)
{
  MODIFY_REG(FMACx->X1BUFCFG, FMAC_X1BUFCFG_X1_BUF_SIZE, ((uint32_t)BufferSize) << FMAC_X1BUFCFG_X1_BUF_SIZE_Pos);
}

/**
  * @brief  Return X1 buffer size.
  * @rmtoll X1BUFCFG     X1_BUF_SIZE   LL_FMAC_GetX1BufferSize
  * @param  FMACx FMAC instance
  * @retval 0x01 .. 0xFF: Number of 16-bit addresses allocated to the input buffer (including the optional "headroom").
  */
__STATIC_INLINE uint8_t LL_FMAC_GetX1BufferSize(FMAC_TypeDef *FMACx)
{
  return (uint8_t)(READ_BIT(FMACx->X1BUFCFG, FMAC_X1BUFCFG_X1_BUF_SIZE) >> FMAC_X1BUFCFG_X1_BUF_SIZE_Pos);
}

/**
  * @brief  Configure X1 base.
  * @rmtoll X1BUFCFG     X1_BASE       LL_FMAC_SetX1Base
  * @param  FMACx FMAC instance
  * @param  Base 0x00 .. 0xFF: Base address of the input buffer (X1) within the internal memory.
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetX1Base(FMAC_TypeDef *FMACx, uint8_t Base)
{
  MODIFY_REG(FMACx->X1BUFCFG, FMAC_X1BUFCFG_X1_BASE, ((uint32_t)Base) << FMAC_X1BUFCFG_X1_BASE_Pos);
}

/**
  * @brief  Return X1 base.
  * @rmtoll X1BUFCFG     X1_BASE       LL_FMAC_GetX1Base
  * @param  FMACx FMAC instance
  * @retval 0x00 .. 0xFF: Base address of the input buffer (X1) within the internal memory.
  */
__STATIC_INLINE uint8_t LL_FMAC_GetX1Base(FMAC_TypeDef *FMACx)
{
  return (uint8_t)(READ_BIT(FMACx->X1BUFCFG, FMAC_X1BUFCFG_X1_BASE) >> FMAC_X1BUFCFG_X1_BASE_Pos);
}

/**
  * @brief  Configure X2 buffer size.
  * @rmtoll X2BUFCFG     X2_BUF_SIZE   LL_FMAC_SetX2BufferSize
  * @param  FMACx FMAC instance
  * @param  BufferSize 0x01 .. 0xFF: Number of 16-bit addresses allocated to the coefficient buffer.
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetX2BufferSize(FMAC_TypeDef *FMACx, uint8_t BufferSize)
{
  MODIFY_REG(FMACx->X2BUFCFG, FMAC_X2BUFCFG_X2_BUF_SIZE, ((uint32_t)BufferSize) << FMAC_X2BUFCFG_X2_BUF_SIZE_Pos);
}

/**
  * @brief  Return X2 buffer size.
  * @rmtoll X2BUFCFG     X2_BUF_SIZE   LL_FMAC_GetX2BufferSize
  * @param  FMACx FMAC instance
  * @retval 0x01 .. 0xFF: Number of 16-bit addresses allocated to the coefficient buffer.
  */
__STATIC_INLINE uint8_t LL_FMAC_GetX2BufferSize(FMAC_TypeDef *FMACx)
{
  return (uint8_t)(READ_BIT(FMACx->X2BUFCFG, FMAC_X2BUFCFG_X2_BUF_SIZE) >> FMAC_X2BUFCFG_X2_BUF_SIZE_Pos);
}

/**
  * @brief  Configure X2 base.
  * @rmtoll X2BUFCFG     X2_BASE       LL_FMAC_SetX2Base
  * @param  FMACx FMAC instance
  * @param  Base 0x00 .. 0xFF: Base address of the coefficient buffer (X2) within the internal memory.
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetX2Base(FMAC_TypeDef *FMACx, uint8_t Base)
{
  MODIFY_REG(FMACx->X2BUFCFG, FMAC_X2BUFCFG_X2_BASE, ((uint32_t)Base) << FMAC_X2BUFCFG_X2_BASE_Pos);
}

/**
  * @brief  Return X2 base.
  * @rmtoll X2BUFCFG     X2_BASE       LL_FMAC_GetX2Base
  * @param  FMACx FMAC instance
  * @retval 0x00 .. 0xFF: Base address of the coefficient buffer (X2) within the internal memory.
  */
__STATIC_INLINE uint8_t LL_FMAC_GetX2Base(FMAC_TypeDef *FMACx)
{
  return (uint8_t)(READ_BIT(FMACx->X2BUFCFG, FMAC_X2BUFCFG_X2_BASE) >> FMAC_X2BUFCFG_X2_BASE_Pos);
}

/**
  * @brief  Configure Y empty watermark.
  * @rmtoll YBUFCFG      EMPTY_WM      LL_FMAC_SetYEmptyWatermark
  * @param  FMACx FMAC instance
  * @param  Watermark This parameter can be one of the following values:
  *         @arg @ref LL_FMAC_WM_0_THRESHOLD_1
  *         @arg @ref LL_FMAC_WM_1_THRESHOLD_2
  *         @arg @ref LL_FMAC_WM_2_THRESHOLD_4
  *         @arg @ref LL_FMAC_WM_3_THRESHOLD_8
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetYEmptyWatermark(FMAC_TypeDef *FMACx, uint32_t Watermark)
{
  MODIFY_REG(FMACx->YBUFCFG, FMAC_YBUFCFG_EMPTY_WM, Watermark);
}

/**
  * @brief  Return Y empty watermark.
  * @rmtoll YBUFCFG      EMPTY_WM      LL_FMAC_GetYEmptyWatermark
  * @param  FMACx FMAC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FMAC_WM_0_THRESHOLD_1
  *         @arg @ref LL_FMAC_WM_1_THRESHOLD_2
  *         @arg @ref LL_FMAC_WM_2_THRESHOLD_4
  *         @arg @ref LL_FMAC_WM_3_THRESHOLD_8
  */
__STATIC_INLINE uint32_t LL_FMAC_GetYEmptyWatermark(FMAC_TypeDef *FMACx)
{
  return (uint32_t)(READ_BIT(FMACx->YBUFCFG, FMAC_YBUFCFG_EMPTY_WM));
}

/**
  * @brief  Configure Y buffer size.
  * @rmtoll YBUFCFG      Y_BUF_SIZE    LL_FMAC_SetYBufferSize
  * @param  FMACx FMAC instance
  * @param  BufferSize 0x01 .. 0xFF: Number of 16-bit addresses allocated to the output buffer (including the optional "headroom").
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetYBufferSize(FMAC_TypeDef *FMACx, uint8_t BufferSize)
{
  MODIFY_REG(FMACx->YBUFCFG, FMAC_YBUFCFG_Y_BUF_SIZE, ((uint32_t)BufferSize) << FMAC_YBUFCFG_Y_BUF_SIZE_Pos);
}

/**
  * @brief  Return Y buffer size.
  * @rmtoll YBUFCFG      Y_BUF_SIZE    LL_FMAC_GetYBufferSize
  * @param  FMACx FMAC instance
  * @retval 0x01 .. 0xFF: Number of 16-bit addresses allocated to the output buffer (including the optional "headroom").
  */
__STATIC_INLINE uint8_t LL_FMAC_GetYBufferSize(FMAC_TypeDef *FMACx)
{
  return (uint8_t)(READ_BIT(FMACx->YBUFCFG, FMAC_YBUFCFG_Y_BUF_SIZE) >> FMAC_YBUFCFG_Y_BUF_SIZE_Pos);
}

/**
  * @brief  Configure Y base.
  * @rmtoll YBUFCFG      Y_BASE        LL_FMAC_SetYBase
  * @param  FMACx FMAC instance
  * @param  Base 0x00 .. 0xFF: Base address of the output buffer (Y) within the internal memory.
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetYBase(FMAC_TypeDef *FMACx, uint8_t Base)
{
  MODIFY_REG(FMACx->YBUFCFG, FMAC_YBUFCFG_Y_BASE, ((uint32_t)Base) << FMAC_YBUFCFG_Y_BASE_Pos);
}

/**
  * @brief  Return Y base.
  * @rmtoll YBUFCFG      Y_BASE        LL_FMAC_GetYBase
  * @param  FMACx FMAC instance
  * @retval 0x00 .. 0xFF: Base address of the output buffer (Y) within the internal memory.
  */
__STATIC_INLINE uint8_t LL_FMAC_GetYBase(FMAC_TypeDef *FMACx)
{
  return (uint8_t)(READ_BIT(FMACx->YBUFCFG, FMAC_YBUFCFG_Y_BASE) >> FMAC_YBUFCFG_Y_BASE_Pos);
}

/**
  * @brief  Start FMAC processing.
  * @rmtoll PARAM        START         LL_FMAC_EnableStart
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableStart(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->PARAM, FMAC_PARAM_START);
}

/**
  * @brief  Stop FMAC processing.
  * @rmtoll PARAM        START         LL_FMAC_DisableStart
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableStart(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->PARAM, FMAC_PARAM_START);
}

/**
  * @brief  Check the state of FMAC processing.
  * @rmtoll PARAM        START         LL_FMAC_IsEnabledStart
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledStart(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->PARAM, FMAC_PARAM_START) == (FMAC_PARAM_START)) ? 1UL : 0UL);
}

/**
  * @brief  Configure function.
  * @rmtoll PARAM        FUNC          LL_FMAC_SetFunction
  * @param  FMACx FMAC instance
  * @param  Function This parameter can be one of the following values:
  *         @arg @ref LL_FMAC_FUNC_LOAD_X1
  *         @arg @ref LL_FMAC_FUNC_LOAD_X2
  *         @arg @ref LL_FMAC_FUNC_LOAD_Y
  *         @arg @ref LL_FMAC_FUNC_CONVO_FIR
  *         @arg @ref LL_FMAC_FUNC_IIR_DIRECT_FORM_1
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetFunction(FMAC_TypeDef *FMACx, uint32_t Function)
{
  MODIFY_REG(FMACx->PARAM, FMAC_PARAM_FUNC, Function);
}

/**
  * @brief  Return function.
  * @rmtoll PARAM        FUNC          LL_FMAC_GetFunction
  * @param  FMACx FMAC instance
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FMAC_FUNC_LOAD_X1
  *         @arg @ref LL_FMAC_FUNC_LOAD_X2
  *         @arg @ref LL_FMAC_FUNC_LOAD_Y
  *         @arg @ref LL_FMAC_FUNC_CONVO_FIR
  *         @arg @ref LL_FMAC_FUNC_IIR_DIRECT_FORM_1
  */
__STATIC_INLINE uint32_t LL_FMAC_GetFunction(FMAC_TypeDef *FMACx)
{
  return (uint32_t)(READ_BIT(FMACx->PARAM, FMAC_PARAM_FUNC));
}

/**
  * @brief  Configure input parameter R.
  * @rmtoll PARAM        R             LL_FMAC_SetParamR
  * @param  FMACx FMAC instance
  * @param  Param 0x00 .. 0xFF: Parameter R (gain, etc.).
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetParamR(FMAC_TypeDef *FMACx, uint8_t Param)
{
  MODIFY_REG(FMACx->PARAM, FMAC_PARAM_R, ((uint32_t)Param) << FMAC_PARAM_R_Pos);
}

/**
  * @brief  Return input parameter R.
  * @rmtoll PARAM        R             LL_FMAC_GetParamR
  * @param  FMACx FMAC instance
  * @retval 0x00 .. 0xFF: Parameter R (gain, etc.).
  */
__STATIC_INLINE uint8_t LL_FMAC_GetParamR(FMAC_TypeDef *FMACx)
{
  return (uint8_t)(READ_BIT(FMACx->PARAM, FMAC_PARAM_R) >> FMAC_PARAM_R_Pos);
}

/**
  * @brief  Configure input parameter Q.
  * @rmtoll PARAM        Q             LL_FMAC_SetParamQ
  * @param  FMACx FMAC instance
  * @param  Param 0x00 .. 0xFF: Parameter Q (vector length, etc.).
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetParamQ(FMAC_TypeDef *FMACx, uint8_t Param)
{
  MODIFY_REG(FMACx->PARAM, FMAC_PARAM_Q, ((uint32_t)Param) << FMAC_PARAM_Q_Pos);
}

/**
  * @brief  Return input parameter Q.
  * @rmtoll PARAM        Q             LL_FMAC_GetParamQ
  * @param  FMACx FMAC instance
  * @retval 0x00 .. 0xFF: Parameter Q (vector length, etc.).
  */
__STATIC_INLINE uint8_t LL_FMAC_GetParamQ(FMAC_TypeDef *FMACx)
{
  return (uint8_t)(READ_BIT(FMACx->PARAM, FMAC_PARAM_Q) >> FMAC_PARAM_Q_Pos);
}

/**
  * @brief  Configure input parameter P.
  * @rmtoll PARAM        P             LL_FMAC_SetParamP
  * @param  FMACx FMAC instance
  * @param  Param 0x00 .. 0xFF: Parameter P (vector length, number of filter taps, etc.).
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_SetParamP(FMAC_TypeDef *FMACx, uint8_t Param)
{
  MODIFY_REG(FMACx->PARAM, FMAC_PARAM_P, ((uint32_t)Param) << FMAC_PARAM_P_Pos);
}

/**
  * @brief  Return input parameter P.
  * @rmtoll PARAM        P             LL_FMAC_GetParamP
  * @param  FMACx FMAC instance
  * @retval 0x00 .. 0xFF: Parameter P (vector length, number of filter taps, etc.).
  */
__STATIC_INLINE uint8_t LL_FMAC_GetParamP(FMAC_TypeDef *FMACx)
{
  return (uint8_t)(READ_BIT(FMACx->PARAM, FMAC_PARAM_P) >> FMAC_PARAM_P_Pos);
}

/**
  * @}
  */

/** @defgroup FMAC_LL_EF_Reset_Management Reset_Management
  * @{
  */

/**
  * @brief  Start the FMAC reset.
  * @rmtoll CR           RESET         LL_FMAC_EnableReset
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableReset(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->CR, FMAC_CR_RESET);
}

/**
  * @brief  Interrupt the FMAC reset.
  * @rmtoll CR           RESET         LL_FMAC_DisableReset
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableReset(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->CR, FMAC_CR_RESET);
}

/**
  * @brief  Check the state of the FMAC reset.
  * @rmtoll CR           RESET         LL_FMAC_IsEnabledReset
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledReset(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->CR, FMAC_CR_RESET) == (FMAC_CR_RESET)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup FMAC_LL_EF_Configuration FMAC Configuration functions
  * @{
  */

/**
  * @brief  Enable Clipping.
  * @rmtoll CR           CLIPEN        LL_FMAC_EnableClipping
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableClipping(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->CR, FMAC_CR_CLIPEN);
}

/**
  * @brief  Disable Clipping.
  * @rmtoll CR           CLIPEN        LL_FMAC_DisableClipping
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableClipping(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->CR, FMAC_CR_CLIPEN);
}

/**
  * @brief  Check Clipping State.
  * @rmtoll CR           CLIPEN        LL_FMAC_IsEnabledClipping
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledClipping(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->CR, FMAC_CR_CLIPEN) == (FMAC_CR_CLIPEN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup FMAC_LL_EF_DMA_Management DMA_Management
  * @{
  */

/**
  * @brief  Enable FMAC DMA write channel request.
  * @rmtoll CR           DMAWEN        LL_FMAC_EnableDMAReq_WRITE
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableDMAReq_WRITE(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->CR, FMAC_CR_DMAWEN);
}

/**
  * @brief  Disable FMAC DMA write channel request.
  * @rmtoll CR           DMAWEN        LL_FMAC_DisableDMAReq_WRITE
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableDMAReq_WRITE(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->CR, FMAC_CR_DMAWEN);
}

/**
  * @brief  Check FMAC DMA write channel request state.
  * @rmtoll CR           DMAWEN        LL_FMAC_IsEnabledDMAReq_WRITE
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledDMAReq_WRITE(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->CR, FMAC_CR_DMAWEN) == (FMAC_CR_DMAWEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable FMAC DMA read channel request.
  * @rmtoll CR           DMAREN        LL_FMAC_EnableDMAReq_READ
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableDMAReq_READ(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->CR, FMAC_CR_DMAREN);
}

/**
  * @brief  Disable FMAC DMA read channel request.
  * @rmtoll CR           DMAREN        LL_FMAC_DisableDMAReq_READ
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableDMAReq_READ(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->CR, FMAC_CR_DMAREN);
}

/**
  * @brief  Check FMAC DMA read channel request state.
  * @rmtoll CR           DMAREN        LL_FMAC_IsEnabledDMAReq_READ
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledDMAReq_READ(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->CR, FMAC_CR_DMAREN) == (FMAC_CR_DMAREN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup FMAC_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable FMAC saturation error interrupt.
  * @rmtoll CR           SATIEN        LL_FMAC_EnableIT_SAT
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableIT_SAT(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->CR, FMAC_CR_SATIEN);
}

/**
  * @brief  Disable FMAC saturation error interrupt.
  * @rmtoll CR           SATIEN        LL_FMAC_DisableIT_SAT
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableIT_SAT(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->CR, FMAC_CR_SATIEN);
}

/**
  * @brief  Check FMAC saturation error interrupt state.
  * @rmtoll CR           SATIEN        LL_FMAC_IsEnabledIT_SAT
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledIT_SAT(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->CR, FMAC_CR_SATIEN) == (FMAC_CR_SATIEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable FMAC underflow error interrupt.
  * @rmtoll CR           UNFLIEN       LL_FMAC_EnableIT_UNFL
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableIT_UNFL(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->CR, FMAC_CR_UNFLIEN);
}

/**
  * @brief  Disable FMAC underflow error interrupt.
  * @rmtoll CR           UNFLIEN       LL_FMAC_DisableIT_UNFL
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableIT_UNFL(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->CR, FMAC_CR_UNFLIEN);
}

/**
  * @brief  Check FMAC underflow error interrupt state.
  * @rmtoll CR           UNFLIEN       LL_FMAC_IsEnabledIT_UNFL
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledIT_UNFL(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->CR, FMAC_CR_UNFLIEN) == (FMAC_CR_UNFLIEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable FMAC overflow error interrupt.
  * @rmtoll CR           OVFLIEN       LL_FMAC_EnableIT_OVFL
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableIT_OVFL(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->CR, FMAC_CR_OVFLIEN);
}

/**
  * @brief  Disable FMAC overflow error interrupt.
  * @rmtoll CR           OVFLIEN       LL_FMAC_DisableIT_OVFL
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableIT_OVFL(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->CR, FMAC_CR_OVFLIEN);
}

/**
  * @brief  Check FMAC overflow error interrupt state.
  * @rmtoll CR           OVFLIEN       LL_FMAC_IsEnabledIT_OVFL
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledIT_OVFL(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->CR, FMAC_CR_OVFLIEN) == (FMAC_CR_OVFLIEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable FMAC write interrupt.
  * @rmtoll CR           WIEN          LL_FMAC_EnableIT_WR
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableIT_WR(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->CR, FMAC_CR_WIEN);
}

/**
  * @brief  Disable FMAC write interrupt.
  * @rmtoll CR           WIEN          LL_FMAC_DisableIT_WR
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableIT_WR(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->CR, FMAC_CR_WIEN);
}

/**
  * @brief  Check FMAC write interrupt state.
  * @rmtoll CR           WIEN          LL_FMAC_IsEnabledIT_WR
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledIT_WR(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->CR, FMAC_CR_WIEN) == (FMAC_CR_WIEN)) ? 1UL : 0UL);
}

/**
  * @brief  Enable FMAC read interrupt.
  * @rmtoll CR           RIEN          LL_FMAC_EnableIT_RD
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_EnableIT_RD(FMAC_TypeDef *FMACx)
{
  SET_BIT(FMACx->CR, FMAC_CR_RIEN);
}

/**
  * @brief  Disable FMAC read interrupt.
  * @rmtoll CR           RIEN          LL_FMAC_DisableIT_RD
  * @param  FMACx FMAC instance
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_DisableIT_RD(FMAC_TypeDef *FMACx)
{
  CLEAR_BIT(FMACx->CR, FMAC_CR_RIEN);
}

/**
  * @brief  Check FMAC read interrupt state.
  * @rmtoll CR           RIEN          LL_FMAC_IsEnabledIT_RD
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsEnabledIT_RD(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->CR, FMAC_CR_RIEN) == (FMAC_CR_RIEN)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup FMAC_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Check FMAC saturation error flag state.
  * @rmtoll SR           SAT           LL_FMAC_IsActiveFlag_SAT
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsActiveFlag_SAT(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->SR, FMAC_SR_SAT) == (FMAC_SR_SAT)) ? 1UL : 0UL);
}

/**
  * @brief  Check FMAC underflow error flag state.
  * @rmtoll SR           UNFL          LL_FMAC_IsActiveFlag_UNFL
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsActiveFlag_UNFL(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->SR, FMAC_SR_UNFL) == (FMAC_SR_UNFL)) ? 1UL : 0UL);
}

/**
  * @brief  Check FMAC overflow error flag state.
  * @rmtoll SR           OVFL          LL_FMAC_IsActiveFlag_OVFL
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsActiveFlag_OVFL(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->SR, FMAC_SR_OVFL) == (FMAC_SR_OVFL)) ? 1UL : 0UL);
}

/**
  * @brief  Check FMAC X1 buffer full flag state.
  * @rmtoll SR           X1FULL        LL_FMAC_IsActiveFlag_X1FULL
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsActiveFlag_X1FULL(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->SR, FMAC_SR_X1FULL) == (FMAC_SR_X1FULL)) ? 1UL : 0UL);
}

/**
  * @brief  Check FMAC Y buffer empty flag state.
  * @rmtoll SR           YEMPTY        LL_FMAC_IsActiveFlag_YEMPTY
  * @param  FMACx FMAC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FMAC_IsActiveFlag_YEMPTY(FMAC_TypeDef *FMACx)
{
  return ((READ_BIT(FMACx->SR, FMAC_SR_YEMPTY) == (FMAC_SR_YEMPTY)) ? 1UL : 0UL);
}

/**
  * @}
  */

/** @defgroup FMAC_LL_EF_Data_Management Data_Management
  * @{
  */

/**
  * @brief  Write 16-bit input data for the FMAC processing.
  * @rmtoll WDATA        WDATA         LL_FMAC_WriteData
  * @param  FMACx FMAC instance
  * @param  InData 0x0000 .. 0xFFFF: 16-bit value to be provided as input data for FMAC processing.
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_WriteData(FMAC_TypeDef *FMACx, uint16_t InData)
{
  WRITE_REG(FMACx->WDATA, InData);
}

/**
  * @brief  Return 16-bit output data of FMAC processing.
  * @rmtoll RDATA        RDATA         LL_FMAC_ReadData
  * @param  FMACx FMAC instance
  * @retval 0x0000 .. 0xFFFF: 16-bit output data of FMAC processing.
  */
__STATIC_INLINE uint16_t LL_FMAC_ReadData(FMAC_TypeDef *FMACx)
{
  return (uint16_t)(READ_REG(FMACx->RDATA));
}

/**
  * @}
  */

/** @defgroup FMAC_LL_EF_Configuration FMAC Configuration functions
  * @{
  */

/**
  * @brief  Configure memory for X1 buffer.
  * @rmtoll X1BUFCFG     FULL_WM       LL_FMAC_ConfigX1\n
  *         X1BUFCFG     X1_BASE       LL_FMAC_ConfigX1\n
  *         X1BUFCFG     X1_BUF_SIZE   LL_FMAC_ConfigX1
  * @param  FMACx FMAC instance
  * @param  Watermark This parameter can be one of the following values:
  *         @arg @ref LL_FMAC_WM_0_THRESHOLD_1
  *         @arg @ref LL_FMAC_WM_1_THRESHOLD_2
  *         @arg @ref LL_FMAC_WM_2_THRESHOLD_4
  *         @arg @ref LL_FMAC_WM_3_THRESHOLD_8
  * @param  Base 0x00 .. 0xFF: Base address of the input buffer (X1) within the internal memory.
  * @param  BufferSize 0x01 .. 0xFF: Number of 16-bit addresses allocated to the input buffer (including the optional "headroom").
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_ConfigX1(FMAC_TypeDef *FMACx, uint32_t Watermark, uint8_t Base, uint8_t BufferSize)
{
  MODIFY_REG(FMACx->X1BUFCFG, FMAC_X1BUFCFG_FULL_WM | FMAC_X1BUFCFG_X1_BASE | FMAC_X1BUFCFG_X1_BUF_SIZE,
             Watermark | (((uint32_t)Base) << FMAC_X1BUFCFG_X1_BASE_Pos) | (((uint32_t)BufferSize) << FMAC_X1BUFCFG_X1_BUF_SIZE_Pos));
}

/**
  * @brief  Configure memory for X2 buffer.
  * @rmtoll X2BUFCFG     X2_BASE       LL_FMAC_ConfigX2\n
  *         X2BUFCFG     X2_BUF_SIZE   LL_FMAC_ConfigX2
  * @param  FMACx FMAC instance
  * @param  Base 0x00 .. 0xFF: Base address of the coefficient buffer (X2) within the internal memory.
  * @param  BufferSize 0x01 .. 0xFF: Number of 16-bit addresses allocated to the coefficient buffer.
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_ConfigX2(FMAC_TypeDef *FMACx, uint8_t Base, uint8_t BufferSize)
{
  MODIFY_REG(FMACx->X2BUFCFG, FMAC_X2BUFCFG_X2_BASE | FMAC_X2BUFCFG_X2_BUF_SIZE,
             (((uint32_t)Base) << FMAC_X2BUFCFG_X2_BASE_Pos) | (((uint32_t)BufferSize) << FMAC_X2BUFCFG_X2_BUF_SIZE_Pos));
}

/**
  * @brief  Configure memory for Y buffer.
  * @rmtoll YBUFCFG      EMPTY_WM      LL_FMAC_ConfigY\n
  *         YBUFCFG      Y_BASE        LL_FMAC_ConfigY\n
  *         YBUFCFG      Y_BUF_SIZE    LL_FMAC_ConfigY
  * @param  FMACx FMAC instance
  * @param  Watermark This parameter can be one of the following values:
  *         @arg @ref LL_FMAC_WM_0_THRESHOLD_1
  *         @arg @ref LL_FMAC_WM_1_THRESHOLD_2
  *         @arg @ref LL_FMAC_WM_2_THRESHOLD_4
  *         @arg @ref LL_FMAC_WM_3_THRESHOLD_8
  * @param  Base 0x00 .. 0xFF: Base address of the output buffer (Y) within the internal memory.
  * @param  BufferSize 0x01 .. 0xFF: Number of 16-bit addresses allocated to the output buffer (including the optional "headroom").
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_ConfigY(FMAC_TypeDef *FMACx, uint32_t Watermark, uint8_t Base, uint8_t BufferSize)
{
  MODIFY_REG(FMACx->YBUFCFG, FMAC_YBUFCFG_EMPTY_WM | FMAC_YBUFCFG_Y_BASE | FMAC_YBUFCFG_Y_BUF_SIZE,
             Watermark | (((uint32_t)Base) << FMAC_YBUFCFG_Y_BASE_Pos) | (((uint32_t)BufferSize) << FMAC_YBUFCFG_Y_BUF_SIZE_Pos));
}

/**
  * @brief  Configure the FMAC processing.
  * @rmtoll PARAM        START         LL_FMAC_ConfigFunc\n
  *         PARAM        FUNC          LL_FMAC_ConfigFunc\n
  *         PARAM        P             LL_FMAC_ConfigFunc\n
  *         PARAM        Q             LL_FMAC_ConfigFunc\n
  *         PARAM        R             LL_FMAC_ConfigFunc
  * @param  FMACx FMAC instance
  * @param  Start 0x00 .. 0x01: Enable or disable FMAC processing.
  * @param  Function This parameter can be one of the following values:
  *         @arg @ref LL_FMAC_FUNC_LOAD_X1
  *         @arg @ref LL_FMAC_FUNC_LOAD_X2
  *         @arg @ref LL_FMAC_FUNC_LOAD_Y
  *         @arg @ref LL_FMAC_FUNC_CONVO_FIR
  *         @arg @ref LL_FMAC_FUNC_IIR_DIRECT_FORM_1
  * @param  ParamP 0x00 .. 0xFF: Parameter P (vector length, number of filter taps, etc.).
  * @param  ParamQ 0x00 .. 0xFF: Parameter Q (vector length, etc.).
  * @param  ParamR 0x00 .. 0xFF: Parameter R (gain, etc.).
  * @retval None
  */
__STATIC_INLINE void LL_FMAC_ConfigFunc(FMAC_TypeDef *FMACx, uint8_t Start, uint32_t Function, uint8_t ParamP,
                                        uint8_t ParamQ, uint8_t ParamR)
{
  MODIFY_REG(FMACx->PARAM, FMAC_PARAM_START | FMAC_PARAM_FUNC | FMAC_PARAM_P | FMAC_PARAM_Q | FMAC_PARAM_R,
             (((uint32_t)Start) << FMAC_PARAM_START_Pos) | Function | (((uint32_t)ParamP) << FMAC_PARAM_P_Pos) | (((uint32_t)ParamQ) << FMAC_PARAM_Q_Pos) | (((uint32_t)ParamR) << FMAC_PARAM_R_Pos));
}

/**
  * @}
  */



#if defined(USE_FULL_LL_DRIVER)
/** @defgroup FMAC_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_FMAC_Init(FMAC_TypeDef *FMACx);
ErrorStatus LL_FMAC_DeInit(FMAC_TypeDef *FMACx);


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

#endif /* defined(FMAC) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32G4xx_LL_FMAC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
