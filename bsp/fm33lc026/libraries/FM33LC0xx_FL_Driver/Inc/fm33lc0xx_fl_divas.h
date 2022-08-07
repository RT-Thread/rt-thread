/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_divas.h
  * @author  FMSH Application Team
  * @brief   Head file of DIVAS FL Module
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
#ifndef __FM33LC0XX_FL_DIVAS_H
#define __FM33LC0XX_FL_DIVAS_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup DIVAS DIVAS
  * @brief DIVAS FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup DIVAS_FL_ES_INIT DIVAS Exported Init structures
  * @{
  */

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup DIVAS_FL_Exported_Constants DIVAS Exported Constants
  * @{
  */

#define    DIV_SR_DIVBYZERO_Pos                                   (1U)
#define    DIV_SR_DIVBYZERO_Msk                                   (0x1U << DIV_SR_DIVBYZERO_Pos)
#define    DIV_SR_DIVBYZERO                                       DIV_SR_DIVBYZERO_Msk

#define    DIV_SR_BUSY_Pos                                        (0U)
#define    DIV_SR_BUSY_Msk                                        (0x1U << DIV_SR_BUSY_Pos)
#define    DIV_SR_BUSY                                            DIV_SR_BUSY_Msk



#define    FL_DIVAS_SR_BUSY_TIMEOUT                               0xFFFU



/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup DIVAS_FL_Exported_Functions DIVAS Exported Functions
  * @{
  */

/**
  * @brief    Write Dividend Register
  * @rmtoll   OPRD        FL_DIV_WriteDividend_S32
  * @param    DIVx DIV instance
  * @param    number
  * @retval   None
  */
__STATIC_INLINE void FL_DIV_WriteDividend_S32(DIV_Type *DIVx, int32_t number)
{
    MODIFY_REG(DIVx->END, (0xffffffffU << 0U), (number << 0U));
}

/**
  * @brief    Read Dividend Register
  * @rmtoll   OPRD        FL_DIV_ReadDividend_S32
  * @param    DIVx DIV instance
  * @retval
  */
__STATIC_INLINE int32_t FL_DIV_ReadDividend_S32(DIV_Type *DIVx)
{
    return (uint32_t)(READ_BIT(DIVx->END, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Write 16bit Signed Divisor
  * @rmtoll   DIVSOR        FL_DIV_WriteDivisor_S16
  * @param    DIVx DIV instance
  * @param    number
  * @retval   None
  */
__STATIC_INLINE void FL_DIV_WriteDivisor_S16(DIV_Type *DIVx, int16_t number)
{
    MODIFY_REG(DIVx->SOR, (0xffffU << 0U), (number << 0U));
}

/**
  * @brief    Read 16bit Signed Divisor
  * @rmtoll   DIVSOR        FL_DIV_ReadDivisor_S16
  * @param    DIVx DIV instance
  * @retval
  */
__STATIC_INLINE int32_t FL_DIV_ReadDivisor_S16(DIV_Type *DIVx)
{
    return (uint32_t)(READ_BIT(DIVx->SOR, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Read 32bit Signed QUTO
  * @rmtoll   QUOT        FL_DIV_ReadQuotient_S32
  * @param    DIVx DIV instance
  * @retval
  */
__STATIC_INLINE int32_t FL_DIV_ReadQuotient_S32(DIV_Type *DIVx)
{
    return (uint32_t)(READ_BIT(DIVx->QUOT, (0xffffffffU << 0U)) >> 0U);
}

/**
  * @brief    Read 16bit Signed Reminder
  * @rmtoll   REMD        FL_DIV_ReadResidue_S16
  * @param    DIVx DIV instance
  * @retval
  */
__STATIC_INLINE int32_t FL_DIV_ReadResidue_S16(DIV_Type *DIVx)
{
    return (uint32_t)(READ_BIT(DIVx->REMD, (0xffffU << 0U)) >> 0U);
}

/**
  * @brief    Get divided by 0 flag
  * @rmtoll   SR    DIVBYZERO    FL_DIV_IsActiveFlag_DividedZero
  * @param    DIVx DIV instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DIV_IsActiveFlag_DividedZero(DIV_Type *DIVx)
{
    return (uint32_t)(READ_BIT(DIVx->SR, DIV_SR_DIVBYZERO_Msk) == (DIV_SR_DIVBYZERO_Msk));
}

/**
  * @brief    Get Busy flag
  * @rmtoll   SR    BUSY    FL_DIV_IsActiveFlag_Busy
  * @param    DIVx DIV instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DIV_IsActiveFlag_Busy(DIV_Type *DIVx)
{
    return (uint32_t)(READ_BIT(DIVx->SR, DIV_SR_BUSY_Msk) == (DIV_SR_BUSY_Msk));
}

/**
  * @}
  */

/** @defgroup DIVAS_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus FL_DIVAS_DeInit(DIV_Type *DIVx);
FL_ErrorStatus FL_DIVAS_Init(DIV_Type *DIVx);

/**
  * @}
  */

/** @defgroup DIVAS_FL_EF_Operation Opeartion functions
  * @{
  */

uint32_t FL_DIVAS_Hdiv_Calculation(DIV_Type *DIVx, int32_t DivisorEnd, int16_t Divisor, int32_t *Quotient, int16_t *Residue);

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

#endif /* __FM33LC0XX_FL_DIVAS_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-23*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
