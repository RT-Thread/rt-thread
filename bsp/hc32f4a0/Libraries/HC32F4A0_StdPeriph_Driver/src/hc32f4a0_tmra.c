/**
 *******************************************************************************
 * @file  hc32f4a0_tmra.c
 * @brief This file provides firmware functions to manage the TMRA(TimerA).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Wuze            First version
   2020-07-02       Wuze            API TMRA_SyncStartCmd() refine.
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
#include "hc32f4a0_tmra.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_TMRA TMRA
 * @brief TMRA Driver Library
 * @{
 */

#if (DDL_TMRA_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMRA_Local_Macros TMRA Local Macros
 * @{
 */

/**
 * @defgroup TMRA_Configuration_Bit_Mask TMRA Configuration Bit Mask
 * @{
 */
#define TMRA_BCSTR_INIT_MSK                     (0x01F6UL)
#define TMRA_BCSTR_INT_MSK                      (0x00003000UL)
#define TMRA_BCSTR_FLAG_MSK                     (0x0000C000UL)
#define TMRA_FCONR_FILTER_CLK_MSK               (0x3UL)
#define TMRA_CCONR_FILTER_CLK_MSK               (TMRA_CCONR_NOFICKCP)
#define TMRA_PWM_POLARITY_MSK                   (0x03FFUL)
#define TMRA_TRIG_COND_MSK                      (TMRA_START_COND_ALL | TMRA_STOP_COND_ALL | TMRA_CLR_COND_ALL)
#define TMRA_CACHE_COND_MSK                     (TMRA_BCONR_BSE0 | TMRA_BCONR_BSE1)
#define TMRA_COM_TRIG_MSK                       (TMRA_COM_TRIG1 | TMRA_COM_TRIG2)
#define TMRA_TRIG_EVENT_MSK                     (AOS_TMRA_HTSSR_TRGSEL)
/**
 * @}
 */

/**
 * @defgroup TMRA_Unit_Index TMRA Unit Index
 * @{
 */
#define __TMRA_BASE                             (0x4003A000UL)
#define __TMRA_UNIT_SIZE                        (0x400UL)
#define TMRA_IDX(__TMRAx__)                     (((uint32_t)&(__TMRAx__)->CNTER - __TMRA_BASE) / __TMRA_UNIT_SIZE)
/**
 * @}
 */

/**
 * @defgroup TMRA_Register_Bit_Band TMRA Register Bit Band
 * @{
 */
#define __BIT_BAND_BASE                         (0x42000000UL)
#define __PERIP_BASE                            (0x40000000UL)
#define __REG_OFS(regAddr)                      ((regAddr) - __PERIP_BASE)
#define __BIT_BAND_ADDR(regAddr, pos)           ((__REG_OFS(regAddr) << 5U) + ((uint32_t)(pos) << 2U) + __BIT_BAND_BASE)
#define BIT_BAND(regAddr, pos)                  (*(__IO uint32_t *)__BIT_BAND_ADDR((regAddr), (pos)))
/**
 * @}
 */

/**
 * @defgroup TMRA_HTSSR_Address TMRA HTSSR Address
 * @{
 */
#define TMRA_HTSSR0_ADDR                        (0x40010880UL)
#define TMRA_HTSSR1_ADDR                        (0x40010884UL)
#define TMRA_HTSSR2_ADDR                        (0x40010888UL)
#define TMRA_HTSSR3_ADDR                        (0x4001088CUL)
/**
 * @}
 */

/**
 * @defgroup TMRA_Check_Parameters_Validity TMRA check parameters validity
 * @{
 */
#define IS_TMRA_UNIT(x)                                                        \
(   ((x) == M4_TMRA_1)                      ||                                 \
    ((x) == M4_TMRA_2)                      ||                                 \
    ((x) == M4_TMRA_3)                      ||                                 \
    ((x) == M4_TMRA_4)                      ||                                 \
    ((x) == M4_TMRA_5)                      ||                                 \
    ((x) == M4_TMRA_6)                      ||                                 \
    ((x) == M4_TMRA_7)                      ||                                 \
    ((x) == M4_TMRA_8)                      ||                                 \
    ((x) == M4_TMRA_9)                      ||                                 \
    ((x) == M4_TMRA_10)                     ||                                 \
    ((x) == M4_TMRA_11)                     ||                                 \
    ((x) == M4_TMRA_12))

#define IS_TMRA_EVEN_UNIT(x)                                                   \
(   ((x) == M4_TMRA_2)                      ||                                 \
    ((x) == M4_TMRA_4)                      ||                                 \
    ((x) == M4_TMRA_6)                      ||                                 \
    ((x) == M4_TMRA_8)                      ||                                 \
    ((x) == M4_TMRA_10)                     ||                                 \
    ((x) == M4_TMRA_12))

#define IS_TMRA_CH(x)                                                          \
(   ((x) <= TMRA_CH_4))

#define IS_TMRA_FUNC_MODE(x)                                                   \
(   ((x) == TMRA_FUNC_COMPARE)              ||                                 \
    ((x) == TMRA_FUNC_CAPTURE))

#define IS_TMRA_PCLK_DIV(x)                                                    \
(   ((x) == TMRA_PCLK_DIV1)                 ||                                 \
    ((x) == TMRA_PCLK_DIV2)                 ||                                 \
    ((x) == TMRA_PCLK_DIV4)                 ||                                 \
    ((x) == TMRA_PCLK_DIV8)                 ||                                 \
    ((x) == TMRA_PCLK_DIV16)                ||                                 \
    ((x) == TMRA_PCLK_DIV32)                ||                                 \
    ((x) == TMRA_PCLK_DIV64)                ||                                 \
    ((x) == TMRA_PCLK_DIV128)               ||                                 \
    ((x) == TMRA_PCLK_DIV256)               ||                                 \
    ((x) == TMRA_PCLK_DIV512)               ||                                 \
    ((x) == TMRA_PCLK_DIV1024))

#define IS_TMRA_CNT_DIR(x)                                                     \
(   ((x) == TMRA_DIR_DOWN)                  ||                                 \
    ((x) == TMRA_DIR_UP))

#define IS_TMRA_CNT_MODE(x)                                                    \
(   ((x) == TMRA_MODE_SAWTOOTH)             ||                                 \
    ((x) == TMRA_MODE_TRIANGLE))

#define IS_TMRA_OVF_OPERATION(x)                                               \
(   ((x) == TMRA_OVF_CNT_CONTINUE)          ||                                 \
    ((x) == TMRA_OVF_CNT_STOP))

#define IS_TMRA_FILTER_CLK_DIV(x)                                              \
(   ((x) <= TMRA_FILTER_CLK_DIV64))

#define IS_TMRA_CACHE_COND(x)                                                  \
(   ((x) == TMRA_CACHE_COND_OVF_CLR)        ||                                 \
    ((x) == TMRA_CACHE_COND_TW_VALLEY)      ||                                 \
    ((x) == TMRA_CACHE_COND_TW_PEAK))

#define IS_TMRA_PWM_START_POLARITY(x)                                          \
(   ((x) == TMRA_PWM_START_LOW)             ||                                 \
    ((x) == TMRA_PWM_START_HIGH)            ||                                 \
    ((x) == TMRA_PWM_START_KEEP))

#define IS_TMRA_PWM_STOP_POLARITY(x)                                           \
(   ((x) == TMRA_PWM_STOP_LOW)              ||                                 \
    ((x) == TMRA_PWM_STOP_HIGH)             ||                                 \
    ((x) == TMRA_PWM_STOP_KEEP))

#define IS_TMRA_PWM_CMP_POLARITY(x)                                            \
(   ((x) == TMRA_PWM_CMP_LOW)               ||                                 \
    ((x) == TMRA_PWM_CMP_HIGH)              ||                                 \
    ((x) == TMRA_PWM_CMP_KEEP)              ||                                 \
    ((x) == TMRA_PWM_CMP_REVERSE))

#define IS_TMRA_PWM_PERIOD_POLARITY(x)                                         \
(   ((x) == TMRA_PWM_PERIOD_LOW)            ||                                 \
    ((x) == TMRA_PWM_PERIOD_HIGH)           ||                                 \
    ((x) == TMRA_PWM_PERIOD_KEEP)           ||                                 \
    ((x) == TMRA_PWM_PERIOD_REVERSE))

#define IS_TMRA_PWM_FORCE_POLARITY(x)                                          \
(   ((x) == TMRA_PWM_FORCE_INVALID)         ||                                 \
    ((x) == TMRA_PWM_FORCE_LOW)             ||                                 \
    ((x) == TMRA_PWM_FORCE_HIGH))

#define IS_TMRA_EVT_USAGE(x)                                                   \
(   ((x) == TMRA_EVENT_USAGE_CNT)           ||                                 \
    ((x) == TMRA_EVENT_USAGE_CAPT))

#define IS_TMRA_COM_TRIGGER(x)                                                 \
(   ((x) != 0U)                             &&                                 \
    (((x) | TMRA_COM_TRIG_MSK) == TMRA_COM_TRIG_MSK))

#define IS_TMRA_VALID_VAL(x)                                                   \
(   (x) <= 0xFFFFUL)

/**
 * @}
 */

/**
 * @defgroup TMRA_Miscellaneous_Macros TMRA Miscellaneous Macros
 * @{
 */
#define TMRA_CH_COUNT                       (4U)
#define TMRA_PIN_PWM_OFFSET                 (3U)
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
 * @defgroup TMRA_Global_Functions TMRA Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified TMRA peripheral according to the specified parameters \
 *         in the structure stc_tmra_init_t
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  pstcInit               Pointer to a stc_tmra_init_t structure value that \
 *                                      contains the configuration information for the TMRA.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t TMRA_Init(M4_TMRA_TypeDef *TMRAx, const stc_tmra_init_t *pstcInit)
{
    uint32_t u32Cfg = 0U;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CNT_DIR(pstcInit->u32CntDir));
        DDL_ASSERT(IS_TMRA_CNT_MODE(pstcInit->u32CntMode));
        DDL_ASSERT(IS_TMRA_OVF_OPERATION(pstcInit->u32CntOvfOp));
        DDL_ASSERT(IS_TMRA_VALID_VAL(pstcInit->u32PeriodVal));
        DDL_ASSERT(IS_TMRA_VALID_VAL(pstcInit->u32CntVal));

        if (pstcInit->u32ClkSrc == TMRA_CLK_PCLK)
        {
            DDL_ASSERT(IS_TMRA_PCLK_DIV(pstcInit->u32PCLKDiv));
            u32Cfg = pstcInit->u32PCLKDiv | pstcInit->u32CntDir | pstcInit->u32CntMode;
        }
        else
        {
            WRITE_REG32(TMRAx->HCUPR, (pstcInit->u32ClkSrc & TMRA_CLK_HW_UP_ALL));
            WRITE_REG32(TMRAx->HCDOR, ((pstcInit->u32ClkSrc & TMRA_CLK_HW_DOWN_ALL) >> 16U));
        }

        u32Cfg |= pstcInit->u32CntOvfOp;

        MODIFY_REG32(TMRAx->BCSTR, TMRA_BCSTR_INIT_MSK, u32Cfg);
        WRITE_REG32(TMRAx->PERAR, pstcInit->u32PeriodVal);
        WRITE_REG32(TMRAx->CNTER, pstcInit->u32CntVal);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the TMRA initialization structure.
 * @param  [in]  pstcInit               Pointer to a stc_tmra_init_t structure value that \
 *                                      contains the configuration information for the TMRA.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcInit == NULL.
 */
en_result_t TMRA_StructInit(stc_tmra_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcInit != NULL)
    {
        pstcInit->u32ClkSrc    = TMRA_CLK_PCLK;
        pstcInit->u32PCLKDiv   = TMRA_PCLK_DIV1;
        pstcInit->u32CntDir    = TMRA_DIR_UP;
        pstcInit->u32CntMode   = TMRA_MODE_SAWTOOTH;
        pstcInit->u32CntOvfOp  = TMRA_OVF_CNT_CONTINUE;
        pstcInit->u32PeriodVal = 0xFFFFUL;
        pstcInit->u32CntVal    = 0UL;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-initializes the TMRA peripheral. Reset all registers of the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @retval None
 */
void TMRA_DeInit(M4_TMRA_TypeDef *TMRAx)
{
    uint32_t i;
    uint32_t u32AddrOffset;
    uint32_t u32CMPARAddr;
    uint32_t u32CCONRAddr;
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    u32CMPARAddr = TMRAx->CMPAR1;
    u32CCONRAddr = TMRAx->CCONR1;
    u32PCONRAddr = TMRAx->PCONR1;

    for (i=0U; i<TMRA_CH_COUNT; i++)
    {
        u32AddrOffset = i * 4U;
        RW_MEM32(u32CMPARAddr + u32AddrOffset) = 0xFFFFUL;
        RW_MEM32(u32CCONRAddr + u32AddrOffset) = 0x0UL;
        RW_MEM32(u32PCONRAddr + u32AddrOffset) = 0x0UL;
    }

    WRITE_REG32(TMRAx->CNTER, 0x0U);
    WRITE_REG32(TMRAx->PERAR, 0xFFFFU);
    WRITE_REG32(TMRAx->BCSTR, 0x2U);
    WRITE_REG32(TMRAx->ICONR, 0x0U);
    WRITE_REG32(TMRAx->ECONR, 0x0U);
    WRITE_REG32(TMRAx->FCONR, 0x0U);
    WRITE_REG32(TMRAx->STFLR, 0x0U);
    WRITE_REG32(TMRAx->BCONR1, 0x0U);
    WRITE_REG32(TMRAx->BCONR2, 0x0U);
    WRITE_REG32(TMRAx->HCONR, 0x0U);
    WRITE_REG32(TMRAx->HCUPR, 0x0U);
    WRITE_REG32(TMRAx->HCDOR, 0x0U);
}

/**
 * @brief  Set general count value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32Val                 The general count value to be set.
 *                                      This parameter can be a number between 0U and 0xFFFFU, inclusive.
 * @retval None
 */
void TMRA_SetCntVal(M4_TMRA_TypeDef *TMRAx, uint32_t u32Val)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_VALID_VAL(u32Val));
    WRITE_REG32(TMRAx->CNTER, u32Val);
}

/**
 * @brief  Get general count value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @retval An uint32_t type type value of general count value between 0U and 0xFFFFU, inclusive.
 */
uint32_t TMRA_GetCntVal(const M4_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    return (TMRAx->CNTER);
}

/**
 * @brief  Set period reference value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32Val                 The period reference value to be set.
 *                                      This parameter can be a number between 0U and 0xFFFFU, inclusive.
 * @retval None
 */
void TMRA_SetPeriodVal(M4_TMRA_TypeDef *TMRAx, uint32_t u32Val)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_VALID_VAL(u32Val));
    WRITE_REG32(TMRAx->PERAR, u32Val);
}

/**
 * @brief  Get period reference value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @retval An uint32_t type type value of period reference value between 0U and 0xFFFFU, inclusive.
 */
uint32_t TMRA_GetPeriodVal(const M4_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    return (TMRAx->PERAR);
}

/**
 * @brief  Specifies the function mode of the specified TMRA channle.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32FuncMode            Function mode of TMRA.
 *                                      This parameter can be a value of @ref TMRA_Function_Mode
 *   @arg  TMRA_FUNC_COMPARE:           The function mode of TMRA is comparison ouput.
 *   @arg  TMRA_FUNC_CAPTURE:           The function mode of TMRA is capture the input.
 * @retval None
 */
void TMRA_SetFuncMode(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32FuncMode)
{
    uint32_t u32CCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
    DDL_ASSERT(IS_TMRA_FUNC_MODE(u32FuncMode));

    u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
    BIT_BAND(u32CCONRAddr, TMRA_CCONR_CAPMD_POS) = u32FuncMode;
}

/**
 * @brief  Set compare reference value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32Val                 The comparison reference value to be set.
 *                                      This parameter can be a number between 0U and 0xFFFFU, inclusive.
 * @retval None
 */
void TMRA_SetCmpVal(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Val)
{
    uint32_t u32CMPARAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_VALID_VAL(u32Val));
    u32CMPARAddr = (uint32_t)&TMRAx->CMPAR1 + (uint32_t)u8TmrCh * 4U;
    RW_MEM32(u32CMPARAddr) = u32Val;
}

/**
 * @brief  Get compare reference value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @retval An uint32_t type type value of comparison reference value between 0U and 0xFFFFU, inclusive.
 */
uint32_t TMRA_GetCmpVal(const M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh)
{
    uint32_t u32CMPARAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));

    u32CMPARAddr = (uint32_t)&TMRAx->CMPAR1 + (uint32_t)u8TmrCh * 4U;
    return RW_MEM32(u32CMPARAddr);
}

/**
 * @brief  Configures the specified channel's PWM of TMRA according to the specified parameters
 *         in the structure stc_tmra_pwm_cfg_t.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  pstcCfg                Pointer to a stc_tmra_pwm_cfg_t structure value that
 *                                      contains the configuration information for the PWM.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t TMRA_PWM_Config(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, const stc_tmra_pwm_cfg_t *pstcCfg)
{
    uint32_t u32Cfg;
    uint32_t u32PCONRAddr;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
        DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
        DDL_ASSERT(IS_TMRA_PWM_START_POLARITY(pstcCfg->u32StartPolarity));
        DDL_ASSERT(IS_TMRA_PWM_STOP_POLARITY(pstcCfg->u32StopPolarity));
        DDL_ASSERT(IS_TMRA_PWM_CMP_POLARITY(pstcCfg->u32CmpPolarity));
        DDL_ASSERT(IS_TMRA_PWM_PERIOD_POLARITY(pstcCfg->u32PeriodPolarity));
        DDL_ASSERT(IS_TMRA_PWM_FORCE_POLARITY(pstcCfg->u32ForcePolarity));

        u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
        u32Cfg = pstcCfg->u32StartPolarity  | \
                 pstcCfg->u32StopPolarity   | \
                 pstcCfg->u32CmpPolarity    | \
                 pstcCfg->u32PeriodPolarity | \
                 pstcCfg->u32ForcePolarity;
        MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PWM_POLARITY_MSK, u32Cfg);

        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the PWM configuration structure.
 * @param  [in]  pstcCfg                Pointer to a stc_tmra_pwm_cfg_t structure value that
 *                                      contains the configuration information for the PWM.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t TMRA_PWM_StructInit(stc_tmra_pwm_cfg_t *pstcCfg)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCfg != NULL)
    {
        pstcCfg->u32StartPolarity  = TMRA_PWM_START_HIGH;
        pstcCfg->u32StopPolarity   = TMRA_PWM_STOP_LOW;
        pstcCfg->u32CmpPolarity    = TMRA_PWM_CMP_REVERSE;
        pstcCfg->u32PeriodPolarity = TMRA_PWM_PERIOD_REVERSE;
        pstcCfg->u32ForcePolarity  = TMRA_PWM_FORCE_INVALID;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Enable or disable the specified channel's PWM output.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified channel's PWM output.
 *   @arg  Disable:                     Disable the specified channel's PWM output.
 * @retval None
 */
void TMRA_PWM_Cmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, en_functional_state_t enNewState)
{
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
    BIT_BAND(u32PCONRAddr, TMRA_PCONR_OUTEN_POS) = (uint32_t)enNewState;
}

/**
 * @brief  Specifies the divider of filter's clock source for the specified TMRA input pin.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8InputPin             The input pin of TMRA.
 *                                      This parameter can be values of @ref TMRA_Input_Pin
 *   @arg  TMRA_PIN_TRIG:               Pin TIMA_<t>_TRIG.
 *   @arg  TMRA_PIN_CLKA:               Pin TIMA_<t>_CLKA.
 *   @arg  TMRA_PIN_CLKB:               Pin TIMA_<t>_CLKB.
 *   @arg  TMRA_PIN_PWM1:               Pin TIMA_<t>_PWM1.
 *   @arg  TMRA_PIN_PWM2:               Pin TIMA_<t>_PWM2.
 *   @arg  TMRA_PIN_PWM3:               Pin TIMA_<t>_PWM3.
 *   @arg  TMRA_PIN_PWM4:               Pin TIMA_<t>_PWM4.
 * @param  [in]  u32ClkDiv              The clock source divider of the filter.
 *                                      This parameter can be a value of @ref TMRA_Filter_Clock_Divider
 *   @arg  TMRA_FILTER_CLK_DIV1:        The filter clock is PCLK / 1.
 *   @arg  TMRA_FILTER_CLK_DIV4:        The filter clock is PCLK / 4.
 *   @arg  TMRA_FILTER_CLK_DIV16:       The filter clock is PCLK / 16.
 *   @arg  TMRA_FILTER_CLK_DIV64:       The filter clock is PCLK / 64.
 * @retval None
 */
void TMRA_FilterConfig(M4_TMRA_TypeDef *TMRAx, uint8_t u8InputPin, uint32_t u32ClkDiv)
{
    uint8_t u8PinIdx = 0U;
    uint8_t u8TmrCh;
    uint32_t u32CfgMsk;
    uint32_t u32CCONRAddr;
    uint8_t au8Offset[] = {TMRA_FCONR_NOFICKTG_POS, TMRA_FCONR_NOFICKCA_POS, TMRA_FCONR_NOFICKCB_POS, \
                           TMRA_CCONR_NOFICKCP_POS, TMRA_CCONR_NOFICKCP_POS, TMRA_CCONR_NOFICKCP_POS, \
                           TMRA_CCONR_NOFICKCP_POS};

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_FILTER_CLK_DIV(u32ClkDiv));

    u8InputPin &= (uint8_t)TMRA_PIN_ALL;
    while (u8InputPin != 0U)
    {
        if ((u8InputPin & 0x1U) != 0U)
        {
            if (u8PinIdx < TMRA_PIN_PWM_OFFSET)
            {
                u32CfgMsk = (uint32_t)(TMRA_FCONR_FILTER_CLK_MSK << au8Offset[u8PinIdx]);
                MODIFY_REG32(TMRAx->FCONR, u32CfgMsk, (u32ClkDiv << au8Offset[u8PinIdx]));
            }
            else
            {
                u8TmrCh = u8PinIdx - TMRA_PIN_PWM_OFFSET;
                u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
                MODIFY_REG32(RW_MEM32(u32CCONRAddr),    \
                             TMRA_CCONR_FILTER_CLK_MSK, \
                             (u32ClkDiv << au8Offset[u8PinIdx]));
            }
        }
        u8InputPin >>= 1U;
        u8PinIdx++;
    }
}

/**
 * @brief  Enable or disable the filter function of the specified TMRA input pin.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8InputPin             The input pin of TMRA.
 *                                      This parameter can be values of @ref TMRA_Input_Pin
 *   @arg  TMRA_PIN_TRIG:               Pin TIMA_<t>_TRIG.
 *   @arg  TMRA_PIN_CLKA:               Pin TIMA_<t>_CLKA.
 *   @arg  TMRA_PIN_CLKB:               Pin TIMA_<t>_CLKB.
 *   @arg  TMRA_PIN_PWM1:               Pin TIMA_<t>_PWM1.
 *   @arg  TMRA_PIN_PWM2:               Pin TIMA_<t>_PWM2.
 *   @arg  TMRA_PIN_PWM3:               Pin TIMA_<t>_PWM3.
 *   @arg  TMRA_PIN_PWM4:               Pin TIMA_<t>_PWM4.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified pin's filter.
 *   @arg  Disable:                     Disable the specified pin's filter.
 * @retval None
 */
void TMRA_FilterCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8InputPin, en_functional_state_t enNewState)
{
    uint8_t u8PinIdx = 0U;
    uint8_t u8TmrCh;
    uint32_t u32CCONRAddr;
    uint8_t au8Offset[] = {TMRA_FCONR_NOFIENTG_POS, TMRA_FCONR_NOFIENCA_POS, TMRA_FCONR_NOFIENCB_POS, \
                           TMRA_CCONR_NOFIENCP_POS, TMRA_CCONR_NOFIENCP_POS, TMRA_CCONR_NOFIENCP_POS, \
                           TMRA_CCONR_NOFIENCP_POS};

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u8InputPin &= (uint8_t)TMRA_PIN_ALL;
    while (u8InputPin != 0U)
    {
        if ((u8InputPin & 0x1U) != 0U)
        {
            if (u8PinIdx < TMRA_PIN_PWM_OFFSET)
            {
                u32CCONRAddr = (uint32_t)&TMRAx->FCONR;
            }
            else
            {
                u8TmrCh = u8PinIdx - TMRA_PIN_PWM_OFFSET;
                u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
            }
            BIT_BAND(u32CCONRAddr, au8Offset[u8PinIdx]) = (uint32_t)enNewState;
        }
        u8InputPin >>= 1U;
        u8PinIdx++;
    }
}

/**
 * @brief  Specifies the capture condition for the specified channel.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32Cond                The capture condition. Set this parameter to 0xFFFF to select all the conditions of capturing start.
 *                                      This parameter can be values of @ref TMRA_Channel_Capture_Condition
 *   @arg  TMRA_CAPT_COND_INVALID:      The condition of capture is INVALID.
 *   @arg  TMRA_CAPT_COND_PWMR:         The condition of capture is a rising edge is sampled on PWM(pin).
 *   @arg  TMRA_CAPT_COND_PWMF:         The condition of capture is a falling edge is sampled on PWM(pin).
 *   @arg  TMRA_CAPT_COND_EVENT:        The condition of capture is the specified event occurred.
 *   @arg  TMRA_CAPT_COND_TRIGR:        The condition of capture is a rising edge is sampled on TRIG.
 *   @arg  TMRA_CAPT_COND_TRIGF:        The condition of capture is a falling edge is sampled on TRIG.
 * @retval None
 */
void TMRA_SetCaptCond(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Cond)
{
    uint32_t u32CCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));

    u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
    MODIFY_REG32(RW_MEM32(u32CCONRAddr), TMRA_CAPT_COND_ALL, u32Cond);
}

/**
 * @brief  Specifies the hardware trigger condition of TMRA according to the specified parameters
 *         in the structure stc_tmra_trig_cond_t.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  pstcCond               Pointer to a stc_tmra_trig_cond_t structure value that contains \
 *                                      the configuration information of hardware trigger condition.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCond == NULL.
 */
en_result_t TMRA_SetTrigCond(M4_TMRA_TypeDef *TMRAx, const stc_tmra_trig_cond_t *pstcCond)
{
    uint32_t u32StartCond;
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCond != NULL)
    {
        DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

        u32StartCond = (pstcCond->u32StartCond | pstcCond->u32StopCond | pstcCond->u32ClrCond) & TMRA_TRIG_COND_MSK;
        WRITE_REG32(TMRAx->HCONR, u32StartCond);
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Set a default value for the hardware trigger condition configuration structure.
 * @param  [in]  pstcCond               Pointer to a stc_tmra_trig_cond_t structure value that contains \
 *                                      the configuration information of hardware trigger condition.
 * @retval An en_result_t enumeration type value.
 *   @arg  Ok:                          No error occurred.
 *   @arg  ErrorInvalidParameter:       pstcCfg == NULL.
 */
en_result_t TMRA_TrigCondStructInit(stc_tmra_trig_cond_t *pstcCond)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (pstcCond != NULL)
    {
        pstcCond->u32StartCond = TMRA_START_COND_INVALID;
        pstcCond->u32StopCond  = TMRA_STOP_COND_INVALID;
        pstcCond->u32ClrCond   = TMRA_CLR_COND_INVALID;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Specifies the event for specified usage.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8EvtUsage             Usage of the event.
 *                                      This parameter can be a value of @ref TMRA_Event_Usage
 *   @arg  TMRA_EVENT_USAGE_CNT:        The specified event is used for counting.
 *   @arg  TMRA_EVENT_USAGE_CAPT:       The specified event is used for capturing.
 * @param  [in]  enEvent                An en_event_src_t enumeration type value.
 * @retval None
 * @note   Correspondence of TMRA instances and the event setting registers is as follows:
 *      TMRA unit         USAGE_CNT        USAGE_CAPT
 * ----------------------------------------------------------
 *      TMRA uint1   |   TMRA_HTSSR0   |   TMRA_HTSSR1
 *      TMRA uint2   |   TMRA_HTSSR1   |   TMRA_HTSSR0
 *      TMRA uint3   |   TMRA_HTSSR2   |   TMRA_HTSSR3
 *      TMRA uint4   |   TMRA_HTSSR3   |   TMRA_HTSSR2
 *      TMRA uint5   |   TMRA_HTSSR0   |   TMRA_HTSSR1
 *      TMRA uint6   |   TMRA_HTSSR1   |   TMRA_HTSSR0
 *      TMRA uint7   |   TMRA_HTSSR2   |   TMRA_HTSSR3
 *      TMRA uint8   |   TMRA_HTSSR3   |   TMRA_HTSSR2
 *      TMRA uint9   |   TMRA_HTSSR0   |   TMRA_HTSSR1
 *      TMRA uint10  |   TMRA_HTSSR1   |   TMRA_HTSSR0
 *      TMRA uint11  |   TMRA_HTSSR2   |   TMRA_HTSSR3
 *      TMRA uint12  |   TMRA_HTSSR3   |   TMRA_HTSSR2
 */
void TMRA_SetTriggerSrc(M4_TMRA_TypeDef *TMRAx, uint8_t u8EvtUsage, en_event_src_t enEvent)
{
    uint32_t u32Idx;
    uint32_t u32HTSSRAddr;
    uint32_t au32CaptEventAddr[] = {TMRA_HTSSR1_ADDR, TMRA_HTSSR0_ADDR, \
                                    TMRA_HTSSR3_ADDR, TMRA_HTSSR2_ADDR};

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_EVT_USAGE(u8EvtUsage));

    u32Idx = TMRA_IDX(TMRAx) % TMRA_CH_COUNT;
    if (u8EvtUsage == TMRA_EVENT_USAGE_CNT)
    {
        u32HTSSRAddr = (uint32_t)&M4_AOS->TMRA_HTSSR0 + u32Idx * 4U;
    }
    else
    {
        u32HTSSRAddr = au32CaptEventAddr[u32Idx];
    }

    MODIFY_REG32(RW_MEM32(u32HTSSRAddr), TMRA_TRIG_EVENT_MSK, enEvent);
}

/**
 * @brief  Enable or disable common trigger event for the specified usage.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8EvtUsage             Usage of the event.
 *                                      This parameter can be a value of @ref TMRA_Event_Usage
 *   @arg  TMRA_EVENT_USAGE_CNT:        The specified event is used for counting.
 *   @arg  TMRA_EVENT_USAGE_CAPT:       The specified event is used for capturing.
 * @param  [in]  u32ComTrig             Common trigger event enable bit mask.
 *                                      This parameter can be values of @ref TMRA_Common_Trigger_Sel
 *   @arg  TMRA_COM_TRIG1:              Common trigger 1.
 *   @arg  TMRA_COM_TRIG2:              Common trigger 2.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the specified common trigger.
 *   @arg Disable:                      Disable the specified common trigger.
 * @retval None
 */
void TMRA_ComTriggerCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8EvtUsage, \
                        uint32_t u32ComTrig, en_functional_state_t enNewState)
{
    uint32_t u32Idx;
    uint32_t u32HTSSRAddr;
    uint32_t au32CaptEventAddr[] = {TMRA_HTSSR1_ADDR, TMRA_HTSSR0_ADDR, \
                                    TMRA_HTSSR3_ADDR, TMRA_HTSSR2_ADDR};

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_EVT_USAGE(u8EvtUsage));
    DDL_ASSERT(IS_TMRA_COM_TRIGGER(u32ComTrig));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Idx = TMRA_IDX(TMRAx) % TMRA_CH_COUNT;
    if (u8EvtUsage == TMRA_EVENT_USAGE_CNT)
    {
        u32HTSSRAddr = (uint32_t)&M4_AOS->TMRA_HTSSR0 + u32Idx * 4U;
    }
    else
    {
        u32HTSSRAddr = au32CaptEventAddr[u32Idx];
    }

    if (enNewState == Enable)
    {
        SET_REG32_BIT(RW_MEM32(u32HTSSRAddr), u32ComTrig);
    }
    else
    {
        CLEAR_REG32_BIT(RW_MEM32(u32HTSSRAddr), u32ComTrig);
    }
}

/**
 * @brief  Configures cache function. Specifies the cache condition of compare value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be one of the following values of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 * @param  [in]  u32CacheCond           Cache condition of the specified TMRA unit.
 *                                      This parameter can be a value of @ref TMRA_Cmp_Value_Cache_Condition
 *   @arg  TIEMRA_CACHE_POS_OVF_CLR:    This configuration value applies to non-triangular wave counting mode. \
 *                                      When counting overflow or underflow or counting register was cleared, \
 *                                      transfer CMPARm(m=2,4) to CMPARn(n=1,3).
 *   @arg  TMRA_CACHE_POS_TW_PEAK:      In triangle wave count mode, when count reached peak, \
 *                                      transfer CMMARm(m=2,4) to CMMARn(n=1,3).
 *   @arg  TMRA_CACHE_POS_TW_VALLEY:    In triangle wave count mode, when count reached valley, \
 *                                      transfer CMMARm(m=2,4) to CMMARn(n=1,3).
 * @retval None
 */
void TMRA_CmpValCacheConfig(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32CacheCond)
{
    uint32_t u32BCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT((u8TmrCh == TMRA_CH_1) || (u8TmrCh == TMRA_CH_3));
    DDL_ASSERT(IS_TMRA_CACHE_COND(u32CacheCond));

    u32BCONRAddr = (uint32_t)&TMRAx->BCONR1 + (uint32_t)u8TmrCh * 4U;
    MODIFY_REG32(RW_MEM32(u32BCONRAddr), TMRA_CACHE_COND_MSK, u32CacheCond);
}

/**
 * @brief  Enable or disable the compare value function..
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be one of the following values of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the comparison reference value function.
 *   @arg  Disable:                     Disable the comparison reference value function.
 * @retval None
 */
void TMRA_CmpValCacheCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, en_functional_state_t enNewState)
{
    uint32_t u32BCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT((u8TmrCh == TMRA_CH_1) || (u8TmrCh == TMRA_CH_3));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32BCONRAddr = (uint32_t)&TMRAx->BCONR1 + (uint32_t)u8TmrCh * 4U;
    BIT_BAND(u32BCONRAddr, TMRA_BCONR_BEN_POS) = (uint32_t)enNewState;
}

/**
 * @brief  Specifies the operation when counting overflow/underflow.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32OvfOp               The operation when count overflow/underflow.
 *   @arg  TMRA_OVF_CNT_CONTINUE:       When counting overflow(or underflow), counting continue.
 *   @arg  TMRA_OVF_CNT_STOP:           When count overflow(or underflow), counting stop.
 * @retval None
 */
void TMRA_SetOvfOperation(M4_TMRA_TypeDef *TMRAx, uint32_t u32OvfOp)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_OVF_OPERATION(u32OvfOp));
    MODIFY_REG32(TMRAx->BCSTR, TMRA_BCSTR_OVSTP, u32OvfOp);
}

/**
 * @brief  Enable or disable synchronous-start. When an even unit enables synchronous-start function, \
 *         start the symmetric odd unit can start the even unit at the same time.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_2:                   TMRA unit 2 instance register base.
 *   @arg  M4_TMRA_4:                   TMRA unit 4 instance register base.
 *   @arg  M4_TMRA_6:                   TMRA unit 6 instance register base.
 *   @arg  M4_TMRA_8:                   TMRA unit 8 instance register base.
 *   @arg  M4_TMRA_10:                  TMRA unit 10 instance register base.
 *   @arg  M4_TMRA_12:                  TMRA unit 12 instance register base.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the synchronous start.
 *   @arg  Disable:                     Disable the synchronous start.
 * @retval None
 * @note   Only even units can be enabled/disabled synchronous-start function.
 * @note   Symmetric units: uint 1 and 2; uint 3 and 4; ...; uint 11 and 12.
 */
void TMRA_SyncStartCmd(M4_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_TMRA_EVEN_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Addr = (uint32_t)&TMRAx->BCSTR;
    BIT_BAND(u32Addr, TMRA_BCSTR_SYNST_POS) = (uint32_t)enNewState;
}

/**
 * @brief  Enable of disable the specified interrupts of the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32IntType             The interrupt type of TMRA. Set this parameter to 0xFFFFFFFF to select all interrupts.
 *                                      This parameter can be values of @ref TMRA_Interrupt_Type
 *   @arg  TMRA_INT_OVF:                Count overflow interrupt.
 *   @arg  TMRA_INT_UNF:                Count underflow interrupt.
 *   @arg  TMRA_INT_CMP_CH1:            Compare-match interrupt of channel 1.
 *   @arg  TMRA_INT_CMP_CH2:            Compare-match interrupt of channel 2.
 *   @arg  TMRA_INT_CMP_CH3:            Compare-match interrupt of channel 3.
 *   @arg  TMRA_INT_CMP_CH4:            Compare-match interrupt of channel 4.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified interrupts.
 *   @arg  Disable:                     Disable the specified interrupts.
 * @retval None
 */
void TMRA_IntCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint32_t u32BCSTR;
    uint32_t u32ICONR;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32IntType &= TMRA_INT_ALL;
    u32BCSTR    = u32IntType & TMRA_BCSTR_INT_MSK;
    u32ICONR    = u32IntType >> 16U;
    if (enNewState == Enable)
    {
        SET_REG32_BIT(TMRAx->BCSTR, u32BCSTR);
        SET_REG32_BIT(TMRAx->ICONR, u32ICONR);
    }
    else
    {
        CLEAR_REG32_BIT(TMRAx->BCSTR, u32BCSTR);
        CLEAR_REG32_BIT(TMRAx->ICONR, u32ICONR);
    }
}

/**
 * @brief  Enable of disable the specified event of the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32EvtType             The event type of TMRA. Set this parameter to 0xFFFF to select all events.
 *                                      This parameter can be values of @ref TMRA_Event_Type
 *   @arg  TMRA_EVENT_CMP_CH1:          Compare-match event of channel 1.
 *   @arg  TMRA_EVENT_CMP_CH2:          Compare-match event of channel 2.
 *   @arg  TMRA_EVENT_CMP_CH3:          Compare-match event of channel 3.
 *   @arg  TMRA_EVENT_CMP_CH4:          Compare-match event of channel 4.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified event.
 *   @arg  Disable:                     Disable the specified event.
 * @retval None
 */
void TMRA_EventCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32EvtType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32EvtType &= TMRA_EVENT_ALL;
    if (enNewState == Enable)
    {
        SET_REG32_BIT(TMRAx->ECONR, u32EvtType);
    }
    else
    {
        CLEAR_REG32_BIT(TMRAx->ECONR, u32EvtType);
    }
}

/**
 * @brief  Get the specified flag's status.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32Flag                The status flags of TMRA.
 *                                      This parameter can be values of @ref TMRA_Status_Flag
 *   @arg  TMRA_FLAG_OVF:               Count overflow flag.
 *   @arg  TMRA_FLAG_UNF:               Count underflow flag.
 *   @arg  TMRA_FLAG_CMP_CH1:           Compare-match flag of channel 1.
 *   @arg  TMRA_FLAG_CMP_CH2:           Compare-match flag of channel 2.
 *   @arg  TMRA_FLAG_CMP_CH3:           Compare-match flag of channel 3.
 *   @arg  TMRA_FLAG_CMP_CH4:           Compare-match flag of channel 4.
 * @retval An en_flag_status_t enumeration type value.
 *   @arg Set:                          At least one of the specified flags is set.
 *   @arg Reset:                        None of the specified flags is set.
 */
en_flag_status_t TMRA_GetStatus(const M4_TMRA_TypeDef *TMRAx, uint32_t u32Flag)
{
    uint32_t u32BCSTR;
    uint32_t u32STFLR;
    en_flag_status_t enFlag = Reset;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    u32Flag &= TMRA_FLAG_ALL;
    u32BCSTR = READ_REG32_BIT(TMRAx->BCSTR, (u32Flag & TMRA_BCSTR_FLAG_MSK));
    u32STFLR = READ_REG32_BIT(TMRAx->STFLR, (u32Flag >> 16U));

    if ((u32BCSTR != 0U) || (u32STFLR != 0U))
    {
        enFlag = Set;
    }

    return enFlag;
}

/**
 * @brief  Clear the specified flags' status.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32Flag                The status flags of TMRA. Set this parameter to 0xFFFFFFFF to select all status flags.
 *                                      This parameter can be values of @ref TMRA_Status_Flag
 *   @arg  TMRA_FLAG_OVF:               Count overflow flag.
 *   @arg  TMRA_FLAG_UNF:               Count underflow flag.
 *   @arg  TMRA_FLAG_CMP_CH1:           Count match flag of channel 1.
 *   @arg  TMRA_FLAG_CMP_CH2:           Count match flag of channel 2.
 *   @arg  TMRA_FLAG_CMP_CH3:           Count match flag of channel 3.
 *   @arg  TMRA_FLAG_CMP_CH4:           Count match flag of channel 4.
 * @retval None
 */
void TMRA_ClrStatus(M4_TMRA_TypeDef *TMRAx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    u32Flag &= TMRA_FLAG_ALL;
    TMRAx->BCSTR &= (uint32_t)(~(u32Flag & TMRA_BCSTR_FLAG_MSK));
    TMRAx->STFLR &= (uint32_t)(~(u32Flag >> 16U));
}

/**
 * @brief  Start the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @retval None
 */
void TMRA_Start(M4_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    SET_REG32_BIT(TMRAx->BCSTR, TMRA_BCSTR_START);
}

/**
 * @brief  Stop the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @retval None
 */
void TMRA_Stop(M4_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    CLEAR_REG32_BIT(TMRAx->BCSTR, TMRA_BCSTR_START);
}

/**
 * @brief  Specifies the counting direction for the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32CntDir              Count direction.
 *                                      This parameter can be a value of @ref TMRA_Count_Direction
 *   @arg  TMRA_DIR_DOWN:               TMRA count down.
 *   @arg  TMRA_DIR_UP:                 TMRA count up.
 * @retval None
 */
void TMRA_SetCntDir(M4_TMRA_TypeDef *TMRAx, uint32_t u32CntDir)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CNT_DIR(u32CntDir));
    MODIFY_REG32(TMRAx->BCSTR, TMRA_BCSTR_DIR, u32CntDir);
}

/**
 * @brief  Specifies the counting mode for the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32CntMode             Count mode.
 *                                      This parameter can be a value of @ref TMRA_Count_Mode
 *   @arg  TMRA_MODE_SAWTOOTH:          Count mode is sawtooth wave.
 *   @arg  TMRA_MODE_TRIANGLE:          Count mode is triangle wave.
 * @retval None
 */
void TMRA_SetCntMode(M4_TMRA_TypeDef *TMRAx, uint32_t u32CntMode)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CNT_MODE(u32CntMode));

    u32Addr = (uint32_t)&TMRAx->BCSTR;
    BIT_BAND(u32Addr, TMRA_BCSTR_SYNST_POS) = (uint32_t)u32CntMode;
}

/**
 * @brief  Specifies the divider of PCLK when the clock source is PCLK.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32ClkDiv              The clock source division.
 *                                      This parameter can be a value of @ref TMRA_PCLK_Divider
 *   @arg  TMRA_PCLK_DIV1:              The clock source of TMRA is PCLK.
 *   @arg  TMRA_PCLK_DIV2:              The clock source of TMRA is PCLK / 2.
 *   @arg  TMRA_PCLK_DIV4:              The clock source of TMRA is PCLK / 4.
 *   @arg  TMRA_PCLK_DIV8:              The clock source of TMRA is PCLK / 8.
 *   @arg  TMRA_PCLK_DIV16:             The clock source of TMRA is PCLK / 16.
 *   @arg  TMRA_PCLK_DIV32:             The clock source of TMRA is PCLK / 32.
 *   @arg  TMRA_PCLK_DIV64:             The clock source of TMRA is PCLK / 64.
 *   @arg  TMRA_PCLK_DIV128:            The clock source of TMRA is PCLK / 128.
 *   @arg  TMRA_PCLK_DIV256:            The clock source of TMRA is PCLK / 256.
 *   @arg  TMRA_PCLK_DIV512:            The clock source of TMRA is PCLK / 512.
 *   @arg  TMRA_PCLK_DIV1024:           The clock source of TMRA is PCLK / 1024.
 * @retval None
 */
void TMRA_SetPCLKDiv(M4_TMRA_TypeDef *TMRAx, uint32_t u32ClkDiv)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_PCLK_DIV(u32ClkDiv));
    MODIFY_REG32(TMRAx->BCSTR, TMRA_BCSTR_CKDIV, u32ClkDiv);
}

/**
 * @brief  Get the counting direction of the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA1 ~ M4_TMRA12:        TMRA unit 1 ~ 12 instance register base.
 * @retval An uint32_t type value of counting direction.
 *   @arg  TMRA_DIR_DOWN:               TMRA count goes down.
 *   @arg  TMRA_DIR_UP:                 TMRA count goes up.
 */
uint32_t TMRA_GetCntDir(const M4_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    return READ_REG32_BIT(TMRAx->BCSTR, TMRA_BCSTR_DIR);
}

/**
 * @brief  Specifies the clock source for the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA1 ~ M4_TMRA12:        TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32ClkSrc              The clock source of TMRA.
 *                                      This parameter can be values of @ref TMRA_Clock_Source
 * @retval None
 */
void TMRA_SetClkSrc(M4_TMRA_TypeDef *TMRAx, uint32_t u32ClkSrc)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    WRITE_REG32(TMRAx->HCUPR, (u32ClkSrc & TMRA_CLK_HW_UP_ALL));
    WRITE_REG32(TMRAx->HCDOR, ((u32ClkSrc & TMRA_CLK_HW_DOWN_ALL) >> 16U));
}

/**
 * @brief  Enable or disable the specified hardware clock source of the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA1 ~ M4_TMRA12:        TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u32HwClkSrc            The hardware clock source of TMRA.
 *                                      This parameter can be values of @ref TMRA_Clock_Source except TMRA_CLK_PCLK
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg Enable:                       Enable the specified hardware clock source.
 *   @arg Disable:                      Disable the specified hardware clock source.
 * @retval None
 */
void TMRA_HwClkSrcCmd(M4_TMRA_TypeDef *TMRAx, uint32_t u32HwClkSrc, en_functional_state_t enNewState)
{
    const uint32_t u32HwCntUpClk   = u32HwClkSrc & TMRA_CLK_HW_UP_ALL;
    const uint32_t u32HwCntDownClk = (u32HwClkSrc & TMRA_CLK_HW_DOWN_ALL) >> 16U;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));
    if (enNewState == Enable)
    {
        SET_REG32_BIT(TMRAx->HCUPR, u32HwCntUpClk);
        SET_REG32_BIT(TMRAx->HCDOR, u32HwCntDownClk);
    }
    else
    {
        CLEAR_REG32_BIT(TMRAx->HCUPR, u32HwCntUpClk);
        CLEAR_REG32_BIT(TMRAx->HCDOR, u32HwCntDownClk);
    }
}

/**
 * @brief  Specifies the PWM polarity when counting start.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Start_Polarity
 *   @arg  TMRA_PWM_START_LOW:          The polarity of PWM output is low.
 *   @arg  TMRA_PWM_START_HIGH:         The polarity of PWM output is high.
 *   @arg  TMRA_PWM_START_KEEP:         The polarity of PWM output keeps the current polarity.
 * @retval None
 */
void TMRA_PWM_SetStartPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
    DDL_ASSERT(IS_TMRA_PWM_START_POLARITY(u32Polarity));

    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
    MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_STAC, u32Polarity);
}

/**
 * @brief  Specifies the PWM polarity when counting stop.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Stop_Polarity
 *   @arg  TMRA_PWM_STOP_LOW:           The polarity of PWM output is low.
 *   @arg  TMRA_PWM_STOP_HIGH:          The polarity of PWM output is high.
 *   @arg  TMRA_PWM_STOP_KEEP:          The polarity of PWM output keeps the current polarity.
 * @retval None
 */
void TMRA_PWM_SetStopPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
    DDL_ASSERT(IS_TMRA_PWM_STOP_POLARITY(u32Polarity));

    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
    MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_STPC, u32Polarity);
}

/**
 * @brief  Specifies the PWM polarity when counting matches the compare reference value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Match_Cmp_Polarity
 *   @arg  TMRA_PWM_CMP_LOW:            The polarity of PWM output is low.
 *   @arg  TMRA_PWM_CMP_HIGH:           The polarity of PWM output is high.
 *   @arg  TMRA_PWM_CMP_KEEP:           The polarity of PWM output keeps the current polarity.
 *   @arg  TMRA_PWM_CMP_REVERSE:        PWM output reverses the current polarity.
 * @retval None
 */
void TMRA_PWM_SetMatchCmpPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
    DDL_ASSERT(IS_TMRA_PWM_CMP_POLARITY(u32Polarity));

    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
    MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_CMPC, u32Polarity);
}

/**
 * @brief  Specifies the PWM polarity when counting matches the period reference value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Match_Period_Polarity
 *   @arg  TMRA_PWM_PERIOD_LOW:         The polarity of PWM output is low.
 *   @arg  TMRA_PWM_PERIOD_HIGH:        The polarity of PWM output is high.
 *   @arg  TMRA_PWM_PERIOD_KEEP:        The polarity of PWM output keeps the current polarity.
 *   @arg  TMRA_PWM_PERIOD_REVERSE:     PWM output reverses the current polarity.
 * @retval None
 */
void TMRA_PWM_SetMatchPeriodPolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
    DDL_ASSERT(IS_TMRA_PWM_PERIOD_POLARITY(u32Polarity));

    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
    MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_PERC, u32Polarity);
}

/**
 * @brief  Specifies the PWM polarity when next cycle start.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32Polarity            Polarity of PWM output.
 *                                      This parameter can be a value of @ref TMRA_PWM_Force_Polarity
 *   @arg  TMRA_PWM_FORCE_INVALID:      Force polarity is invalid.
 *   @arg  TMRA_PWM_FORCE_LOW:          Force the PWM output low at the beginning of the next cycle. \
 *                                      The beginning of the next cycle: overflow position or underflow position \
 *                                      of sawtooth wave; valley position of triangle wave.
 *   @arg  TMRA_PWM_FORCE_HIGH:         Force the PWM output high at the beginning of the next cycle. \
 *                                      The beginning of the next cycle: overflow position or underflow position \
 *                                      of sawtooth wave; valley position of triangle wave.
 * @retval None
 */
void TMRA_PWM_SetForcePolarity(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32Polarity)
{
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
    DDL_ASSERT(IS_TMRA_PWM_FORCE_POLARITY(u32Polarity));

    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (uint32_t)u8TmrCh * 4U;
    MODIFY_REG32(RW_MEM32(u32PCONRAddr), TMRA_PCONR_FORC, u32Polarity);
}

/**
 * @brief  Specifies the capture condition for the specified channel.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32CaptCond            The capture condition. Set this parameter to 0xFFFF to select all the conditions of capturing start.
 *                                      This parameter can be values of @ref TMRA_Channel_Capture_Condition
 *   @arg  TMRA_CAPT_COND_PWMR:         The condition of capture is a rising edge is sampled on PWM(pin).
 *   @arg  TMRA_CAPT_COND_PWMF:         The condition of capture is a falling edge is sampled on PWM(pin).
 *   @arg  TMRA_CAPT_COND_EVENT:        The condition of capture is the specified event occurred.
 *   @arg  TMRA_CAPT_COND_TRIGR:        The condition of capture is a rising edge is sampled on TRIG.
 *   @arg  TMRA_CAPT_COND_TRIGF:        The condition of capture is a falling edge is sampled on TRIG.
 * @param  [in]  enNewState             An @ref en_functional_state_t value.
 *   @arg  Enable:                      Enable the sepcified capture conditions.
 *   @arg  Disable:                     Disable the sepcified capture conditions.
 * @retval None
 */
void TMRA_CaptCondCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32CaptCond, en_functional_state_t enNewState)
{
    uint32_t u32CCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CH(u8TmrCh));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32CaptCond &= TMRA_CAPT_COND_ALL;
    u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (uint32_t)u8TmrCh * 4U;
    if (enNewState == Enable)
    {
        SET_REG32_BIT(RW_MEM32(u32CCONRAddr), u32CaptCond);
    }
    else
    {
        CLEAR_REG32_BIT(RW_MEM32(u32CCONRAddr), u32CaptCond);
    }
}

/**
 * @brief  Enable or disable the specified hardware start condition.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  M4_TMRA_1 ~ M4_TMRA_12:      TMRA unit 1 ~ 12 instance register base.
 * @param  [in]  u8TmrCh                TMRA channel number.
 *                                      This parameter can be a value of @ref TMRA_Channel
 *   @arg  TMRA_CH_1:                   Channel 1 of TMRA.
 *   @arg  TMRA_CH_2:                   Channel 2 of TMRA.
 *   @arg  TMRA_CH_3:                   Channel 3 of TMRA.
 *   @arg  TMRA_CH_4:                   Channel 4 of TMRA.
 * @param  [in]  u32TrigCond            The trigger condition.
 *                                      This parameter can be a value of:
 *                                      @ref TMRA_Hardware_Start_Condition
 *                                      @ref TMRA_Hardware_Stop_Condition
 *                                      @ref TMRA_Hardware_Clear_Condition
 *   @arg  TMRA_START_COND_TRIGR:       1. Sync start is invalid: The condition is that a rising edge is sampled on TRIG of the current TMRA unit. \
 *                                      2. Sync start is valid: The condition is that a rising edge is sampled on TRIG of the symmetric TMRA unit.
 *   @arg  TMRA_START_COND_TRIGF:       1. Sync start is invalid: The condition is that a falling edge is sampled on TRIG of the current TMRA unit. \
 *                                      2. Sync start is valid: The condition is that a falling edge is sampled on TRIG of the symmetric TMRA unit.
 *   @arg  TMRA_START_COND_EVENT:       The condition is that the event which is set in register TMRA_HTSSR0 has occurred.
 *   @arg  TMRA_STOP_COND_TRIGR:        The condition is that a rising edge is sampled on pin TRIG of the current TMRA unit.
 *   @arg  TMRA_STOP_COND_TRIGF:        The condition is that a falling edge is sampled on pin TRIG of the current TMRA unit.
 *   @arg  TMRA_STOP_COND_EVENT:        The condition is that the event which is set in register TMRA_HTSSR0 has occurred.
 *   @arg  TMRA_CLR_COND_TRIGR:         The condition is that a rising edge is sampled on TRIG of the current TMRA unit.
 *   @arg  TMRA_CLR_COND_TRIGF:         The condition is that a falling edge is sampled on TRIG of the current TMRA unit.
 *   @arg  TMRA_CLR_COND_EVENT:         The condition is that the event which is set in register TMRA_HTSSR0 has occurred.
 *   @arg  TMRA_CLR_COND_SYM_TRIGR:     The condition is that a rising edge is sampled on TRIG of the symmetric unit.
 *   @arg  TMRA_CLR_COND_SYM_TRIGF:     The condition is that a falling edge is sampled on TRIG of the symmetric unit.
 *   @arg  TMRA_CLR_COND_PWM3R:         The condition is that a rising edge is sampled on PWM3 of the current TMRA unit.
 *   @arg  TMRA_CLR_COND_PWM3F:         The condition is that a falling edge is sampled on PWM3 of the current TMRA unit.
 * @param  [in]  enNewState             An en_functional_state_t enumeration type value.
 *   @arg  Enable:                      Enable the specified hardware start condition.
 *   @arg  Disable:                     Disable the specified hardware start condition.
 * @retval None
 */
void TMRA_TrigCondCmd(M4_TMRA_TypeDef *TMRAx, uint8_t u8TmrCh, uint32_t u32TrigCond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32TrigCond &= TMRA_TRIG_COND_MSK;
    if (enNewState == Enable)
    {
        SET_REG32_BIT(TMRAx->HCONR, u32TrigCond);
    }
    else
    {
        CLEAR_REG32_BIT(TMRAx->HCONR, u32TrigCond);
    }
}

/**
 * @}
 */

#endif /* DDL_TMRA_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
