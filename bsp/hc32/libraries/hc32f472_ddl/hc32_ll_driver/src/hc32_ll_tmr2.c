/**
 *******************************************************************************
 * @file  hc32_ll_tmr2.c
 * @brief This file provides firmware functions to manage the TMR2(Timer2).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-06-30       CDT             First version
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
#include "hc32_ll_tmr2.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_TMR2 TMR2
 * @brief TMR2 Driver Library
 * @{
 */
#if (LL_TMR2_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup TMR2_Local_Macros TMR2 Local Macros
 * @{
 */

/**
 * @defgroup TMR2_Configuration_Bit_Mask TMR2 Configuration Bit Mask
 * @{
 */
#define TMR2_BCONR_INIT_MASK                (TMR2_BCONR_CAPMDA | TMR2_BCONR_SYNSA | TMR2_BCONR_SYNCLKA | \
                                             TMR2_BCONR_ASYNCLKA | TMR2_BCONR_CKDIVA | TMR2_BCONR_SYNCLKAT)
#define TMR2_BCONR_CLK_CFG_MASK             (TMR2_BCONR_SYNSA | TMR2_BCONR_SYNCLKA | \
                                             TMR2_BCONR_ASYNCLKA | TMR2_BCONR_SYNCLKAT)

#define TMR2_PWM_POLARITY_MASK              (TMR2_PCONR_STACA | TMR2_PCONR_STPCA | TMR2_PCONR_CMPCA)
#define TMR2_FILTER_CLK_DIV_MASK            (TMR2_PCONR_NOFICKA)
/**
 * @}
 */

/**
 * @defgroup TMR2_Channel_Cfg_Bit_Field_Offset TMR2 Channel Configuration Bit Field Offset
 * @{
 */
#define TMR2_CH_OFFSET                      (16U)

#define TMR2_PWM_POLARITY_OFFSET            (2U)

/**
 * @}
 */

/**
 * @defgroup TMR2_Check_Parameters_Validity TMR2 check parameters validity
 * @{
 */
#define IS_TMR2_BIT_MASK(x, mask)   (((x) != 0U) && (((x) | (mask)) == (mask)))

#define IS_TMR2_UNIT(x)                                                        \
(   ((x) == CM_TMR2_1)                       ||                                \
    ((x) == CM_TMR2_2)                       ||                                \
    ((x) == CM_TMR2_3)                       ||                                \
    ((x) == CM_TMR2_4))

#define IS_TMR2_CH(x)               ((x) <= TMR2_CH_B)

#define IS_TMR2_FUNC(x)             (((x) == TMR2_FUNC_CMP) || ((x) == TMR2_FUNC_CAPT))

#define IS_TMR2_CLK_SRC(x)                                                     \
(   ((x) == TMR2_CLK_PCLK1)                 ||                                 \
    ((x) == TMR2_CLK_TRIG_RISING)           ||                                 \
    ((x) == TMR2_CLK_TRIG_FALLING)          ||                                 \
    ((x) == TMR2_CLK_EVT)                   ||                                 \
    ((x) == TMR2_CLK_TMR6_OVF)              ||                                 \
    ((x) == TMR2_CLK_TMR6_UDF)              ||                                 \
    ((x) == TMR2_CLK_TMR6_OVF_UDF)          ||                                 \
    ((x) == TMR2_CLK_LRC)                   ||                                 \
    ((x) == TMR2_CLK_XTAL32)                ||                                 \
    ((x) == TMR2_CLK_PIN_CLK))

#define IS_TMR2_CLK_DIV(x)                                                     \
(   ((x) == TMR2_CLK_DIV1)                  ||                                 \
    ((x) == TMR2_CLK_DIV2)                  ||                                 \
    ((x) == TMR2_CLK_DIV4)                  ||                                 \
    ((x) == TMR2_CLK_DIV8)                  ||                                 \
    ((x) == TMR2_CLK_DIV16)                 ||                                 \
    ((x) == TMR2_CLK_DIV32)                 ||                                 \
    ((x) == TMR2_CLK_DIV64)                 ||                                 \
    ((x) == TMR2_CLK_DIV128)                ||                                 \
    ((x) == TMR2_CLK_DIV256)                ||                                 \
    ((x) == TMR2_CLK_DIV512)                ||                                 \
    ((x) == TMR2_CLK_DIV1024))

#define IS_TMR2_INT(x)              IS_TMR2_BIT_MASK((x), TMR2_INT_ALL)

#define IS_TMR2_FLAG(x)             IS_TMR2_BIT_MASK((x), TMR2_FLAG_ALL)

#define IS_TMR2_PWM_START_POLARITY(x)                                          \
(   ((x) == TMR2_PWM_LOW)                   ||                                 \
    ((x) == TMR2_PWM_HIGH)                  ||                                 \
    ((x) == TMR2_PWM_HOLD))

#define IS_TMR2_PWM_STOP_POLARITY(x)                                           \
(   ((x) == TMR2_PWM_LOW)                   ||                                 \
    ((x) == TMR2_PWM_HIGH)                  ||                                 \
    ((x) == TMR2_PWM_HOLD))

#define IS_TMR2_PWM_MATCH_CMP_POLARITY(x)                                      \
(   ((x) == TMR2_PWM_LOW)                   ||                                 \
    ((x) == TMR2_PWM_HIGH)                  ||                                 \
    ((x) == TMR2_PWM_HOLD)                  ||                                 \
    ((x) == TMR2_PWM_INVT))

#define IS_TMR2_PWM_POLARITY(st, pol)                                          \
(   (((st) == TMR2_CNT_STAT_START) && IS_TMR2_PWM_START_POLARITY(pol))      || \
    (((st) == TMR2_CNT_STAT_STOP) && IS_TMR2_PWM_STOP_POLARITY(pol))        || \
    (((st) == TMR2_CNT_STAT_MATCH_CMP) && IS_TMR2_PWM_MATCH_CMP_POLARITY(pol)))

#define IS_TMR2_START_COND(x)       IS_TMR2_BIT_MASK((x), TMR2_START_COND_ALL)

#define IS_TMR2_STOP_COND(x)        IS_TMR2_BIT_MASK((x), TMR2_STOP_COND_ALL)

#define IS_TMR2_CLR_COND(x)         IS_TMR2_BIT_MASK((x), TMR2_CLR_COND_ALL)

#define IS_TMR2_CAPT_COND(x)        IS_TMR2_BIT_MASK((x), TMR2_CAPT_COND_ALL)

#define IS_TMR2_FILTER_CLK_DIV(x)                                              \
(   ((x) == TMR2_FILTER_CLK_DIV1)           ||                                 \
    ((x) == TMR2_FILTER_CLK_DIV4)           ||                                 \
    ((x) == TMR2_FILTER_CLK_DIV16)          ||                                 \
    ((x) == TMR2_FILTER_CLK_DIV64))

#define IS_TMR2_VALID_VAL(x)        ((x) <= 0xFFFFUL)

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
 * @defgroup TMR2_Global_Functions TMR2 Global Functions
 * @{
 */

/**
 * @brief  Initializes the specified TMR2 channel according to the specified parameters
 *         in the structure stc_tmr2_init_t
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  pstcTmr2Init           Pointer to a stc_tmr2_init_t structure value that
 *                                      contains the configuration information for the TMR2 channel.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcTmr2Init == NULL.
 */
int32_t TMR2_Init(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, const stc_tmr2_init_t *pstcTmr2Init)
{
    uint32_t u32Tmp;
    int32_t i32Ret = LL_ERR_INVD_PARAM;
    __IO uint32_t *reg32CMPR;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));

    if (pstcTmr2Init != NULL) {
        DDL_ASSERT(IS_TMR2_CLK_SRC(pstcTmr2Init->u32ClockSrc));
        DDL_ASSERT(IS_TMR2_CLK_DIV(pstcTmr2Init->u32ClockDiv));
        DDL_ASSERT(IS_TMR2_FUNC(pstcTmr2Init->u32Func));
        DDL_ASSERT(IS_TMR2_VALID_VAL(pstcTmr2Init->u32CompareValue));

        u32Tmp = pstcTmr2Init->u32Func | pstcTmr2Init->u32ClockSrc |
                 pstcTmr2Init->u32ClockDiv;
        reg32CMPR = (__IO uint32_t *)((uint32_t)&TMR2x->CMPAR);
        WRITE_REG32(reg32CMPR[u32Ch], pstcTmr2Init->u32CompareValue);
        /* Channel bit filed offset. */
        u32Ch *= TMR2_CH_OFFSET;
        MODIFY_REG32(TMR2x->BCONR, (TMR2_BCONR_INIT_MASK << u32Ch), (u32Tmp << u32Ch));
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set a default value for TMR2 initialization structure.
 * @param  [in]  pstcTmr2Init           Pointer to a stc_tmr2_init_t structure that
 *                                      contains configuration information.
 * @retval int32_t:
 *           - LL_OK:                   No errors occurred.
 *           - LL_ERR_INVD_PARAM:       pstcTmr2Init == NULL.
 */
int32_t TMR2_StructInit(stc_tmr2_init_t *pstcTmr2Init)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstcTmr2Init != NULL) {
        pstcTmr2Init->u32ClockSrc = TMR2_CLK_PCLK1;
        pstcTmr2Init->u32ClockDiv = TMR2_CLK_DIV1;
        pstcTmr2Init->u32Func     = TMR2_FUNC_CMP;
        pstcTmr2Init->u32CompareValue = 0xFFFFUL;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-initializes the specified TMR2 unit.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @retval None
 */
void TMR2_DeInit(CM_TMR2_TypeDef *TMR2x)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));

    TMR2_Stop(TMR2x, TMR2_CH_A);
    TMR2_Stop(TMR2x, TMR2_CH_B);
    WRITE_REG32(TMR2x->CMPBR, 0xFFFFU);
    CLR_REG32(TMR2x->CNTBR);
    CLR_REG32(TMR2x->CNTAR);
    CLR_REG32(TMR2x->BCONR);
    CLR_REG32(TMR2x->ICONR);
    CLR_REG32(TMR2x->PCONR);
    CLR_REG32(TMR2x->HCONR);
    CLR_REG32(TMR2x->STFLR);
    WRITE_REG32(TMR2x->CMPAR, 0xFFFFU);
}

/**
 * @brief  Specifies the function mode for the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Func                Function mode.
 *                                      This parameter can be a value of @ref TMR2_Function
 *   @arg  TMR2_FUNC_CMP:               The function of TMR2 channel is ouput compare.
 *   @arg  TMR2_FUNC_CAPT:              The function of TMR2 channel is input capture.
 * @retval None
 */
void TMR2_SetFunc(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Func)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_FUNC(u32Func));

    /* Channel bit filed offset. */
    u32Ch *= TMR2_CH_OFFSET;
    MODIFY_REG32(TMR2x->BCONR, (TMR2_BCONR_CAPMDA << u32Ch), (u32Func << u32Ch));
}

/**
 * @brief  Specifies the clock source for the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Src                 Clock source.
 *                                      This parameter can be a value of @ref TMR2_Clock_Source
 * @retval None
 */
void TMR2_SetClockSrc(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Src)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_CLK_SRC(u32Src));

    /* Channel bit filed offset. */
    u32Ch *= TMR2_CH_OFFSET;
    MODIFY_REG32(TMR2x->BCONR, (TMR2_BCONR_CLK_CFG_MASK << u32Ch), (u32Src << u32Ch));
}

/**
 * @brief  Specifies the clock divider for the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Div                 Clock divider.
 *                                      This parameter can be a value of @ref TMR2_Clock_Divider
 * @retval None
 */
void TMR2_SetClockDiv(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Div)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_CLK_DIV(u32Div));

    /* Channel bit filed offset. */
    u32Ch *= TMR2_CH_OFFSET;
    MODIFY_REG32(TMR2x->BCONR, (TMR2_BCONR_CKDIVA << u32Ch), (u32Div << u32Ch));
}

/**
 * @brief  Set a default value for the TMR2 output compare configuration structure.
 * @param  [in]  pstPwmInit             Pointer to a stc_tmr2_pwm_init_t structure value that
 *                                      contains the configuration information for the TMR2 PWM.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcTmr2Init == NULL.
 */
int32_t TMR2_PWM_StructInit(stc_tmr2_pwm_init_t *pstPwmInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (pstPwmInit != NULL) {
        pstPwmInit->u32StartPolarity = TMR2_PWM_HIGH;
        pstPwmInit->u32StopPolarity  = TMR2_PWM_LOW;
        pstPwmInit->u32CompareMatchPolarity = TMR2_PWM_INVT;
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Configures the PWM of the specified TMR2 channel
 *         according to the specified parameters in the structure @ref stc_tmr2_pwm_init_t
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  pstPwmInit             Pointer to a @ref stc_tmr2_pwm_init_t structure value that
 *                                      contains the configuration information for the TMR2 PWM.
 * @retval int32_t:
 *           - LL_OK:                   No error occurred.
 *           - LL_ERR_INVD_PARAM:       pstcTmr2Init == NULL.
 */
int32_t TMR2_PWM_Init(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, const stc_tmr2_pwm_init_t *pstPwmInit)
{
    uint32_t u32Tmp;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));

    if (pstPwmInit != NULL) {
        DDL_ASSERT(IS_TMR2_PWM_START_POLARITY(pstPwmInit->u32StartPolarity));
        DDL_ASSERT(IS_TMR2_PWM_STOP_POLARITY(pstPwmInit->u32StopPolarity));
        DDL_ASSERT(IS_TMR2_PWM_MATCH_CMP_POLARITY(pstPwmInit->u32CompareMatchPolarity));
        /* Configures PWM polarity. */
        u32Tmp = (pstPwmInit->u32StartPolarity << TMR2_PCONR_STACA_POS) | \
                 (pstPwmInit->u32StopPolarity << TMR2_PCONR_STPCA_POS)  | \
                 (pstPwmInit->u32CompareMatchPolarity << TMR2_PCONR_CMPCA_POS);
        u32Ch *= TMR2_CH_OFFSET;
        MODIFY_REG32(TMR2x->PCONR, (TMR2_PWM_POLARITY_MASK << u32Ch), (u32Tmp << u32Ch));
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable PWM output of the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR2_PWM_OutputCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    uint32_t u32PCONRAddr;
    uint8_t au8EnPos[] = {TMR2_PCONR_OUTENA_POS, TMR2_PCONR_OUTENB_POS};
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32PCONRAddr = (uint32_t)&TMR2x->PCONR;
    WRITE_REG32(PERIPH_BIT_BAND(u32PCONRAddr, au8EnPos[u32Ch]), enNewState);
}

/**
 * @brief  Enable or disable the specified hardware capture condition.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Cond                Hardware capture condition.
 *                                      This parameter can be a value of @ref TMR2_Capture_Condition
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR2_HWCaptureCondCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_CAPT_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Cond <<= (u32Ch * TMR2_CH_OFFSET);

    if (enNewState == ENABLE) {
        SET_REG32_BIT(TMR2x->HCONR, u32Cond);
    } else {
        CLR_REG32_BIT(TMR2x->HCONR, u32Cond);
    }
}

/**
 * @brief  Enable or disable the specified hardware start condition.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Cond                Hardware start condition.
 *                                      This parameter can be a value of @ref TMR2_Start_Condition
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR2_HWStartCondCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_START_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Cond <<= (u32Ch * TMR2_CH_OFFSET);

    if (enNewState == ENABLE) {
        SET_REG32_BIT(TMR2x->HCONR, u32Cond);
    } else {
        CLR_REG32_BIT(TMR2x->HCONR, u32Cond);
    }
}

/**
 * @brief  Enable or disable the specified hardware stop condition.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Cond                Hardware stop condition.
 *                                      This parameter can be a value of @ref TMR2_Stop_Condition
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR2_HWStopCondCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_STOP_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Cond <<= (u32Ch * TMR2_CH_OFFSET);

    if (enNewState == ENABLE) {
        SET_REG32_BIT(TMR2x->HCONR, u32Cond);
    } else {
        CLR_REG32_BIT(TMR2x->HCONR, u32Cond);
    }
}

/**
 * @brief  Enable or disable the specified hardware clear condition.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Cond                Hardware clear condition.
 *                                      This parameter can be a value of @ref TMR2_Clear_Condition
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR2_HWClearCondCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Cond, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_CLR_COND(u32Cond));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32Cond <<= (u32Ch * TMR2_CH_OFFSET);

    if (enNewState == ENABLE) {
        SET_REG32_BIT(TMR2x->HCONR, u32Cond);
    } else {
        CLR_REG32_BIT(TMR2x->HCONR, u32Cond);
    }
}

/**
 * @brief  Specifies the clock divider of filter.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Div                 The clock source divider of the filter.
 *                                      This parameter can be a value of @ref TMR2_Filter_Clock_Divider
 *   @arg  TMR2_FILTER_CLK_DIV1:        The filter clock is the clock of timer2 / 1.
 *   @arg  TMR2_FILTER_CLK_DIV4:        The filter clock is the clock of timer2 / 4.
 *   @arg  TMR2_FILTER_CLK_DIV16:       The filter clock is the clock of timer2 / 16.
 *   @arg  TMR2_FILTER_CLK_DIV64:       The filter clock is the clock of timer2 / 64.
 * @retval None
 */
void TMR2_SetFilterClockDiv(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Div)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_FILTER_CLK_DIV(u32Div));

    u32Ch *= TMR2_CH_OFFSET;
    MODIFY_REG32(TMR2x->PCONR, TMR2_FILTER_CLK_DIV_MASK << u32Ch, u32Div << u32Ch);
}

/**
 * @brief  Enable or disable the filter of the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR2_FilterCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, en_functional_state_t enNewState)
{
    uint32_t u32PCONRAddr;
    uint8_t au8EnPos[] = {TMR2_PCONR_NOFIENA_POS, TMR2_PCONR_NOFIENB_POS};
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32PCONRAddr = (uint32_t)&TMR2x->PCONR;
    WRITE_REG32(PERIPH_BIT_BAND(u32PCONRAddr, au8EnPos[u32Ch]), enNewState);
}

/**
 * @brief  Enable or disable the interrupt of the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32IntType             The interrupt type.
 *                                      This parameter can be values of @ref TMR2_Interrupt_Type
 * @param  [in]  enNewState             An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void TMR2_IntCmd(CM_TMR2_TypeDef *TMR2x, uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (enNewState == ENABLE) {
        SET_REG32_BIT(TMR2x->ICONR, u32IntType);
    } else {
        CLR_REG32_BIT(TMR2x->ICONR, u32IntType);
    }
}

/**
 * @brief  Start the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @retval None
 */
void TMR2_Start(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));

    SET_REG32_BIT(TMR2x->BCONR, TMR2_BCONR_CSTA << (u32Ch * TMR2_CH_OFFSET));
}

/**
 * @brief  Stop the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @retval None
 */
void TMR2_Stop(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));

    CLR_REG32_BIT(TMR2x->BCONR, TMR2_BCONR_CSTA << (u32Ch * TMR2_CH_OFFSET));
}

/**
 * @brief  Get the status of the specified TMR2 flag.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Flag                TMR2 status flag.
 *                                      This parameter can be values of @ref TMR2_Status_Flag
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t TMR2_GetStatus(const CM_TMR2_TypeDef *TMR2x, uint32_t u32Flag)
{
    en_flag_status_t enStatus = RESET;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_FLAG(u32Flag));

    if (READ_REG32_BIT(TMR2x->STFLR, u32Flag) != 0U) {
        enStatus = SET;
    }

    return enStatus;
}

/**
 * @brief  Clear the status of the specified TMR2 flag.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Flag                TMR2 status flag.
 *                                      This parameter can be values of @ref TMR2_Status_Flag
 * @retval None
 */
void TMR2_ClearStatus(CM_TMR2_TypeDef *TMR2x, uint32_t u32Flag)
{
    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_FLAG(u32Flag));
    CLR_REG32_BIT(TMR2x->STFLR, u32Flag);
}

/**
 * @brief  Set compare value for the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  The TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Value               The compare reference value of the specified TMR2 channel.
 *                                      This parameter can be a number between 0U and 0xFFFFU, inclusive.
 * @retval None
 */
void TMR2_SetCompareValue(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Value)
{
    __IO uint32_t *reg32CMPR;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_VALID_VAL(u32Value));

    reg32CMPR = (__IO uint32_t *)((uint32_t)&TMR2x->CMPAR);
    WRITE_REG32(reg32CMPR[u32Ch], u32Value);
}

/**
 * @brief  Get compare value of the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                The TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @retval The compare value of the specified TMR2 channel. A number between 0U and 0xFFFFU, inclusive.
 */
uint32_t TMR2_GetCompareValue(const CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch)
{
    __IO uint32_t *reg32CMPR;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));

    reg32CMPR = (__IO uint32_t *)((uint32_t)&TMR2x->CMPAR);
    return reg32CMPR[u32Ch];
}

/**
 * @brief  Set counter value for the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  The TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @param  [in]  u32Value               The counter value for the specified TMR2 channel.
 *                                      This parameter can be a number between 0U and 0xFFFFU, inclusive.
 * @retval None
 */
void TMR2_SetCountValue(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint32_t u32Value)
{
    __IO uint32_t *reg32CNTR;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_VALID_VAL(u32Value));

    reg32CNTR = (__IO uint32_t *)((uint32_t)&TMR2x->CNTAR);
    WRITE_REG32(reg32CNTR[u32Ch], u32Value);
}

/**
 * @brief  Get counter value of the specified TMR2 channel.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  The TMR2 channel.
 *                                      This parameter can be a value of @ref TMR2_Channel
 * @retval The counter value of the specified TMR2 channel. A number between 0U and 0xFFFFU, inclusive.
 */
uint32_t TMR2_GetCountValue(const CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch)
{
    __IO uint32_t *reg32CNTR;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));

    reg32CNTR = (__IO uint32_t *)((uint32_t)&TMR2x->CNTAR);
    return reg32CNTR[u32Ch];
}

/**
 * @brief  Specifies the ouput polarity of the PWM at the specified state of counter.
 * @param  [in]  TMR2x                  Pointer to TMR2 instance register base.
 *                                      This parameter can be a value of the following:
 *   @arg  CM_TMR2_x or CM_TMR2
 * @param  [in]  u32Ch                  TMR2 channel.
 *                                      This parameter can be a value @ref TMR2_Channel
 * @param  [in]  u8CountState           TMR2 counter state.
 *                                      This parameter can be a value @ref TMR2_Counter_State
 * @param  [in]  u32Polarity            The polarity of PWM.
 *                                      This parameter can be a value @ref TMR2_PWM_Polarity
 * @retval None
 */
void TMR2_PWM_SetPolarity(CM_TMR2_TypeDef *TMR2x, uint32_t u32Ch, uint8_t u8CountState, uint32_t u32Polarity)
{
    uint32_t u32PolarityPos;

    DDL_ASSERT(IS_TMR2_UNIT(TMR2x));
    DDL_ASSERT(IS_TMR2_CH(u32Ch));
    DDL_ASSERT(IS_TMR2_PWM_POLARITY(u8CountState, u32Polarity));

    u32PolarityPos = ((uint32_t)u8CountState * TMR2_PWM_POLARITY_OFFSET) + (u32Ch * TMR2_CH_OFFSET);
    MODIFY_REG32(TMR2x->PCONR, TMR2_PCONR_STACA << u32PolarityPos, u32Polarity << u32PolarityPos);
}

/**
 * @}
 */

#endif /* LL_TMR2_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
