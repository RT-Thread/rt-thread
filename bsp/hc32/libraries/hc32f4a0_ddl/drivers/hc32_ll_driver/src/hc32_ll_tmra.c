/**
 *******************************************************************************
 * @file  hc32_ll_tmra.c
 * @brief This file provides firmware functions to manage the TMRA(TimerA).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
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
#include "hc32_ll_tmra.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_TMRA TMRA
 * @brief TMRA Driver Library
 * @{
 */

#if (LL_TMRA_ENABLE == DDL_ON)

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
 * @defgroup TMRA_Registers_Setting_definition TMRA Registers setting definition
 * @{
 */
#define TMRA_REG_TYPE                       uint16_t
#define TMRA_REG_VALUE_MAX                  (0xFFFFUL)

#define SET_VAL_BY_ADDR(addr, v)            (*(__IO TMRA_REG_TYPE *)(addr)) = (TMRA_REG_TYPE)(v)
#define GET_VAL_BY_ADDR(addr)               (*(__IO TMRA_REG_TYPE *)(addr))
/**
 * @}
 */

/**
 * @defgroup TMRA_Configuration_Bit_Mask TMRA Configuration Bit Mask
 * @{
 */
#define TMRA_BCSTR_INT_MASK                 (TMRA_BCSTR_ITENUDF | TMRA_BCSTR_ITENOVF)
#define TMRA_BCSTR_FLAG_MASK                (TMRA_BCSTR_UDFF | TMRA_BCSTR_OVFF)
#define TMRA_FCONR_FILTER_CLK_MASK          (0x3UL)
#define TMRA_CCONR_FILTER_CLK_MASK          (TMRA_CCONR_NOFICKCP)
#define TMRA_PWM_POLARITY_MASK              (TMRA_PCONR_STAC)
/**
 * @}
 */

/**
 * @defgroup TMRA_Filter_Pin_Max TMRA Pin With Filter Max
 * @note TMRA_1 and TMRA_2 of HC32M423 do NOT contain pin TMRA_PIN_PWM2.
 * @{
 */
#define TMRA_PIN_MAX                        (TMRA_PIN_PWM4)
/**
 * @}
 */

/**
 * @defgroup TMRA_Check_Parameters_Validity TMRA check parameters validity
 * @{
 */
#define IS_TMRA_BIT_MASK(x, mask)   (((x) != 0U) && (((x) | (mask)) == (mask)))

/* Unit check */
#define IS_TMRA_UNIT(x)                                                        \
(   ((x) == CM_TMRA_1)                      ||                                 \
    ((x) == CM_TMRA_2)                      ||                                 \
    ((x) == CM_TMRA_3)                      ||                                 \
    ((x) == CM_TMRA_4)                      ||                                 \
    ((x) == CM_TMRA_5)                      ||                                 \
    ((x) == CM_TMRA_6)                      ||                                 \
    ((x) == CM_TMRA_7)                      ||                                 \
    ((x) == CM_TMRA_8)                      ||                                 \
    ((x) == CM_TMRA_9)                      ||                                 \
    ((x) == CM_TMRA_10)                     ||                                 \
    ((x) == CM_TMRA_11)                     ||                                 \
    ((x) == CM_TMRA_12))

/* Sync unit check */
#define IS_TMRA_SYNC_UNIT(x)                                                   \
(   ((x) == CM_TMRA_2)                      ||                                 \
    ((x) == CM_TMRA_4)                      ||                                 \
    ((x) == CM_TMRA_6)                      ||                                 \
    ((x) == CM_TMRA_8)                      ||                                 \
    ((x) == CM_TMRA_10)                     ||                                 \
    ((x) == CM_TMRA_12))

#define IS_TMRA_CH(x)               ((x) <= TMRA_CH4)

/* Unit and channel */
#define IS_TMRA_UNIT_CH(unit, ch)   (IS_TMRA_UNIT(unit) && IS_TMRA_CH(ch))

#define IS_TMRA_CNT_SRC(x)          (((x) == TMRA_CNT_SRC_SW) || ((x) == TMRA_CNT_SRC_HW))

#define IS_TMRA_FUNC(x)             (((x) == TMRA_FUNC_CMP) || ((x) == TMRA_FUNC_CAPT))

#define IS_TMRA_DIR(x)              (((x) == TMRA_DIR_DOWN) || ((x) == TMRA_DIR_UP))

#define IS_TMRA_MD(x)               (((x) == TMRA_MD_SAWTOOTH) || ((x) == TMRA_MD_TRIANGLE))

/* Counter reload */
#define IS_TMRA_CNT_RELOAD(x)       (((x) == TMRA_CNT_RELOAD_DISABLE) || ((x) == TMRA_CNT_RELOAD_ENABLE))

#define IS_TMRA_CMPVAL_BUF_CH(x)    (((x) == TMRA_CH1) || ((x) == TMRA_CH3))

#define IS_TMRA_CLK_DIV(x)                                                     \
(   ((x) == TMRA_CLK_DIV1)                  ||                                 \
    ((x) == TMRA_CLK_DIV2)                  ||                                 \
    ((x) == TMRA_CLK_DIV4)                  ||                                 \
    ((x) == TMRA_CLK_DIV8)                  ||                                 \
    ((x) == TMRA_CLK_DIV16)                 ||                                 \
    ((x) == TMRA_CLK_DIV32)                 ||                                 \
    ((x) == TMRA_CLK_DIV64)                 ||                                 \
    ((x) == TMRA_CLK_DIV128)                ||                                 \
    ((x) == TMRA_CLK_DIV256)                ||                                 \
    ((x) == TMRA_CLK_DIV512)                ||                                 \
    ((x) == TMRA_CLK_DIV1024))

#define IS_TMRA_FILTER_PIN(x)           ((x) <= TMRA_PIN_MAX)

#define IS_TMRA_CNT_UP_COND(x)          IS_TMRA_BIT_MASK(x, TMRA_CNT_UP_COND_ALL)

#define IS_TMRA_CNT_DOWN_COND(x)        IS_TMRA_BIT_MASK(x, TMRA_CNT_DOWN_COND_ALL)

#define IS_TMRA_INT(x)                  IS_TMRA_BIT_MASK(x, TMRA_INT_ALL)

#define IS_TMRA_EVT(x)                  IS_TMRA_BIT_MASK(x, TMRA_EVT_ALL)

#define IS_TMRA_FLAG(x)                 IS_TMRA_BIT_MASK(x, TMRA_FLAG_ALL)

#define IS_TMRA_CAPT_COND(x)            IS_TMRA_BIT_MASK(x, TMRA_CAPT_COND_ALL)

#define IS_TMRA_FILTER_CLK_DIV(x)       ((x) <= TMRA_FILTER_CLK_DIV64)

/* Special check of TMRA_1 & TMRA_2 of HC32M423 */

/* Unit and interrupt */
#define IS_TMRA_UNIT_INT(u, x)      (IS_TMRA_UNIT(u) && IS_TMRA_INT(x))

/* Unit and event of channel */
#define IS_TMRA_CH_EVT(u, x)        (IS_TMRA_UNIT(u) && IS_TMRA_EVT(x))

/* Unit and pin with filter */
#define IS_TMRA_UNIT_FPIN(u, x)     (IS_TMRA_UNIT(u) && IS_TMRA_FILTER_PIN(x))

/* Unit and flag */
#define IS_TMRA_UNIT_FLAG(u, x)     (IS_TMRA_UNIT(u) && IS_TMRA_FLAG(x))

#define IS_TMRA_CMPVAL_BUF_COND(x)                                             \
(   ((x) == TMRA_BUF_TRANS_COND_OVF_UDF_CLR)    ||                             \
    ((x) == TMRA_BUF_TRANS_COND_PEAK)           ||                             \
    ((x) == TMRA_BUF_TRANS_COND_VALLEY)         ||                             \
    ((x) == TMRA_BUF_TRANS_COND_PEAK_VALLEY))

#define IS_TMRA_PWM_START_POLARITY(x)                                          \
(   ((x) == TMRA_PWM_LOW)                   ||                                 \
    ((x) == TMRA_PWM_HIGH)                  ||                                 \
    ((x) == TMRA_PWM_HOLD))

#define IS_TMRA_PWM_STOP_POLARITY(x)                                           \
(   ((x) == TMRA_PWM_LOW)                   ||                                 \
    ((x) == TMRA_PWM_HIGH)                  ||                                 \
    ((x) == TMRA_PWM_HOLD))

#define IS_TMRA_PWM_CMP_POLARITY(x)                                            \
(   ((x) == TMRA_PWM_LOW)                   ||                                 \
    ((x) == TMRA_PWM_HIGH)                  ||                                 \
    ((x) == TMRA_PWM_HOLD)                  ||                                 \
    ((x) == TMRA_PWM_INVT))

#define IS_TMRA_PWM_PERIOD_POLARITY(x)                                         \
(   ((x) == TMRA_PWM_LOW)                   ||                                 \
    ((x) == TMRA_PWM_HIGH)                  ||                                 \
    ((x) == TMRA_PWM_HOLD)                  ||                                 \
    ((x) == TMRA_PWM_INVT))

#define IS_TMRA_PWM_FORCE_POLARITY(x)                                          \
(   ((x) == TMRA_PWM_FORCE_INVD)            ||                                 \
    ((x) == TMRA_PWM_FORCE_LOW)             ||                                 \
    ((x) == TMRA_PWM_FORCE_HIGH))

#define IS_TMRA_PWM_POLARITY(st, pol)                                          \
(   (((st) == TMRA_CNT_STAT_START) && IS_TMRA_PWM_START_POLARITY(pol))      || \
    (((st) == TMRA_CNT_STAT_STOP) && IS_TMRA_PWM_STOP_POLARITY(pol))        || \
    (((st) == TMRA_CNT_STAT_MATCH_CMP) && IS_TMRA_PWM_CMP_POLARITY(pol))    || \
    (((st) == TMRA_CNT_STAT_MATCH_PERIOD) && IS_TMRA_PWM_PERIOD_POLARITY(pol)))

#define IS_TMRA_START_COND(x)       IS_TMRA_BIT_MASK((x), TMRA_START_COND_ALL)

#define IS_TMRA_STOP_COND(x)        IS_TMRA_BIT_MASK((x), TMRA_STOP_COND_ALL)

#define IS_TMRA_CLR_COND(x)         IS_TMRA_BIT_MASK((x), TMRA_CLR_COND_ALL)

/**
 * @}
 */

/**
 * @defgroup TMRA_Miscellaneous_Macros TMRA Miscellaneous Macros
 * @{
 */
#define TMRA_PIN_PWM_OFFSET         (3U)

#define TMRA_CH_NUM                 (4U)
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
 * @brief  Initializes the specified TMRA peripheral according to the specified parameters
 *         in the structure stc_tmra_init_t
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  pstcTmraInit           Pointer to a stc_tmra_init_t structure value that
 *                                      contains the configuration information for the TMRA.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcTmraInit == NULL.
 */
int32_t TMRA_Init(CM_TMRA_TypeDef *TMRAx, const stc_tmra_init_t *pstcTmraInit)
{
    int32_t i32Ret  = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    if (pstcTmraInit != NULL) {
        DDL_ASSERT(IS_TMRA_CNT_SRC(pstcTmraInit->u8CountSrc));

        if (pstcTmraInit->u8CountSrc == TMRA_CNT_SRC_SW) {
            DDL_ASSERT(IS_TMRA_MD(pstcTmraInit->sw_count.u16CountMode));
            DDL_ASSERT(IS_TMRA_DIR(pstcTmraInit->sw_count.u16CountDir));
            DDL_ASSERT(IS_TMRA_CLK_DIV(pstcTmraInit->sw_count.u16ClockDiv));

            WRITE_REG16(TMRAx->BCSTR, pstcTmraInit->sw_count.u16CountMode | \
                        pstcTmraInit->sw_count.u16CountDir  | \
                        pstcTmraInit->sw_count.u16ClockDiv);
        } else {
            DDL_ASSERT(IS_TMRA_CNT_UP_COND(pstcTmraInit->hw_count.u16CountUpCond) || \
                       (pstcTmraInit->hw_count.u16CountUpCond == TMRA_CNT_UP_COND_INVD));
            DDL_ASSERT(IS_TMRA_CNT_DOWN_COND(pstcTmraInit->hw_count.u16CountDownCond) || \
                       (pstcTmraInit->hw_count.u16CountDownCond == TMRA_CNT_DOWN_COND_INVD));
            WRITE_REG16(TMRAx->HCUPR, pstcTmraInit->hw_count.u16CountUpCond);
            WRITE_REG16(TMRAx->HCDOR, pstcTmraInit->hw_count.u16CountDownCond);
        }

        /* Counter reload */
        DDL_ASSERT(IS_TMRA_CNT_RELOAD(pstcTmraInit->u16CountReload));
        MODIFY_REG16(TMRAx->BCSTR, TMRA_BCSTR_OVSTP, pstcTmraInit->u16CountReload);

        /* Specifies period value. */
        TMRA_SetPeriodValue(TMRAx, pstcTmraInit->u32PeriodValue);

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set a default value for the TMRA initialization structure.
 * @param  [out] pstcTmraInit           Pointer to a stc_tmra_init_t structure value that
 *                                      contains the configuration information for the TMRA.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcTmraInit == NULL.
 */
int32_t TMRA_StructInit(stc_tmra_init_t *pstcTmraInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcTmraInit != NULL) {
        pstcTmraInit->u8CountSrc            = TMRA_CNT_SRC_SW;
        pstcTmraInit->sw_count.u16ClockDiv  = TMRA_CLK_DIV1;
        pstcTmraInit->sw_count.u16CountMode = TMRA_MD_SAWTOOTH;
        pstcTmraInit->sw_count.u16CountDir  = TMRA_DIR_UP;
        pstcTmraInit->u32PeriodValue        = (TMRA_REG_TYPE)0xFFFFFFFFUL;
        /* Counter reload */
        pstcTmraInit->u16CountReload = TMRA_CNT_RELOAD_ENABLE;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Specifies the counting mode for the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u16Mode                Count mode.
 *                                      This parameter can be a value of @ref TMRA_Count_Mode
 *   @arg  TMRA_MD_SAWTOOTH:            Count mode is sawtooth wave.
 *   @arg  TMRA_MD_TRIANGLE:            Count mode is triangle wave.
 * @retval None
 */
void TMRA_SetCountMode(CM_TMRA_TypeDef *TMRAx, uint16_t u16Mode)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_MD(u16Mode));
    MODIFY_REG16(TMRAx->BCSTR, TMRA_BCSTR_MODE, u16Mode);
}

/**
 * @brief  Specifies the counting direction for the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u16Dir                 Count direction.
 *                                      This parameter can be a value of @ref TMRA_Count_Dir
 *   @arg  TMRA_DIR_DOWN:               TMRA count down.
 *   @arg  TMRA_DIR_UP:                 TMRA count up.
 * @retval None
 */
void TMRA_SetCountDir(CM_TMRA_TypeDef *TMRAx, uint16_t u16Dir)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_DIR(u16Dir));
    MODIFY_REG16(TMRAx->BCSTR, TMRA_BCSTR_DIR, u16Dir);
}

/**
 * @brief  Specifies the clcok divider for the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u16Div                 Clcok divider.
 *                                      This parameter can be a value of @ref TMRA_Clock_Divider
 * @retval None
 */
void TMRA_SetClockDiv(CM_TMRA_TypeDef *TMRAx, uint16_t u16Div)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CLK_DIV(u16Div));
    MODIFY_REG16(TMRAx->BCSTR, TMRA_BCSTR_CKDIV, u16Div);
}

/**
 * @brief  Enable or disable the specified hardware count up condition.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u16Cond                Hardware count up condition.
 *                                      This parameter can be values of @ref TMRA_Hard_Count_Up_Condition
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_HWCountUpCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CNT_UP_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(TMRAx->HCUPR, u16Cond);
    } else {
        CLR_REG16_BIT(TMRAx->HCUPR, u16Cond);
    }
}

/**
 * @brief  Enable or disable the specified hardware count down condition.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u16Cond                Hardware count down condition.
 *                                      This parameter can be values of @ref TMRA_Hard_Count_Down_Condition
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_HWCountDownCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CNT_DOWN_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(TMRAx->HCDOR, u16Cond);
    } else {
        CLR_REG16_BIT(TMRAx->HCDOR, u16Cond);
    }
}

/**
 * @brief  Specifies function mode of TMRA.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u16Func                Function mode of TRMA.
 *                                      This parameter can be a value of @ref TMRA_Function_Mode
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be a value of @ref TMRA_Channel
 * @retval None
 */
void TMRA_SetFunc(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Func)
{
    uint32_t u32CCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_TMRA_FUNC(u16Func));

    u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (u32Ch * 4U);
    MODIFY_REG16(RW_MEM16(u32CCONRAddr), TMRA_CCONR_CAPMD, u16Func);
}

/**
 * @brief  Initializes the PWM according to the specified parameters
 *         in the structure stc_tmra_pwm_init_t
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  pstcPwmInit            Pointer to a stc_tmra_pwm_init_t structure value that
 *                                      contains the configuration information for PWM.
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be a value of @ref TMRA_Channel
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcPwmInit == NULL.
 */
int32_t TMRA_PWM_Init(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, const stc_tmra_pwm_init_t *pstcPwmInit)
{
    uint32_t u32CMPARAddr;
    uint32_t u32PCONRAddr;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_TMRA_UNIT_CH(TMRAx, u32Ch));

    if (pstcPwmInit != NULL) {
        DDL_ASSERT(IS_TMRA_PWM_START_POLARITY(pstcPwmInit->u16StartPolarity));
        DDL_ASSERT(IS_TMRA_PWM_STOP_POLARITY(pstcPwmInit->u16StopPolarity));
        DDL_ASSERT(IS_TMRA_PWM_CMP_POLARITY(pstcPwmInit->u16CompareMatchPolarity));
        DDL_ASSERT(IS_TMRA_PWM_PERIOD_POLARITY(pstcPwmInit->u16PeriodMatchPolarity));

        u32Ch *= 4U;
        u32CMPARAddr = (uint32_t)&TMRAx->CMPAR1 + u32Ch;
        SET_VAL_BY_ADDR(u32CMPARAddr, pstcPwmInit->u32CompareValue);

        u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + u32Ch;
        RW_MEM16(u32PCONRAddr) = (uint16_t)((pstcPwmInit->u16StartPolarity << TMRA_PCONR_STAC_POS) | \
                                            (pstcPwmInit->u16StopPolarity << TMRA_PCONR_STPC_POS)  | \
                                            (pstcPwmInit->u16CompareMatchPolarity << TMRA_PCONR_CMPC_POS) | \
                                            (pstcPwmInit->u16PeriodMatchPolarity << TMRA_PCONR_PERC_POS));
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set a default value for the PWM initialization structure.
 * @param  [out] pstcPwmInit            Pointer to a stc_tmra_pwm_init_t structure value that
 *                                      contains the configuration information for PWM.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcPwmInit == NULL.
 */
int32_t TMRA_PWM_StructInit(stc_tmra_pwm_init_t *pstcPwmInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcPwmInit != NULL) {
        pstcPwmInit->u32CompareValue         = TMRA_REG_VALUE_MAX;
        pstcPwmInit->u16StartPolarity        = TMRA_PWM_HIGH;
        pstcPwmInit->u16StopPolarity         = TMRA_PWM_LOW;
        pstcPwmInit->u16CompareMatchPolarity = TMRA_PWM_INVT;
        pstcPwmInit->u16PeriodMatchPolarity  = TMRA_PWM_INVT;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable the PWM ouput of the specified channel.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be a value of @ref TMRA_Channel
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_PWM_OutputCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, en_functional_state_t enNewState)
{
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (u32Ch * 4U);
    WRITE_REG32(PERIPH_BIT_BAND(u32PCONRAddr, TMRA_PCONR_OUTEN_POS), enNewState);
}

/**
 * @brief  Specifies the ouput polarity of the PWM at the specified state of counter.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be a value @ref TMRA_Channel
 * @param  [in]  u8CountState           TMRA counter state.
 *                                      This parameter can be a value @ref TMRA_Counter_State
 * @param  [in]  u16Polarity            The polarity of PWM.
 *                                      This parameter can be a value @ref TMRA_PWM_Polarity
 * @retval None
 * @note   The polarity(high or low) of couting start is only valid when the clock is not divided(BCSTR.CKDIV == 0).
 */
void TMRA_PWM_SetPolarity(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint8_t u8CountState, uint16_t u16Polarity)
{
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_TMRA_PWM_POLARITY(u8CountState, u16Polarity));

    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (u32Ch * 4U);
    MODIFY_REG16(RW_MEM16(u32PCONRAddr),
                 (uint16_t)TMRA_PWM_POLARITY_MASK << (u8CountState * 2U),
                 u16Polarity << (u8CountState * 2U));
}

/**
 * @brief  Specifies the force polarity of the PWM.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be a value @ref TMRA_Channel
 * @param  [in]  u16Polarity            The force polarity of PWM.
 *                                      This parameter can be a value @ref TMRA_PWM_Force_Polarity
 * @retval None
 */
void TMRA_PWM_SetForcePolarity(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Polarity)
{
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_TMRA_PWM_FORCE_POLARITY(u16Polarity));

    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1 + (u32Ch * 4U);
    MODIFY_REG16(RW_MEM16(u32PCONRAddr), TMRA_PCONR_FORC, u16Polarity);
}

/**
 * @brief  Enable or disable the specified capture condition.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be a value @ref TMRA_Channel
 * @param  [in]  u16Cond                The capture condition.
 *                                      This parameter can be a value @ref TMRA_Capture_Cond
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_HWCaptureCondCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Cond, en_functional_state_t enNewState)
{
    uint32_t u32CCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT_CH(TMRAx, u32Ch));
    DDL_ASSERT(IS_TMRA_CAPT_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

#if defined __DEBUG
    if ((u16Cond & (TMRA_CAPT_COND_TRIG_RISING | TMRA_CAPT_COND_TRIG_FALLING)) != 0U) {
        DDL_ASSERT(u32Ch == TMRA_CH3);
    }
#endif

    u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + (u32Ch * 4U);
    if (enNewState == ENABLE) {
        SET_REG16_BIT(RW_MEM16(u32CCONRAddr), u16Cond);
    } else {
        CLR_REG16_BIT(RW_MEM16(u32CCONRAddr), u16Cond);
    }
}

/**
 * @brief  Enable or disable hardware start condition.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u16Cond                Hardware start condition.
 *                                      This parameter can be a value @ref TMRA_Hardware_Start_Condition
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_HWStartCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_START_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(TMRAx->HCONR, u16Cond);
    } else {
        CLR_REG16_BIT(TMRAx->HCONR, u16Cond);
    }
}

/**
 * @brief  Enable or disable hardware stop condition.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u16Cond                Hardware stop condition.
 *                                      This parameter can be a value @ref TMRA_Hardware_Stop_Condition
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_HWStopCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_STOP_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(TMRAx->HCONR, u16Cond);
    } else {
        CLR_REG16_BIT(TMRAx->HCONR, u16Cond);
    }
}

/**
 * @brief  Enable or disable hardware clear condition.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u16Cond                Hardware clear condition.
 *                                      This parameter can be a value @ref TMRA_Hardware_Clear_Condition
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_HWClearCondCmd(CM_TMRA_TypeDef *TMRAx, uint16_t u16Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CLR_COND(u16Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(TMRAx->HCONR, u16Cond);
    } else {
        CLR_REG16_BIT(TMRAx->HCONR, u16Cond);
    }
}

/**
 * @brief  Specifies the clock divider of filter.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Pin                 The pin with filter of TMRA.
 *                                      This parameter can be a value of @ref TMRA_Filter_Pin
 * @param  [in]  u16Div                 The clock source divider of the filter.
 *                                      This parameter can be a value of @ref TMRA_Filter_Clock_Divider
 *   @arg  TMRA_FILTER_CLK_DIV1:        The filter clock is the clock of timerA / 1.
 *   @arg  TMRA_FILTER_CLK_DIV4:        The filter clock is the clock of timerA / 4.
 *   @arg  TMRA_FILTER_CLK_DIV16:       The filter clock is the clock of timerA / 16.
 *   @arg  TMRA_FILTER_CLK_DIV64:       The filter clock is the clock of timerA / 64.
 * @retval None
 */
void TMRA_SetFilterClockDiv(CM_TMRA_TypeDef *TMRAx, uint32_t u32Pin, uint16_t u16Div)
{
    uint32_t u32Ch;
    uint32_t u32CCONRAddr;
    const uint8_t au8Offset[] = {
        TMRA_FCONR_NOFICKTG_POS, TMRA_FCONR_NOFICKCA_POS, TMRA_FCONR_NOFICKCB_POS,
    };

    DDL_ASSERT(IS_TMRA_UNIT_FPIN(TMRAx, u32Pin));
    DDL_ASSERT(IS_TMRA_FILTER_CLK_DIV(u16Div));

    if (u32Pin < TMRA_PIN_PWM_OFFSET) {
        MODIFY_REG16(TMRAx->FCONR,
                     (TMRA_FCONR_FILTER_CLK_MASK << au8Offset[u32Pin]),
                     (u16Div << au8Offset[u32Pin]));
    } else {
        u32Ch = u32Pin - TMRA_PIN_PWM_OFFSET;
        u32CCONRAddr = (uint32_t)&TMRAx->CCONR1 + u32Ch * 4U;
        MODIFY_REG16(RW_MEM16(u32CCONRAddr),
                     TMRA_CCONR_FILTER_CLK_MASK,
                     (u16Div << TMRA_CCONR_NOFICKCP_POS));
    }
}

/**
 * @brief  Enable or disable the filter function of the specified TMRA input pin.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Pin                 The pin with filter of TMRA.
 *                                      This parameter can be values of @ref TMRA_Filter_Pin
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_FilterCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Pin, en_functional_state_t enNewState)
{
    uint8_t u8EnPos;
    uint32_t u32Ch;
    uint32_t u32RegAddr;
    const uint8_t au8Offset[] = {
        TMRA_FCONR_NOFIENTG_POS, TMRA_FCONR_NOFIENCA_POS, TMRA_FCONR_NOFIENCB_POS,
    };

    DDL_ASSERT(IS_TMRA_UNIT_FPIN(TMRAx, u32Pin));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (u32Pin < TMRA_PIN_PWM_OFFSET) {
        u32RegAddr = (uint32_t)&TMRAx->FCONR;
        u8EnPos    = au8Offset[u32Pin];
    } else {
        u32Ch      = u32Pin - TMRA_PIN_PWM_OFFSET;
        u32RegAddr = (uint32_t)&TMRAx->CCONR1 + u32Ch * 4U;
        u8EnPos    = TMRA_CCONR_NOFIENCP_POS;
    }
    WRITE_REG32(PERIPH_BIT_BAND(u32RegAddr, u8EnPos), enNewState);
}

/**
 * @brief  De-initializes the TMRA peripheral. Reset all registers of the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @retval None
 */
void TMRA_DeInit(CM_TMRA_TypeDef *TMRAx)
{
    uint32_t i;
    uint32_t u32ChNum = TMRA_CH_NUM;
    uint32_t u32AddrOffset;
    uint32_t u32PERARAddr;
    uint32_t u32CNTERAddr;
    uint32_t u32CMPARAddr;
    uint32_t u32CCONRAddr;
    uint32_t u32PCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));

    u32PERARAddr = (uint32_t)&TMRAx->PERAR;
    u32CNTERAddr = (uint32_t)&TMRAx->CNTER;
    u32CMPARAddr = (uint32_t)&TMRAx->CMPAR1;
    u32CCONRAddr = (uint32_t)&TMRAx->CCONR1;
    u32PCONRAddr = (uint32_t)&TMRAx->PCONR1;

    for (i = 0U; i < u32ChNum; i++) {
        u32AddrOffset = i * 4U;
        RW_MEM16(u32CMPARAddr + u32AddrOffset) = 0xFFFFU;
        RW_MEM16(u32CCONRAddr + u32AddrOffset) = 0x0U;
        RW_MEM16(u32PCONRAddr + u32AddrOffset) = 0x0U;
    }

    SET_VAL_BY_ADDR(u32PERARAddr, 0xFFFFFFFFUL);
    SET_VAL_BY_ADDR(u32CNTERAddr, 0x0U);
    WRITE_REG16(TMRAx->BCSTR, 0x2U);
    WRITE_REG16(TMRAx->ICONR, 0x0U);
    WRITE_REG16(TMRAx->ECONR, 0x0U);
    WRITE_REG16(TMRAx->FCONR, 0x0U);
    WRITE_REG16(TMRAx->STFLR, 0x0U);
    WRITE_REG16(TMRAx->HCONR, 0x0U);
    WRITE_REG16(TMRAx->HCUPR, 0x0U);
    WRITE_REG16(TMRAx->HCDOR, 0x0U);

    WRITE_REG16(TMRAx->BCONR1, 0x0U);
    WRITE_REG16(TMRAx->BCONR2, 0x0U);
}

/**
 * @brief  Get the counting direction of the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @retval An uint16_t type value of counting direction.
 *          -TMRA_DIR_DOWN:             TMRA count down.
 *          -TMRA_DIR_UP:               TMRA count up.
 */
uint16_t TMRA_GetCountDir(const CM_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    return READ_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_DIR);
}

/**
 * @brief  Set period value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Value               The period value to be set.
 *                                      This parameter can be a number between:
 *                                      0UL and 0xFFFFFFFFUL for TimerA1 and TimerA2 of HC32F472.
 *                                      0UL and 0xFFFFUL for TimerA3/4/5/6 of HC32F472 and all TimerA units of other MCUs.
 * @retval None
 */
void TMRA_SetPeriodValue(CM_TMRA_TypeDef *TMRAx, uint32_t u32Value)
{
    uint32_t u32PERARAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    u32PERARAddr = (uint32_t)&TMRAx->PERAR;
    SET_VAL_BY_ADDR(u32PERARAddr, u32Value);
}

/**
 * @brief  Get period value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @retval An uint32_t type type value of period value between:
 *         - 0UL and 0xFFFFFFFFUL for TimerA1 and TimerA2 of HC32F472.
 *         - 0UL and 0xFFFFUL for TimerA3/4/5/6 of HC32F472 and all TimerA units of other MCUs.
 */
uint32_t TMRA_GetPeriodValue(const CM_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    return (TMRAx->PERAR);
}

/**
 * @brief  Set general counter value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Value               The general counter value to be set.
 *                                      This parameter can be a number between:
 *                                      0UL and 0xFFFFFFFFUL for TimerA1 and TimerA2 of HC32F472.
 *                                      0UL and 0xFFFFUL for TimerA3/4/5/6 of HC32F472 and all TimerA units of other MCUs.
 * @retval None
 */
void TMRA_SetCountValue(CM_TMRA_TypeDef *TMRAx, uint32_t u32Value)
{
    uint32_t u32CNTERAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    u32CNTERAddr = (uint32_t)&TMRAx->CNTER;
    SET_VAL_BY_ADDR(u32CNTERAddr, u32Value);
}

/**
 * @brief  Get general counter value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @retval An uint32_t type type value of counter value between:
 *         - 0UL and 0xFFFFFFFFUL for TimerA1 and TimerA2 of HC32F472.
 *         - 0UL and 0xFFFFUL for TimerA3/4/5/6 of HC32F472 and all TimerA units of other MCUs.
 */
uint32_t TMRA_GetCountValue(const CM_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    return (TMRAx->CNTER);
}

/**
 * @brief  Set comparison value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be a value of @ref TMRA_Channel
 * @param  [in]  u32Value               The comparison value to be set.
 *                                      This parameter can be a number between:
 *                                      0UL and 0xFFFFFFFFUL for TimerA1 and TimerA2 of HC32F472.
 *                                      0UL and 0xFFFFUL for TimerA3/4/5/6 of HC32F472 and all TimerA units of other MCUs.
 * @retval None
 */
void TMRA_SetCompareValue(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint32_t u32Value)
{
    uint32_t u32CMPARAddr;

    DDL_ASSERT(IS_TMRA_UNIT_CH(TMRAx, u32Ch));

    u32CMPARAddr = (uint32_t)&TMRAx->CMPAR1 + u32Ch * 4U;
    SET_VAL_BY_ADDR(u32CMPARAddr, u32Value);
}

/**
 * @brief  Get comparison value.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be a value of @ref TMRA_Channel
 * @retval An uint32_t type type value of comparison value value between:
 *         - 0UL and 0xFFFFFFFFUL for TimerA1 and TimerA2 of HC32F472.
 *         - 0UL and 0xFFFFUL for TimerA3/4/5/6 of HC32F472 and all TimerA units of other MCUs.
 */
uint32_t TMRA_GetCompareValue(const CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch)
{
    uint32_t u32CMPARAddr;

    DDL_ASSERT(IS_TMRA_UNIT_CH(TMRAx, u32Ch));

    u32CMPARAddr = (uint32_t)&TMRAx->CMPAR1 + u32Ch * 4U;
    return GET_VAL_BY_ADDR(u32CMPARAddr);
}

/* Sync start. */
/**
 * @brief  Enable or disable synchronous-start. When an even unit enables synchronous-start function,
 *         start the symmetric odd unit can start the even unit at the same time.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x(x is an even number)
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_SyncStartCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    uint32_t u32Addr;

    DDL_ASSERT(IS_TMRA_SYNC_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Addr = (uint32_t)&TMRAx->BCSTR;
    WRITE_REG32(PERIPH_BIT_BAND(u32Addr, TMRA_BCSTR_SYNST_POS), enNewState);
}

/* Reload and continue counting when overflow/underflow? */
/**
 * @brief  Enable or disable reload and continue counting when overflow/underflow.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_CountReloadCmd(CM_TMRA_TypeDef *TMRAx, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        CLR_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_OVSTP);
    } else {
        SET_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_OVSTP);
    }
}

/**
 * @brief  Specifies the condition of compare value buffer transmission.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be one of the odd channels of @ref TMRA_Channel
 * @param  [in]  u16Cond                Buffer condition of the specified TMRA unit.
 *                                      This parameter can be a value of @ref TMRA_Cmp_Value_Buf_Trans_Cond
 *   @arg  TMRA_BUF_TRANS_COND_OVF_UDF_CLR: This configuration value applies to non-triangular wave counting mode.
 *                                      When counting overflow or underflow or counting register was cleared,
 *                                      transfer CMPARm(m=2,4,6,8,...) to CMPARn(n=1,3,5,7,...).
 *   @arg  TMRA_BUF_TRANS_COND_PEAK:    In triangle wave count mode, when count reached peak,
 *                                      transfer CMMARm(m=2,4,6,8,...) to CMMARn(n=1,3,5,7,...).
 *   @arg  TMRA_BUF_TRANS_COND_VALLEY:  In triangle wave count mode, when count reached valley,
 *                                      transfer CMMARm(m=2,4,6,8,...) to CMMARn(n=1,3,5,7,...).
 * @retval None
 */
void TMRA_SetCompareBufCond(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, uint16_t u16Cond)
{
    uint32_t u32BCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CMPVAL_BUF_CH(u32Ch));
    DDL_ASSERT(IS_TMRA_CMPVAL_BUF_COND(u16Cond));

    u32BCONRAddr = (uint32_t)&TMRAx->BCONR1 + u32Ch * 4U;
    MODIFY_REG16(RW_MEM16(u32BCONRAddr), TMRA_BUF_TRANS_COND_PEAK_VALLEY, u16Cond);
}

/**
 * @brief  Enable or disable compare value buffer.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Ch                  TMRA channel.
 *                                      This parameter can be one of the odd channels of @ref TMRA_Channel
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_CompareBufCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32Ch, en_functional_state_t enNewState)
{
    uint32_t u32BCONRAddr;

    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    DDL_ASSERT(IS_TMRA_CMPVAL_BUF_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32BCONRAddr = (uint32_t)&TMRAx->BCONR1 + u32Ch * 4U;
    WRITE_REG32(PERIPH_BIT_BAND(u32BCONRAddr, TMRA_BCONR_BEN_POS), enNewState);
}

/**
 * @brief  Get the status of the specified flag.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Flag                The status flags of TMRA.
 *                                      This parameter can be a value of @ref TMRA_Status_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t TMRA_GetStatus(const CM_TMRA_TypeDef *TMRAx, uint32_t u32Flag)
{
    uint16_t u16BCSTR;
    uint16_t u16STFLR;
    en_flag_status_t enStatus = RESET;

    DDL_ASSERT(IS_TMRA_UNIT_FLAG(TMRAx, u32Flag));

    u16BCSTR = (uint16_t)(u32Flag & TMRA_BCSTR_FLAG_MASK);
    u16STFLR = (uint16_t)(u32Flag >> 16U);
    u16BCSTR = READ_REG16_BIT(TMRAx->BCSTR, u16BCSTR);
    u16STFLR = READ_REG16_BIT(TMRAx->STFLR, u16STFLR);

    if ((u16BCSTR != 0U) || (u16STFLR != 0U)) {
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief  Clear the status of the specified flags.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32Flag                The status flags of TMRA.
 *                                      This parameter can be values of @ref TMRA_Status_Flag
 * @retval None
 */
void TMRA_ClearStatus(CM_TMRA_TypeDef *TMRAx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_TMRA_UNIT_FLAG(TMRAx, u32Flag));

    CLR_REG16_BIT(TMRAx->BCSTR, u32Flag & TMRA_BCSTR_FLAG_MASK);
    CLR_REG16_BIT(TMRAx->STFLR, u32Flag >> 16U);
}

/**
 * @brief  Enable of disable the specified interrupts of the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32IntType             The interrupt type of TMRA.
 *                                      This parameter can be values of @ref TMRA_Interrupt_Type
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_IntCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint32_t u32BCSTR;
    uint32_t u32ICONR;

    DDL_ASSERT(IS_TMRA_UNIT_INT(TMRAx, u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32BCSTR = u32IntType & TMRA_BCSTR_INT_MASK;
    u32ICONR = u32IntType >> 16U;
    if (enNewState == ENABLE) {
        SET_REG16_BIT(TMRAx->BCSTR, u32BCSTR);
        SET_REG16_BIT(TMRAx->ICONR, u32ICONR);
    } else {
        CLR_REG16_BIT(TMRAx->BCSTR, u32BCSTR);
        CLR_REG16_BIT(TMRAx->ICONR, u32ICONR);
    }
}

/**
 * @brief  Enable of disable the specified event of the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @param  [in]  u32EventType           The event type of TMRA.
 *                                      This parameter can be values of @ref TMRA_Event_Type
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMRA_EventCmd(CM_TMRA_TypeDef *TMRAx, uint32_t u32EventType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMRA_CH_EVT(TMRAx, u32EventType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG16_BIT(TMRAx->ECONR, u32EventType);
    } else {
        CLR_REG16_BIT(TMRAx->ECONR, u32EventType);
    }
}

/**
 * @brief  Start the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @retval None
 */
void TMRA_Start(CM_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    SET_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_START);
}

/**
 * @brief  Stop the specified TMRA unit.
 * @param  [in]  TMRAx                  Pointer to TMRA instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMRA_x or CM_TMRA
 * @retval None
 */
void TMRA_Stop(CM_TMRA_TypeDef *TMRAx)
{
    DDL_ASSERT(IS_TMRA_UNIT(TMRAx));
    CLR_REG16_BIT(TMRAx->BCSTR, TMRA_BCSTR_START);
}
/**
 * @}
 */

#endif /* LL_TMRA_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
