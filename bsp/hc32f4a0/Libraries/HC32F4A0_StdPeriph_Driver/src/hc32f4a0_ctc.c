/**
 *******************************************************************************
 * @file  hc32f4a0_ctc.c
 * @brief This file provides firmware functions to manage the Clock Trimming
 *        Controller(CTC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-09-01       Hongjh          First version
   2020-10-30       Hongjh          Modify for refining CTC initialization structure
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_ctc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_CTC CTC
 * @brief CTC Driver Library
 * @{
 */

#if (DDL_CTC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup CTC_Local_Macros CTC Local Macros
 * @{
 */

/**
 * @defgroup CTC_Check_Parameters_Validity CTC Check Parameters Validity
 * @{
 */

#define IS_CTC_REF_CLK_SRC(x)                                                  \
(   ((x) == CTC_REF_CLK_XTAL)                   ||                             \
    ((x) == CTC_REF_CLK_XTAL32)                 ||                             \
    ((x) == CTC_REF_CLK_CTCREF))

#define IS_CTC_REF_CLK_DIV(x)                                                  \
(   ((x) == CTC_REF_CLK_DIV8)                   ||                             \
    ((x) == CTC_REF_CLK_DIV32)                  ||                             \
    ((x) == CTC_REF_CLK_DIV128)                 ||                             \
    ((x) == CTC_REF_CLK_DIV256)                 ||                             \
    ((x) == CTC_REF_CLK_DIV512)                 ||                             \
    ((x) == CTC_REF_CLK_DIV1024)                ||                             \
    ((x) == CTC_REF_CLK_DIV2048)                ||                             \
    ((x) == CTC_REF_CLK_DIV4096))

#define IS_CTC_OFFSET_VALUE(x)                  ((x) <= 0xFFUL)

#define IS_CTC_RELOAD_VALUE(x)                  ((x) <= 0xFFFFUL)

#define IS_CTC_TRIM_VALUE(x)                    ((x) <= 0x3FUL)

#define IS_CTC_TOLERANCE_DEVIATION(x)           (((x) >= 0.0F) &&              \
                                                 ((x) <= CTC_TOLERANCE_DEVIATION_MAX))

#define IS_CTC_FLAG(x)                                                         \
(   ((x) != 0UL)                                &&                             \
    (((x) | CTC_FLAG_ALL) ==  CTC_FLAG_ALL))
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup CTC_Global_Functions CTC Global Functions
 * @{
 */

/**
 * @brief  Initialize CTC function.
 * @param  [in] pstcCtcInit         Pointer to a @ref stc_ctc_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorNotReady: CTC state is busy
 *           - ErrorInvalidParameter:   If one of following cases matches:
 *                                      - pstcCtcInit is NULL
 *                                      - Reference frequency is out of range
 *                                      - Calculate reload & offset value out of range
 */
en_result_t CTC_Init(const stc_ctc_init_t *pstcCtcInit)
{
    float f32OffsetValue;
    uint32_t u32RegValue;
    uint32_t u32ReloadValue;
    uint32_t u32OffsetValue;
    uint32_t u32RefClockDiv;
    uint32_t u32Multiplier;
    uint64_t u64InterClock;
    uint32_t u32HrcFreq = HRC_VALUE;
    en_result_t enRet = ErrorNotReady;

    /* Check CTC status */
    if (CTC_FLAG_BUSY != (READ_REG32_BIT(M4_CTC->STR, CTC_FLAG_BUSY)))
    {
        if ((NULL == pstcCtcInit) || (0UL == pstcCtcInit->u32RefClockFreq))
        {
            enRet = ErrorInvalidParameter;
        }
        else
        {
            /* Check parameters */
            DDL_ASSERT(IS_CTC_REF_CLK_SRC(pstcCtcInit->u32RefClockSrc));
            DDL_ASSERT(IS_CTC_REF_CLK_DIV(pstcCtcInit->u32RefClockDiv));
            DDL_ASSERT(IS_CTC_TRIM_VALUE(pstcCtcInit->u32TrimValue));
            DDL_ASSERT(IS_CTC_TOLERANCE_DEVIATION(pstcCtcInit->f32ToleranceDeviation));

            if (pstcCtcInit->u32RefClockDiv < CTC_REF_CLK_DIV128)
            {
                u32RefClockDiv = (8UL << (2UL * pstcCtcInit->u32RefClockDiv));
            }
            else
            {
                u32RefClockDiv = (32UL << pstcCtcInit->u32RefClockDiv);
            }
            u64InterClock = ((uint64_t)u32HrcFreq) * ((uint64_t)(u32RefClockDiv));
            u32Multiplier = (uint32_t)(u64InterClock / pstcCtcInit->u32RefClockFreq);

            /* Calculate offset value formula: OFSVAL = (Fhrc / (Fref * Fref_divsion)) * TA */
            f32OffsetValue = ((float)u32Multiplier) * (pstcCtcInit->f32ToleranceDeviation);
            u32OffsetValue = (uint32_t)(f32OffsetValue);

            /* Calculate reload value formula: RLDVAL = (Fhrc / (Fref * Fref_divsion)) + OFSVAL */
            u32ReloadValue = u32Multiplier + u32OffsetValue;

            if ((IS_CTC_OFFSET_VALUE(u32OffsetValue)) && (IS_CTC_RELOAD_VALUE(u32ReloadValue)))
            {
                /* Set CR1 */
                u32RegValue = (pstcCtcInit->u32RefClockDiv | \
                               pstcCtcInit->u32RefClockSrc | \
                               (pstcCtcInit->u32TrimValue << CTC_CR1_TRMVAL_POS));
                WRITE_REG32(M4_CTC->CR1, u32RegValue);

                /* Set CR2 */
                u32RegValue = ((u32ReloadValue << CTC_CR2_RLDVAL_POS) | u32OffsetValue);
                WRITE_REG32(M4_CTC->CR2, u32RegValue);
                enRet = Ok;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_uart_init_t to default values.
 * @param  [out] pstcCtcInit        Pointer to a @ref stc_ctc_init_t structure.
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: pstcCtcInit is NULL
 */
en_result_t CTC_StructInit(stc_ctc_init_t *pstcCtcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check parameters */
    if (NULL != pstcCtcInit)
    {
        pstcCtcInit->u32RefClockFreq = 0UL;
        pstcCtcInit->u32RefClockSrc = CTC_REF_CLK_CTCREF;
        pstcCtcInit->u32RefClockDiv = CTC_REF_CLK_DIV8;
        pstcCtcInit->f32ToleranceDeviation = 0.0F;
        pstcCtcInit->u32TrimValue = 0UL;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize CTC function.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: De-Initialize success
 *           - ErrorNotReady: CTC state is busy
 */
en_result_t CTC_DeInit(void)
{
    en_result_t enRet = ErrorNotReady;

    /* Check CTC status */
    if (CTC_FLAG_BUSY != (READ_REG32_BIT(M4_CTC->STR, CTC_FLAG_BUSY)))
    {
        /* Configures the registers to reset value. */
        WRITE_REG32(M4_CTC->CR1, 0UL);
        WRITE_REG32(M4_CTC->CR2, 0UL);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set CTC reference clock division.
 * @param  [in] u32Div              CTC reference clock prescaler
 *         This parameter can be one of the following values:
 *           @arg CTC_REF_CLK_DIV8:    REFCLK/8
 *           @arg CTC_REF_CLK_DIV32:   REFCLK/32
 *           @arg CTC_REF_CLK_DIV128:  REFCLK/128
 *           @arg CTC_REF_CLK_DIV256:  REFCLK/256
 *           @arg CTC_REF_CLK_DIV512:  REFCLK/512
 *           @arg CTC_REF_CLK_DIV1024: REFCLK/1024
 *           @arg CTC_REF_CLK_DIV2048: REFCLK/2048
 *           @arg CTC_REF_CLK_DIV4096: REFCLK/4096
 * @retval None
 */
void CTC_SetRefClockDiv(uint32_t u32Div)
{
    /* Check parameters */
    DDL_ASSERT(IS_CTC_REF_CLK_DIV(u32Div));

    MODIFY_REG32(M4_CTC->CR1, CTC_CR1_REFPSC, u32Div);
}

/**
 * @brief  Set CTC reference clock source.
 * @param  [in] u32ClockSrc         CTC reference clock source
 *         This parameter can be one of the following values:
 *           @arg CTC_REF_CLK_CTCREF: Clock source CTCREF
 *           @arg CTC_REF_CLK_XTAL:   Clock source XTAL
 * @retval None
 */
void CTC_SetRefClockSrc(uint32_t u32ClockSrc)
{
    /* Check parameters */
    DDL_ASSERT(IS_CTC_REF_CLK_SRC(u32ClockSrc));

    MODIFY_REG32(M4_CTC->CR1, CTC_CR1_REFCKS, u32ClockSrc);
}

/**
 * @brief  Enable or disable CTC error interrupt function.
 * @param  [in] enNewState          The function new state.
 *         This parameter can be one of the following values:
 *           @arg Enable:           Enable CTC error interrupt function.
 *           @arg Disable:          Disable CTC error interrupt function.
 * @retval None
 */
void CTC_IntCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bM4_CTC->CR1_b.ERRIE, enNewState);
}

/**
 * @brief  Get CTC flag.
 * @param  [in] u32Flag             CTC flag
 *         This parameter can be any composed value of the following values::
 *           @arg CTC_FLAG_TRIM_OK:  Trimming OK flag
 *           @arg CTC_FLAG_TRIM_OVF: Trimming overflow flag
 *           @arg CTC_FLAG_TRIM_UDF: Trimming underflow flag
 *           @arg CTC_FLAG_BUSY:     CTC busy flag
 * @retval Returned value can be one of the following values:
 *           - Set:   Any bit of the composed flag is set.
 *           - Reset: All bit of the composed flag is reset.
 */
en_flag_status_t CTC_GetStatus(uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_CTC_FLAG(u32Flag));

    return ((0UL == READ_REG32_BIT(M4_CTC->STR, u32Flag)) ? Reset : Set);
}

/**
 * @brief  Set CTC trimming value.
 * @param  [in] u32TrimValue        CTC trimming value
 *         This parameter can be min=0 && max=0x3F
 * @retval None
 */
void CTC_SetTrimValue(uint32_t u32TrimValue)
{
    /* Check parameters */
    DDL_ASSERT(IS_CTC_TRIM_VALUE(u32TrimValue));

    MODIFY_REG32(M4_CTC->CR1, CTC_CR1_TRMVAL, (u32TrimValue << CTC_CR1_TRMVAL_POS));
}

/**
 * @brief  Get CTC trimming value.
 * @param  None
 * @retval CTC trimming value(between Min_Data=0 and Max_Data=0x3F)
 */
uint32_t CTC_GetTrimValue(void)
{
    return (READ_REG32_BIT(M4_CTC->CR1, CTC_CR1_TRMVAL) >> CTC_CR1_TRMVAL_POS);
}

/**
 * @brief  Set CTC reload value.
 * @param  [in] u32ReloadValue      CTC reload value
 *         This parameter can be between Min_Data=0 and Max_Data=0xFFFF
 * @retval None
 */
void CTC_SetReloadValue(uint32_t u32ReloadValue)
{
    /* Check parameters */
    DDL_ASSERT(IS_CTC_RELOAD_VALUE(u32ReloadValue));

    MODIFY_REG32(M4_CTC->CR2, CTC_CR2_RLDVAL, (u32ReloadValue << CTC_CR2_RLDVAL_POS));
}

/**
 * @brief  Get CTC reload value.
 * @param  None
 * @retval CTC reload value (between Min_Data=0 and Max_Data=0xFFFF)
 */
uint16_t CTC_GetReloadValue(void)
{
    return (uint16_t)(READ_REG32_BIT(M4_CTC->CR2, CTC_CR2_RLDVAL) >> CTC_CR2_RLDVAL_POS);
}

/**
 * @brief  Set CTC offset value.
 * @param  [in] u32OffsetValue      CTC offset value
 *         This parameter can be between Min_Data=0 and Max_Data=0xFF
 * @retval None
 */
void CTC_SetOffsetValue(uint32_t u32OffsetValue)
{
    /* Check parameters */
    DDL_ASSERT(IS_CTC_OFFSET_VALUE(u32OffsetValue));

    MODIFY_REG32(M4_CTC->CR2, CTC_CR2_OFSVAL, (u32OffsetValue << CTC_CR2_OFSVAL_POS));
}

/**
 * @brief  Get CTC offset value.
 * @param  None
 * @retval CTC offset value (between Min_Data=0 and Max_Data=0xFF)
 */
uint32_t CTC_GetOffsetValue(void)
{
    return (READ_REG32_BIT(M4_CTC->CR2, CTC_CR2_OFSVAL) >> CTC_CR2_OFSVAL_POS);
}

/**
 * @}
 */

#endif /* DDL_CTC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
