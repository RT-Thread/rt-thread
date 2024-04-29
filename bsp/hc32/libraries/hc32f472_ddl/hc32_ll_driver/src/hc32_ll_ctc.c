/**
 *******************************************************************************
 * @file  hc32_ll_ctc.c
 * @brief This file provides firmware functions to manage the Clock Trimming
 *        Controller(CTC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
   2023-06-30       CDT             Modify typo
                                    Modify CTC_DeInit() to use RMU function reset
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_ctc.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_CTC CTC
 * @brief CTC Driver Library
 * @{
 */

#if (LL_CTC_ENABLE == DDL_ON)

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
(   ((x) == CTC_REF_CLK_SRC_XTAL)           ||                                 \
    ((x) == CTC_REF_CLK_SRC_XTAL32)         ||                                 \
    ((x) == CTC_REF_CLK_SRC_CTCREF))

#define IS_CTC_REF_CLK_DIV(x)                                                  \
(   ((x) == CTC_REF_CLK_DIV2)               ||                                 \
    ((x) == CTC_REF_CLK_DIV4)               ||                                 \
    ((x) == CTC_REF_CLK_DIV8)               ||                                 \
    ((x) == CTC_REF_CLK_DIV16)              ||                                 \
    ((x) == CTC_REF_CLK_DIV64)              ||                                 \
    ((x) == CTC_REF_CLK_DIV256)             ||                                 \
    ((x) == CTC_REF_CLK_DIV1024)            ||                                 \
    ((x) == CTC_REF_CLK_DIV4096))

#define IS_CTC_OFFSET_VALUE(x)              ((x) <= 0xFFUL)

#define IS_CTC_RELOAD_VALUE(x)              ((x) <= 0xFFFFUL)

#define IS_CTC_TRIM_VALUE(x)                ((x) <= 0x3FUL)

#define IS_CTC_TOLERANT_ERR(x)                                                 \
(   ((x) >= 0.0F) &&                                                           \
    ((x) <= CTC_TOLERANT_ERR_MAX))

#define IS_CTC_FLAG(x)                                                         \
(   ((x) != 0UL)                            &&                                 \
    (((x) | CTC_FLAG_ALL) ==  CTC_FLAG_ALL))

#define IS_CTC_HRC_CLK_DIV(x)                                                  \
(   ((x) == CTC_HRC_CLK_DIV1)               ||                                 \
    ((x) == CTC_HRC_CLK_DIV2)               ||                                 \
    ((x) == CTC_HRC_CLK_DIV4)               ||                                 \
    ((x) == CTC_HRC_CLK_DIV8)               ||                                 \
    ((x) == CTC_HRC_CLK_DIV32)              ||                                 \
    ((x) == CTC_HRC_CLK_DIV128)             ||                                 \
    ((x) == CTC_HRC_CLK_DIV512)             ||                                 \
    ((x) == CTC_HRC_CLK_DIV2048))

#define IS_CTC_CTCREF_EDGE(x)                                                  \
(   ((x) == CTC_CTCREF_RISING_RISING)       ||                                 \
    ((x) == CTC_CTCREF_RISING_FALLING)      ||                                 \
    ((x) == CTC_CTCREF_FALLING_RISING)      ||                                 \
    ((x) == CTC_CTCREF_FALLING_FALLING))
/**
 * @}
 */

/**
 * @defgroup CTC_Tolerant_Error_Max CTC Tolerant Error Max
 * @{
 */
#define CTC_TOLERANT_ERR_MAX                (1.0F)
/**
 * @}
 */

#define CTC_RMU_TIMEOUT                     (100UL)

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
 * @defgroup CTC_Local_Functions CTC Local Functions
 * @{
 */

/**
 * @brief  Get HRC clock frequency.
 * @param  None
 * @retval HRC clock frequency.
 */
static uint32_t CTC_GetHrcClockFreq(void)
{
    return HRC_VALUE;
}

/**
 * @brief  Get reference clock division.
 * @param  [in] u32Cr1RefPsc            CTC CR1 REFPSC bits value.
 *         This parameter can be between Min_Data=0 and Max_Data=7
 * @retval Reference clock division.
 */
static uint32_t CTC_GetRefClockDiv(uint32_t u32Cr1RefPsc)
{
    uint32_t u32RefclkDiv;

    if (u32Cr1RefPsc < CTC_REF_CLK_DIV64) {
        u32RefclkDiv = (2UL << u32Cr1RefPsc);
    } else {
        u32RefclkDiv = (64UL << (2UL * (u32Cr1RefPsc - CTC_REF_CLK_DIV64)));
    }

    return u32RefclkDiv;
}

/**
 * @brief  Get CTC HRC clock division.
 * @param  [in] u32Cr1HrcPsc            CTC CR1 REFPSC bits value.
 *         This parameter can be between Min_Data=0 and Max_Data=7
 * @retval CTC HRC clock division.
 */
static uint32_t CTC_GetCtcHrcClockDiv(uint32_t u32Cr1HrcPsc)
{
    uint32_t u32CtcHrcDiv;

    if (u32Cr1HrcPsc < CTC_HRC_CLK_DIV32) {
        u32CtcHrcDiv = (1UL << u32Cr1HrcPsc);
    } else {
        u32CtcHrcDiv = (32UL << (2UL * (u32Cr1HrcPsc - CTC_HRC_CLK_DIV32)));
    }

    return u32CtcHrcDiv;
}
/**
 * @}
 */

/**
 * @defgroup CTC_Global_Functions CTC Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_ctc_ct_init_t to default values.
 * @param  [out] pstcCtcInit            Pointer to a @ref stc_ctc_ct_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcCtcInit value is NULL.
 */
int32_t CTC_CT_StructInit(stc_ctc_ct_init_t *pstcCtcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcCtcInit) {
        pstcCtcInit->u32HrcClockDiv = CTC_HRC_CLK_DIV1;
        pstcCtcInit->u32RefClockFreq = 0UL;
        pstcCtcInit->u32RefClockSrc = CTC_REF_CLK_SRC_CTCREF;
        pstcCtcInit->u32RefClockDiv = CTC_REF_CLK_DIV8;
        pstcCtcInit->f32TolerantErrRate = 0.0F;
        pstcCtcInit->u8TrimValue = 0U;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize CTC continuous trim function.
 * @param  [in] pstcCtcInit             Pointer to a @ref stc_ctc_ct_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_BUSY:             CTC state is busy.
 *           - LL_ERR_INVD_PARAM:       If one of following cases matches:
 *                                      - The pointer pstcCtcInit value is NULL.
 *                                      - Reference frequency is out of range.
 *                                      - Calculate reload & offset value out of range.
 */
int32_t CTC_CT_Init(const stc_ctc_ct_init_t *pstcCtcInit)
{
    float32_t f32OffsetValue;
    uint32_t u32RegValue;
    uint32_t u32ReloadValue;
    uint32_t u32OffsetValue;
    uint32_t u32RefClockDiv;
    uint32_t u32CtcHrcFreq;
    uint32_t u32Multiplier;
    uint64_t u64InterClock;
    int32_t i32Ret = LL_ERR_BUSY;

    /* Check CTC status */
    if (CTC_FLAG_BUSY != (READ_REG32_BIT(CM_CTC->STR, CTC_FLAG_BUSY))) {
        if ((NULL == pstcCtcInit) || (0UL == pstcCtcInit->u32RefClockFreq)) {
            i32Ret = LL_ERR_INVD_PARAM;
        } else {
            DDL_ASSERT(IS_CTC_REF_CLK_SRC(pstcCtcInit->u32RefClockSrc));
            DDL_ASSERT(IS_CTC_REF_CLK_DIV(pstcCtcInit->u32RefClockDiv));
            DDL_ASSERT(IS_CTC_TRIM_VALUE(pstcCtcInit->u8TrimValue));
            DDL_ASSERT(IS_CTC_TOLERANT_ERR(pstcCtcInit->f32TolerantErrRate));
            DDL_ASSERT(IS_CTC_HRC_CLK_DIV(pstcCtcInit->u32HrcClockDiv));

            u32CtcHrcFreq = (CTC_GetHrcClockFreq() / CTC_GetCtcHrcClockDiv(pstcCtcInit->u32HrcClockDiv));

            u32RefClockDiv = CTC_GetRefClockDiv(pstcCtcInit->u32RefClockDiv);
            u64InterClock = ((uint64_t)u32CtcHrcFreq) * ((uint64_t)(u32RefClockDiv));
            u32Multiplier = (uint32_t)(u64InterClock / pstcCtcInit->u32RefClockFreq);

            /* Calculate offset value formula: OFSVAL = (Fhrc / (Fref * Fref_division)) * TA */
            f32OffsetValue = ((float32_t)u32Multiplier) * (pstcCtcInit->f32TolerantErrRate);
            u32OffsetValue = (uint32_t)(f32OffsetValue);

            /* Calculate reload value formula: RLDVAL = (Fhrc / (Fref * Fref_division)) + OFSVAL */
            u32ReloadValue = u32Multiplier + u32OffsetValue;

            /* Check reload and offset value */
            if ((IS_CTC_OFFSET_VALUE(u32OffsetValue)) && (IS_CTC_RELOAD_VALUE(u32ReloadValue))) {
                /* Set CR1 */
                u32RegValue = (pstcCtcInit->u32RefClockDiv | pstcCtcInit->u32RefClockSrc | \
                               ((uint32_t)pstcCtcInit->u8TrimValue << CTC_CR1_TRMVAL_POS));
                u32RegValue |= pstcCtcInit->u32HrcClockDiv;
                WRITE_REG32(CM_CTC->CR1, u32RegValue);

                /* Set CR2 */
                u32RegValue = ((u32ReloadValue << CTC_CR2_RLDVAL_POS) | u32OffsetValue);
                WRITE_REG32(CM_CTC->CR2, u32RegValue);
                i32Ret = LL_OK;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_ctc_st_init_t to default values.
 * @param  [out] pstcCtcInit            Pointer to a @ref stc_ctc_st_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcCtcInit value is NULL.
 */
int32_t CTC_ST_StructInit(stc_ctc_st_init_t *pstcCtcInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcCtcInit) {
        pstcCtcInit->u32HrcClockDiv = CTC_HRC_CLK_DIV1;
        pstcCtcInit->f32CtcRefEdgeTime = 0.0F;
        pstcCtcInit->f32TolerantErrRate = 0.0F;
        pstcCtcInit->u32CtcRefEdge = CTC_CTCREF_RISING_RISING;
        pstcCtcInit->u8TrimValue = 0U;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize CTC single trim function.
 * @param  [in] pstcCtcInit             Pointer to a @ref stc_ctc_st_init_t structure.
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_BUSY:             CTC state is busy
 *           - LL_ERR_INVD_PARAM:       If one of following cases matches:
 *                                      - pstcCtcInit is NULL.
 *                                      - Reference frequency is out of range.
 *                                      - Calculate reload & offset value out of range
 */
int32_t CTC_ST_Init(const stc_ctc_st_init_t *pstcCtcInit)
{
    float32_t f32OffsetValue;
    uint32_t u32RegValue;
    uint32_t u32ReloadValue;
    uint32_t u32OffsetValue;
    uint32_t u32CtcHrcFreq;
    uint32_t u32Multiplier;
    int32_t i32Ret = LL_ERR_BUSY;

    /* Check CTC status */
    if (CTC_FLAG_BUSY != (READ_REG32_BIT(CM_CTC->STR, CTC_FLAG_BUSY))) {
        if (NULL == pstcCtcInit) {
            i32Ret = LL_ERR_INVD_PARAM;
        } else {
            DDL_ASSERT(IS_CTC_HRC_CLK_DIV(pstcCtcInit->u32HrcClockDiv));
            DDL_ASSERT(IS_CTC_TOLERANT_ERR(pstcCtcInit->f32TolerantErrRate));
            DDL_ASSERT(IS_CTC_CTCREF_EDGE(pstcCtcInit->u32CtcRefEdge));
            DDL_ASSERT(IS_CTC_TRIM_VALUE(pstcCtcInit->u8TrimValue));

            /* CTC trim HRC clock frequency */
            u32CtcHrcFreq = (CTC_GetHrcClockFreq() / CTC_GetCtcHrcClockDiv(pstcCtcInit->u32HrcClockDiv));

            f32OffsetValue = ((float32_t)u32CtcHrcFreq * pstcCtcInit->f32CtcRefEdgeTime);
            u32Multiplier = (uint32_t)(f32OffsetValue);

            /* Calculate offset value formula: OFSVAL = ( Fhrc x Ttrim ) x TA */
            f32OffsetValue = ((float32_t)u32Multiplier) * (pstcCtcInit->f32TolerantErrRate);
            u32OffsetValue = (uint32_t)(f32OffsetValue);

            /* Calculate reload value formula: RLDVAL = ( Fhrc x Ttrim ) + OFSVAL */
            u32ReloadValue = u32Multiplier + u32OffsetValue;

            /* Check reload and offset value */
            if ((IS_CTC_OFFSET_VALUE(u32OffsetValue)) && (IS_CTC_RELOAD_VALUE(u32ReloadValue))) {
                /* Set CR1 */
                u32RegValue = (CTC_CR1_REFCKS_0 | pstcCtcInit->u32HrcClockDiv |  pstcCtcInit->u32CtcRefEdge | \
                               ((uint32_t)pstcCtcInit->u8TrimValue << CTC_CR1_TRMVAL_POS));
                WRITE_REG32(CM_CTC->CR1, u32RegValue);

                /* Set CR2 */
                u32RegValue = ((u32ReloadValue << CTC_CR2_RLDVAL_POS) | u32OffsetValue);
                WRITE_REG32(CM_CTC->CR2, u32RegValue);
                i32Ret = LL_OK;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize CTC function.
 * @param  None
 * @retval int32_t:
 *           - LL_OK:                   De-Initialize success
 *           - LL_ERR_TIMEOUT:          Reset time out
 */
int32_t CTC_DeInit(void)
{
    __IO uint32_t u32TimeOut = 0U;
    int32_t i32Ret = LL_OK;

    DDL_ASSERT((CM_PWC->FPRC & PWC_FPRC_FPRCB1) == PWC_FPRC_FPRCB1);

    CLR_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_CTC);
    /* Ensure reset procedure is completed */
    while (RMU_FRST0_CTC != READ_REG32_BIT(CM_RMU->FRST0, RMU_FRST0_CTC)) {
        u32TimeOut++;
        if (u32TimeOut > CTC_RMU_TIMEOUT) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable CTC error interrupt function.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void CTC_IntCmd(en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(CM_CTC->CR1, CTC_CR1_ERRIE);
    } else {
        CLR_REG32_BIT(CM_CTC->CR1, CTC_CR1_ERRIE);
    }
}

/**
 * @brief  Get CTC flag status.
 * @param  [in] u32Flag                 CTC flag
 *         This parameter can be any composed value of the macros group @ref CTC_Flag
 *           @arg CTC_FLAG_TRIM_OK:     Trimming OK flag
 *           @arg CTC_FLAG_TRIM_OVF:    Trimming overflow flag
 *           @arg CTC_FLAG_TRIM_UDF:    Trimming underflow flag
 *           @arg CTC_FLAG_BUSY:        CTC busy flag
 * @retval Returned value can be one of the following values:
 */
en_flag_status_t CTC_GetStatus(uint32_t u32Flag)
{
    DDL_ASSERT(IS_CTC_FLAG(u32Flag));

    return ((0UL == READ_REG32_BIT(CM_CTC->STR, u32Flag)) ? RESET : SET);
}

/**
 * @brief  Set CTC trimming value.
 * @param  [in] u8TrimValue             CTC trimming value
 *         This parameter can be Min_Data=0 && Max_Data=0x3F
 * @retval None
 */
void CTC_SetTrimValue(uint8_t u8TrimValue)
{
    DDL_ASSERT(IS_CTC_TRIM_VALUE(u8TrimValue));

    MODIFY_REG32(CM_CTC->CR1, CTC_CR1_TRMVAL, ((uint32_t)u8TrimValue << CTC_CR1_TRMVAL_POS));
}

/**
 * @brief  Get CTC trimming value.
 * @param  None
 * @retval CTC trimming value(between Min_Data=0 and Max_Data=0x3F)
 */
uint8_t CTC_GetTrimValue(void)
{
    return (uint8_t)(READ_REG32_BIT(CM_CTC->CR1, CTC_CR1_TRMVAL) >> CTC_CR1_TRMVAL_POS);
}

/**
 * @brief  Set CTC reload value.
 * @param  [in] u16ReloadValue          CTC reload value
 *         This parameter can be between Min_Data=0 and Max_Data=0xFFFF
 * @retval None
 */
void CTC_SetReloadValue(uint16_t u16ReloadValue)
{
    MODIFY_REG32(CM_CTC->CR2, CTC_CR2_RLDVAL, ((uint32_t)u16ReloadValue << CTC_CR2_RLDVAL_POS));
}

/**
 * @brief  Get CTC reload value.
 * @param  None
 * @retval CTC reload value (between Min_Data=0 and Max_Data=0xFFFF)
 */
uint16_t CTC_GetReloadValue(void)
{
    return (uint16_t)(READ_REG32_BIT(CM_CTC->CR2, CTC_CR2_RLDVAL) >> CTC_CR2_RLDVAL_POS);
}

/**
 * @brief  Set CTC offset value.
 * @param  [in] u8OffsetValue           CTC offset value
 *         This parameter can be between Min_Data=0 and Max_Data=0xFF
 * @retval None
 */
void CTC_SetOffsetValue(uint8_t u8OffsetValue)
{
    MODIFY_REG32(CM_CTC->CR2, CTC_CR2_OFSVAL, ((uint32_t)u8OffsetValue << CTC_CR2_OFSVAL_POS));
}

/**
 * @brief  Get CTC offset value.
 * @param  None
 * @retval CTC offset value (between Min_Data=0 and Max_Data=0xFF)
 */
uint8_t CTC_GetOffsetValue(void)
{
    return (uint8_t)(READ_REG32_BIT(CM_CTC->CR2, CTC_CR2_OFSVAL) >> CTC_CR2_OFSVAL_POS);
}

/**
 * @brief  Get CTC count value.
 * @param  None
 * @retval CTC count value (between Min_Data=0 and Max_Data=0xFFFF)
 */
uint16_t CTC_GetCountValue(void)
{
    return READ_REG16(CM_CTC->CNT);
}

/**
 * @}
 */

#endif /* LL_CTC_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
