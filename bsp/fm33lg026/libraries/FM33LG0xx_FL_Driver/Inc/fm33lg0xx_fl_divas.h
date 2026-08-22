/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_divas.h
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
#ifndef __FM33LG0XX_FL_DIVAS_H
#define __FM33LG0XX_FL_DIVAS_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
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
  * @brief FL DIVAS Init Sturcture definition
  */

/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup DIVAS_FL_Exported_Constants DIVAS Exported Constants
  * @{
  */
#define    FL_DIVAS_SR_BUSY_TIMEOUT                                (0xFFFU)

#define    DIVAS_SR_DIV0_Pos                                      (1U)
#define    DIVAS_SR_DIV0_Msk                                      (0x1U << DIVAS_SR_DIV0_Pos)
#define    DIVAS_SR_DIV0                                          DIVAS_SR_DIV0_Msk

#define    DIVAS_SR_BUSY_Pos                                      (0U)
#define    DIVAS_SR_BUSY_Msk                                      (0x1U << DIVAS_SR_BUSY_Pos)
#define    DIVAS_SR_BUSY                                          DIVAS_SR_BUSY_Msk

#define    DIVAS_CR_MODE_Pos                                      (0U)
#define    DIVAS_CR_MODE_Msk                                      (0x1U << DIVAS_CR_MODE_Pos)
#define    DIVAS_CR_MODE                                          DIVAS_CR_MODE_Msk






#define    FL_DIVAS_MODE_DIV                                      (0x0U << DIVAS_CR_MODE_Pos)
#define    FL_DIVAS_MODE_ROOT                                     (0x1U << DIVAS_CR_MODE_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup DIVAS_FL_Exported_Functions DIVAS Exported Functions
  * @{
  */

/**
  * @brief    Write Operator Register
  * @rmtoll   OPRD        FL_DIVAS_WriteOperand
  * @param    DIVASx DIVAS instance
  * @param    number
  * @retval   None
  */
__STATIC_INLINE void FL_DIVAS_WriteOperand(DIVAS_Type *DIVASx, uint32_t number)
{
    WRITE_REG(DIVASx->OPRD, (number << 0U));
}

/**
  * @brief    Read Operator Register
  * @rmtoll   OPRD        FL_DIVAS_ReadOperand
  * @param    DIVASx DIVAS instance
  * @retval
  */
__STATIC_INLINE int32_t FL_DIVAS_ReadOperand(DIVAS_Type *DIVASx)
{
    return (int32_t)(READ_REG(DIVASx->OPRD));
}

/**
  * @brief    Write 16bit Signed Dividend
  * @rmtoll   DIVSOR        FL_DIVAS_WriteDivisor
  * @param    DIVASx DIVAS instance
  * @param    number
  * @retval   None
  */
__STATIC_INLINE void FL_DIVAS_WriteDivisor(DIVAS_Type *DIVASx, uint32_t number)
{
    MODIFY_REG(DIVASx->DIVSOR, (0xffffU << 0U), (number << 0U));
}

/**
  * @brief    Read 16bit Signed Dividend
  * @rmtoll   DIVSOR        FL_DIVAS_ReadDivisor
  * @param    DIVASx DIVAS instance
  * @retval
  */
__STATIC_INLINE int32_t FL_DIVAS_ReadDivisor(DIVAS_Type *DIVASx)
{
    return (int32_t)(READ_BIT(DIVASx->DIVSOR, 0xffffU) >> 0U);
}

/**
  * @brief    Read 32bit Signed QUTO
  * @rmtoll   QUOT        FL_DIVAS_ReadQuotient
  * @param    DIVASx DIVAS instance
  * @retval
  */
__STATIC_INLINE int32_t FL_DIVAS_ReadQuotient(DIVAS_Type *DIVASx)
{
    return (int32_t)(READ_REG(DIVASx->QUOT));
}

/**
  * @brief    Read 16bit Signed Reminder
  * @rmtoll   REMD        FL_DIVAS_ReadResidue
  * @param    DIVASx DIVAS instance
  * @retval
  */
__STATIC_INLINE int16_t FL_DIVAS_ReadResidue(DIVAS_Type *DIVASx)
{
    return (int16_t)(READ_BIT(DIVASx->REMD, 0xffffU) >> 0U);
}

/**
  * @brief    Read 16bit Unsigned Square Root
  * @rmtoll   ROOT        FL_DIVAS_ReadRoot
  * @param    DIVASx DIVAS instance
  * @retval
  */
__STATIC_INLINE uint16_t FL_DIVAS_ReadRoot(DIVAS_Type *DIVASx)
{
    return (uint16_t)(READ_BIT(DIVASx->ROOT, 0xffffU) >> 0U);
}

/**
  * @brief    Get divided by 0 flag
  * @rmtoll   SR    DIV0    FL_DIVAS_IsActiveFlag_DividedZero
  * @param    DIVASx DIVAS instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DIVAS_IsActiveFlag_DividedZero(DIVAS_Type *DIVASx)
{
    return (uint32_t)(READ_BIT(DIVASx->SR, DIVAS_SR_DIV0_Msk) == (DIVAS_SR_DIV0_Msk));
}

/**
  * @brief    Get Busy flag
  * @rmtoll   SR    BUSY    FL_DIVAS_IsActiveFlag_Busy
  * @param    DIVASx DIVAS instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_DIVAS_IsActiveFlag_Busy(DIVAS_Type *DIVASx)
{
    return (uint32_t)(READ_BIT(DIVASx->SR, DIVAS_SR_BUSY_Msk) == (DIVAS_SR_BUSY_Msk));
}

/**
  * @brief    Set Work Mode
  * @rmtoll   CR    MODE    FL_DIVAS_SetMode
  * @param    DIVASx DIVAS instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_DIVAS_MODE_DIV
  *           @arg @ref FL_DIVAS_MODE_ROOT
  * @retval   None
  */
__STATIC_INLINE void FL_DIVAS_SetMode(DIVAS_Type *DIVASx, uint32_t mode)
{
    MODIFY_REG(DIVASx->CR, DIVAS_CR_MODE_Msk, mode);
}

/**
  * @brief    Get Work Mode
  * @rmtoll   CR    MODE    FL_DIVAS_GetMode
  * @param    DIVASx DIVAS instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_DIVAS_MODE_DIV
  *           @arg @ref FL_DIVAS_MODE_ROOT
  */
__STATIC_INLINE uint32_t FL_DIVAS_GetMode(DIVAS_Type *DIVASx)
{
    return (uint32_t)(READ_BIT(DIVASx->CR, DIVAS_CR_MODE_Msk));
}

/**
  * @}
  */

/** @defgroup DIVAS_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_DIVAS_DeInit(DIVAS_Type *DIVASx);
FL_ErrorStatus FL_DIVAS_Init(DIVAS_Type *DIVASx);
uint32_t FL_DIVAS_Hdiv_Calculation(DIVAS_Type *DIVASx, int32_t DivisorEnd, int16_t Divisor, int32_t *Quotient, int16_t *Residue);
uint32_t FL_DIVAS_Root_Calculation(DIVAS_Type *DIVASx, uint32_t Root, uint16_t *Result);

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

#endif /* __FM33LG0XX_FL_DIVAS_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.1 @ 2020-09-14*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
