/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_crc.h
  * @author  FMSH Application Team
  * @brief   Head file of CRC FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LC0XX_FL_CRC_H
#define __FM33LC0XX_FL_CRC_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup CRC CRC
  * @brief CRC FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup CRC_FL_ES_INIT CRC Exported Init structures
  * @{
  */

/**
  * @brief FL CRC Init Sturcture definition
  */
typedef struct
{
    /** CRC初值 */
    uint32_t initVal;

    /** 计算数据宽度 */
    uint32_t dataWidth;

    /** 输入数据翻转 */
    uint32_t reflectIn;

    /** 输出数据翻转 */
    uint32_t reflectOut;

    /** 输出结果异或寄存器 */
    uint32_t xorReg;

    /** 输出结果异或使能 */
    uint32_t xorRegState;

    /** CRC多项式宽 */
    uint32_t polynomialWidth;

    /** CRC多项式 */
    uint32_t polynomial;

    /** 计算模式串行或并行 */
    uint32_t calculatMode;

} FL_CRC_InitTypeDef;

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup CRC_FL_Exported_Constants CRC Exported Constants
  * @{
  */

#define    CRC_CR_OPWD_Pos                                        (9U)
#define    CRC_CR_OPWD_Msk                                        (0x1U << CRC_CR_OPWD_Pos)
#define    CRC_CR_OPWD                                            CRC_CR_OPWD_Msk

#define    CRC_CR_PARA_Pos                                        (8U)
#define    CRC_CR_PARA_Msk                                        (0x1U << CRC_CR_PARA_Pos)
#define    CRC_CR_PARA                                            CRC_CR_PARA_Msk

#define    CRC_CR_RFLTIN_Pos                                      (6U)
#define    CRC_CR_RFLTIN_Msk                                      (0x3U << CRC_CR_RFLTIN_Pos)
#define    CRC_CR_RFLTIN                                          CRC_CR_RFLTIN_Msk

#define    CRC_CR_RFLTO_Pos                                       (5U)
#define    CRC_CR_RFLTO_Msk                                       (0x1U << CRC_CR_RFLTO_Pos)
#define    CRC_CR_RFLTO                                           CRC_CR_RFLTO_Msk

#define    CRC_CR_RES_Pos                                         (4U)
#define    CRC_CR_RES_Msk                                         (0x1U << CRC_CR_RES_Pos)
#define    CRC_CR_RES                                             CRC_CR_RES_Msk

#define    CRC_CR_BUSY_Pos                                        (3U)
#define    CRC_CR_BUSY_Msk                                        (0x1U << CRC_CR_BUSY_Pos)
#define    CRC_CR_BUSY                                            CRC_CR_BUSY_Msk

#define    CRC_CR_XOR_Pos                                         (2U)
#define    CRC_CR_XOR_Msk                                         (0x1U << CRC_CR_XOR_Pos)
#define    CRC_CR_XOR                                             CRC_CR_XOR_Msk

#define    CRC_CR_SEL_Pos                                         (0U)
#define    CRC_CR_SEL_Msk                                         (0x3U << CRC_CR_SEL_Pos)
#define    CRC_CR_SEL                                             CRC_CR_SEL_Msk


#define    FL_CRC_DATA_WIDTH_8B                                   (0x0U << CRC_CR_OPWD_Pos)
#define    FL_CRC_DATA_WIDTH_32B                                  (0x1U << CRC_CR_OPWD_Pos)


#define    FL_CRC_CALCULATE_SERIAL                                (0x0U << CRC_CR_PARA_Pos)
#define    FL_CRC_CALCULATE_PARALLEL                              (0x1U << CRC_CR_PARA_Pos)


#define    FL_CRC_INPUT_INVERT_NONE                               (0x0U << CRC_CR_RFLTIN_Pos)
#define    FL_CRC_INPUT_INVERT_BYTE                               (0x1U << CRC_CR_RFLTIN_Pos)
#define    FL_CRC_INPUT_INVERT_HALF_WORD                          (0x2U << CRC_CR_RFLTIN_Pos)
#define    FL_CRC_INPUT_INVERT_WORD                               (0x3U << CRC_CR_RFLTIN_Pos)


#define    FL_CRC_OUPUT_INVERT_NONE                               (0x0U << CRC_CR_RFLTO_Pos)
#define    FL_CRC_OUPUT_INVERT_BYTE                               (0x1U << CRC_CR_RFLTO_Pos)


#define    FL_CRC_POLYNOMIAL_32B                                  (0x0U << CRC_CR_SEL_Pos)
#define    FL_CRC_POLYNOMIAL_16B                                  (0x1U << CRC_CR_SEL_Pos)
#define    FL_CRC_POLYNOMIAL_8B                                   (0x2U << CRC_CR_SEL_Pos)
#define    FL_CRC_POLYNOMIAL_7B                                   (0x3U << CRC_CR_SEL_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup CRC_FL_Exported_Functions CRC Exported Functions
  * @{
  */

/**
  * @brief    Set CRC data register
  * @rmtoll   DR        FL_CRC_WriteData
  * @param    CRCx CRC instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_WriteData(CRC_Type *CRCx, uint32_t data)
{
    MODIFY_REG(CRCx->DR, (0xffffffffU << 0U), (data << 0U));
}

/**
  * @brief    Get CRC data register value
  * @rmtoll   DR        FL_CRC_ReadData
  * @param    CRCx CRC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CRC_ReadData(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->DR, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Set CRC calculate operation width
  * @rmtoll   CR    OPWD    FL_CRC_SetDataWidth
  * @param    CRCx CRC instance
  * @param    dataWidth This parameter can be one of the following values:
  *           @arg @ref FL_CRC_DATA_WIDTH_8B
  *           @arg @ref FL_CRC_DATA_WIDTH_32B
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_SetDataWidth(CRC_Type *CRCx, uint32_t dataWidth)
{
    MODIFY_REG(CRCx->CR, CRC_CR_OPWD_Msk, dataWidth);
}

/**
  * @brief    Get CRC calculate operation width
  * @rmtoll   CR    OPWD    FL_CRC_GetDataWidth
  * @param    CRCx CRC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CRC_DATA_WIDTH_8B
  *           @arg @ref FL_CRC_DATA_WIDTH_32B
  */
__STATIC_INLINE uint32_t FL_CRC_GetDataWidth(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_OPWD_Msk));
}

/**
  * @brief    Set CRC parallel calculation mode
  * @rmtoll   CR    PARA    FL_CRC_SetCalculateMode
  * @param    CRCx CRC instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_CRC_CALCULATE_SERIAL
  *           @arg @ref FL_CRC_CALCULATE_PARALLEL
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_SetCalculateMode(CRC_Type *CRCx, uint32_t mode)
{
    MODIFY_REG(CRCx->CR, CRC_CR_PARA_Msk, mode);
}

/**
  * @brief    Get CRC parallel calculation mode
  * @rmtoll   CR    PARA    FL_CRC_GetCalculateMode
  * @param    CRCx CRC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CRC_CALCULATE_SERIAL
  *           @arg @ref FL_CRC_CALCULATE_PARALLEL
  */
__STATIC_INLINE uint32_t FL_CRC_GetCalculateMode(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_PARA_Msk));
}

/**
  * @brief    Set CRC reflected input
  * @rmtoll   CR    RFLTIN    FL_CRC_SetInputInvertMode
  * @param    CRCx CRC instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_CRC_INPUT_INVERT_NONE
  *           @arg @ref FL_CRC_INPUT_INVERT_BYTE
  *           @arg @ref FL_CRC_INPUT_INVERT_HALF_WORD
  *           @arg @ref FL_CRC_INPUT_INVERT_WORD
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_SetInputInvertMode(CRC_Type *CRCx, uint32_t mode)
{
    MODIFY_REG(CRCx->CR, CRC_CR_RFLTIN_Msk, mode);
}

/**
  * @brief    Get CRC reflected input status
  * @rmtoll   CR    RFLTIN    FL_CRC_GetInputInvertMode
  * @param    CRCx CRC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CRC_INPUT_INVERT_NONE
  *           @arg @ref FL_CRC_INPUT_INVERT_BYTE
  *           @arg @ref FL_CRC_INPUT_INVERT_HALF_WORD
  *           @arg @ref FL_CRC_INPUT_INVERT_WORD
  */
__STATIC_INLINE uint32_t FL_CRC_GetInputInvertMode(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_RFLTIN_Msk));
}

/**
  * @brief    Set CRC reflected output
  * @rmtoll   CR    RFLTO    FL_CRC_SetOutputInvertMode
  * @param    CRCx CRC instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_CRC_OUPUT_INVERT_NONE
  *           @arg @ref FL_CRC_OUPUT_INVERT_BYTE
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_SetOutputInvertMode(CRC_Type *CRCx, uint32_t mode)
{
    MODIFY_REG(CRCx->CR, CRC_CR_RFLTO_Msk, mode);
}

/**
  * @brief    Get CRC feflected output status
  * @rmtoll   CR    RFLTO    FL_CRC_GetOutputInvertMode
  * @param    CRCx CRC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CRC_OUPUT_INVERT_NONE
  *           @arg @ref FL_CRC_OUPUT_INVERT_BYTE
  */
__STATIC_INLINE uint32_t FL_CRC_GetOutputInvertMode(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_RFLTO_Msk));
}

/**
  * @brief    Get CRC result flag
  * @rmtoll   CR    RES    FL_CRC_IsActiveFlag_Zero
  * @param    CRCx CRC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CRC_IsActiveFlag_Zero(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_RES_Msk) == (CRC_CR_RES_Msk));
}

/**
  * @brief    Get CRC operational flag
  * @rmtoll   CR    BUSY    FL_CRC_IsActiveFlag_Busy
  * @param    CRCx CRC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CRC_IsActiveFlag_Busy(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_BUSY_Msk) == (CRC_CR_BUSY_Msk));
}

/**
  * @brief    Output XORed with CRC_XOR register enable
  * @rmtoll   CR    XOR    FL_CRC_EnableOutputXOR
  * @param    CRCx CRC instance
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_EnableOutputXOR(CRC_Type *CRCx)
{
    SET_BIT(CRCx->CR, CRC_CR_XOR_Msk);
}

/**
  * @brief    Get output XORed with CRC_XOR register enable status
  * @rmtoll   CR    XOR    FL_CRC_IsEnabledOutputXOR
  * @param    CRCx CRC instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_CRC_IsEnabledOutputXOR(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_XOR_Msk) == CRC_CR_XOR_Msk);
}

/**
  * @brief    Output XORed with CRC_XOR register disable
  * @rmtoll   CR    XOR    FL_CRC_DisableOutputXOR
  * @param    CRCx CRC instance
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_DisableOutputXOR(CRC_Type *CRCx)
{
    CLEAR_BIT(CRCx->CR, CRC_CR_XOR_Msk);
}

/**
  * @brief    Polynomial width selection
  * @rmtoll   CR    SEL    FL_CRC_SetPolynomialWidth
  * @param    CRCx CRC instance
  * @param    width This parameter can be one of the following values:
  *           @arg @ref FL_CRC_POLYNOMIAL_32B
  *           @arg @ref FL_CRC_POLYNOMIAL_16B
  *           @arg @ref FL_CRC_POLYNOMIAL_8B
  *           @arg @ref FL_CRC_POLYNOMIAL_7B
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_SetPolynomialWidth(CRC_Type *CRCx, uint32_t width)
{
    MODIFY_REG(CRCx->CR, CRC_CR_SEL_Msk, width);
}

/**
  * @brief    Get Polynomial width Selection status
  * @rmtoll   CR    SEL    FL_CRC_GetPolynomialWidth
  * @param    CRCx CRC instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_CRC_POLYNOMIAL_32B
  *           @arg @ref FL_CRC_POLYNOMIAL_16B
  *           @arg @ref FL_CRC_POLYNOMIAL_8B
  *           @arg @ref FL_CRC_POLYNOMIAL_7B
  */
__STATIC_INLINE uint32_t FL_CRC_GetPolynomialWidth(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->CR, CRC_CR_SEL_Msk));
}

/**
  * @brief    Set linear feedback shift register
  * @rmtoll   LFSR        FL_CRC_WriteInitialValue
  * @param    CRCx CRC instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_WriteInitialValue(CRC_Type *CRCx, uint32_t data)
{
    MODIFY_REG(CRCx->LFSR, (0xffffffffU << 0U), (data << 0U));
}

/**
  * @brief    Get linear feedback shift register value
  * @rmtoll   LFSR        FL_CRC_ReadInitialValue
  * @param    CRCx CRC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CRC_ReadInitialValue(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->LFSR, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Set eXclusive XOR register
  * @rmtoll   XOR        FL_CRC_WriteXORValue
  * @param    CRCx CRC instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_WriteXORValue(CRC_Type *CRCx, uint32_t data)
{
    MODIFY_REG(CRCx->XOR, (0xffffffffU << 0U), (data << 0U));
}

/**
  * @brief    Get eXclusive XOR register value
  * @rmtoll   XOR        FL_CRC_ReadXORValue
  * @param    CRCx CRC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CRC_ReadXORValue(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->XOR, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Set CRC Polynominals
  * @rmtoll   POLY        FL_CRC_WritePolynominalParam
  * @param    CRCx CRC instance
  * @param    data
  * @retval   None
  */
__STATIC_INLINE void FL_CRC_WritePolynominalParam(CRC_Type *CRCx, uint32_t data)
{
    MODIFY_REG(CRCx->POLY, (0xffffffffU << 0U), (data << 0U));
}

/**
  * @brief    Get CRC Polynominals
  * @rmtoll   POLY        FL_CRC_ReadPolynominalParam
  * @param    CRCx CRC instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_CRC_ReadPolynominalParam(CRC_Type *CRCx)
{
    return (uint32_t)(READ_BIT(CRCx->POLY, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @}
  */

/** @defgroup CRC_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_CRC_DeInit(CRC_Type *CRCx);
void FL_CRC_StructInit(FL_CRC_InitTypeDef *CRC_InitStruct);
FL_ErrorStatus FL_CRC_Init(CRC_Type *CRCx, FL_CRC_InitTypeDef *CRC_InitStruct);

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

#endif /* __FM33LC0XX_FL_CRC_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-23*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
