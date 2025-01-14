/**
 *******************************************************************************
 * @file  hc32_ll_emb.c
 * @brief This file provides firmware functions to manage the EMB
 *        (Emergency Brake).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
   2022-06-30       CDT             Optimize function: EMB_TMR4_Init
                                    Optimize function: EMB_TMR6_Init
   2023-06-30       CDT             Function EMB_TMR4_Init don't call EMB_DeInit
                                    Function EMB_TMR6_Init don't call EMB_DeInit
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
#include "hc32_ll_emb.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_EMB EMB
 * @brief Emergency Brake Driver Library
 * @{
 */

#if (LL_EMB_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EMB_Local_Macros EMB Local Macros
 * @{
 */

/**
 * @defgroup EMB_Check_Parameters_Validity EMB Check Parameters Validity
 * @{
 */
#define IS_EMB_GROUP(x)                                                        \
(   ((x) == CM_EMB0)                        ||                                 \
    ((x) == CM_EMB1)                        ||                                 \
    ((x) == CM_EMB2)                        ||                                 \
    ((x) == CM_EMB3))
#define IS_EMB_TMR4_GROUP(x)                                                   \
(   ((x) == CM_EMB1)                        ||                                 \
    ((x) == CM_EMB2)                        ||                                 \
    ((x) == CM_EMB3))
#define IS_EMB_TMR6_GROUP(x)                ((x) == CM_EMB0)

#define IS_EMB_OSC_STAT(x)                                                     \
(   ((x) == EMB_OSC_ENABLE)                 ||                                 \
    ((x) == EMB_OSC_DISABLE))

#define IS_EMB_TMR4_PWM_W_STAT(x)                                              \
(   ((x) == EMB_TMR4_PWM_W_ENABLE)          ||                                 \
    ((x) == EMB_TMR4_PWM_W_DISABLE))

#define IS_EMB_DETECT_TMR4_PWM_W_LVL(x)                                        \
(   ((x) == EMB_DETECT_TMR4_PWM_W_BOTH_LOW) ||                                 \
    ((x) == EMB_DETECT_TMR4_PWM_W_BOTH_HIGH))

#define IS_EMB_TMR4_PWM_V_STAT(x)                                              \
(   ((x) == EMB_TMR4_PWM_V_ENABLE)          ||                                 \
    ((x) == EMB_TMR4_PWM_V_DISABLE))

#define IS_EMB_DETECT_TMR4_PWM_V_LVL(x)                                        \
(   ((x) == EMB_DETECT_TMR4_PWM_V_BOTH_LOW) ||                                 \
    ((x) == EMB_DETECT_TMR4_PWM_V_BOTH_HIGH))

#define IS_EMB_TMR4_PWM_U_STAT(x)                                              \
(   ((x) == EMB_TMR4_PWM_U_ENABLE)          ||                                 \
    ((x) == EMB_TMR4_PWM_U_DISABLE))

#define IS_EMB_DETECT_TMR4_PWM_U_LVL(x)                                        \
(   ((x) == EMB_DETECT_TMR4_PWM_U_BOTH_LOW) ||                                 \
    ((x) == EMB_DETECT_TMR4_PWM_U_BOTH_HIGH))

#define IS_EMB_CMP1_STAT(x)                                                    \
(   ((x) == EMB_CMP1_ENABLE)                ||                                 \
    ((x) == EMB_CMP1_DISABLE))

#define IS_EMB_CMP2_STAT(x)                                                    \
(   ((x) == EMB_CMP2_ENABLE)                ||                                 \
    ((x) == EMB_CMP2_DISABLE))

#define IS_EMB_CMP3_STAT(x)                                                    \
(   ((x) == EMB_CMP3_ENABLE)                ||                                 \
    ((x) == EMB_CMP3_DISABLE))

#define IS_EMB_PORT1_STAT(x)                                                   \
(   ((x) == EMB_PORT1_ENABLE)               ||                                 \
    ((x) == EMB_PORT1_DISABLE))

#define IS_EMB_PORT1_DETECT_LVL(x)                                             \
(   ((x) == EMB_PORT1_DETECT_LVL_LOW)       ||                                 \
    ((x) == EMB_PORT1_DETECT_LVL_HIGH))

#define IS_EMB_PORT1_FILTER_STAT(x)                                            \
(   ((x) == EMB_PORT1_FILTER_ENABLE)        ||                                 \
    ((x) == EMB_PORT1_FILTER_DISABLE))

#define IS_EMB_PORT1_FILTER_DIV(x)          (((x) & (~EMB_PORT1_FILTER_CLK_DIV_MASK)) == 0UL)

#define IS_EMB_TMR6_1_PWM_STAT(x)                                              \
(   ((x) == EMB_TMR6_1_PWM_ENABLE)          ||                                 \
    ((x) == EMB_TMR6_1_PWM_DISABLE))

#define IS_EMB_DETECT_TMR6_1_PWM_LVL(x)                                        \
(   ((x) == EMB_DETECT_TMR6_1_PWM_BOTH_LOW) ||                                 \
    ((x) == EMB_DETECT_TMR6_1_PWM_BOTH_HIGH))

#define IS_EMB_TMR6_2_PWM_STAT(x)                                              \
(   ((x) == EMB_TMR6_2_PWM_ENABLE)          ||                                 \
    ((x) == EMB_TMR6_2_PWM_DISABLE))

#define IS_EMB_DETECT_TMR6_2_PWM_LVL(x)                                        \
(   ((x) == EMB_DETECT_TMR6_2_PWM_BOTH_LOW) ||                                 \
    ((x) == EMB_DETECT_TMR6_2_PWM_BOTH_HIGH))

#define IS_EMB_TMR6_3_PWM_STAT(x)                                              \
(   ((x) == EMB_TMR6_3_PWM_ENABLE)          ||                                 \
    ((x) == EMB_TMR6_3_PWM_DISABLE))

#define IS_EMB_DETECT_TMR6_3_PWM_LVL(x)                                        \
(   ((x) == EMB_DETECT_TMR6_3_PWM_BOTH_LOW) ||                                 \
    ((x) == EMB_DETECT_TMR6_3_PWM_BOTH_HIGH))

#define IS_VALID_EMB_INT(x)                                                    \
(   ((x) != 0UL)                            &&                                 \
    (((x) | EMB_INT_ALL) == EMB_INT_ALL))

#define IS_EMB_FLAG(x)                                                         \
(   ((x) != 0UL)                            &&                                 \
    (((x) | EMB_FLAG_ALL) == EMB_FLAG_ALL))

/**
 * @}
 */

#define EMB_PORT1_FILTER_CLK_DIV_MASK       EMB_PORT1_FILTER_CLK_DIV128
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
 * @defgroup EMB_Global_Functions EMB Global Functions
 * @{
 */

/**
 * @brief  Set the fields of structure stc_emb_tmr4_init_t to default values
 * @param  [out] pstcEmbInit           Pointer to a @ref stc_emb_tmr4_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcEmbInit value is NULL.
 */
int32_t EMB_TMR4_StructInit(stc_emb_tmr4_init_t *pstcEmbInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcEmbInit) {
        /* OSC */
        pstcEmbInit->stcOsc.u32OscState = EMB_OSC_DISABLE;

        /* CMP */
        pstcEmbInit->stcCmp.u32Cmp1State = EMB_CMP1_DISABLE;
        pstcEmbInit->stcCmp.u32Cmp2State = EMB_CMP2_DISABLE;
        pstcEmbInit->stcCmp.u32Cmp3State = EMB_CMP3_DISABLE;

        /* Port */
        pstcEmbInit->stcPort.stcPort1.u32PortState = EMB_PORT1_DISABLE;
        pstcEmbInit->stcPort.stcPort1.u32PortLevel = EMB_PORT1_DETECT_LVL_HIGH;
        pstcEmbInit->stcPort.stcPort1.u32PortFilterDiv = EMB_PORT1_FILTER_CLK_DIV1;
        pstcEmbInit->stcPort.stcPort1.u32PortFilterState = EMB_PORT1_FILTER_DISABLE;

        /* PWM */
        pstcEmbInit->stcTmr4.stcTmr4PwmU.u32PwmState = EMB_TMR4_PWM_U_DISABLE;
        pstcEmbInit->stcTmr4.stcTmr4PwmU.u32PwmLevel = EMB_DETECT_TMR4_PWM_U_BOTH_LOW;
        pstcEmbInit->stcTmr4.stcTmr4PwmV.u32PwmState = EMB_TMR4_PWM_V_DISABLE;
        pstcEmbInit->stcTmr4.stcTmr4PwmV.u32PwmLevel = EMB_DETECT_TMR4_PWM_V_BOTH_LOW;
        pstcEmbInit->stcTmr4.stcTmr4PwmW.u32PwmState = EMB_TMR4_PWM_W_DISABLE;
        pstcEmbInit->stcTmr4.stcTmr4PwmW.u32PwmLevel = EMB_DETECT_TMR4_PWM_W_BOTH_LOW;

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize EMB for TMR4.
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMBx:              EMB group instance register base
 * @param  [in] pstcEmbInit             Pointer to a @ref stc_emb_tmr4_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcEmbInit value is NULL.
 */
int32_t EMB_TMR4_Init(CM_EMB_TypeDef *EMBx, const stc_emb_tmr4_init_t *pstcEmbInit)
{
    uint32_t u32Reg1Value;
    uint32_t u32Reg2Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcEmbInit) {
        DDL_ASSERT(IS_EMB_TMR4_GROUP(EMBx));
        DDL_ASSERT(IS_EMB_OSC_STAT(pstcEmbInit->stcOsc.u32OscState));
        DDL_ASSERT(IS_EMB_CMP1_STAT(pstcEmbInit->stcCmp.u32Cmp1State));
        DDL_ASSERT(IS_EMB_CMP2_STAT(pstcEmbInit->stcCmp.u32Cmp2State));
        DDL_ASSERT(IS_EMB_CMP3_STAT(pstcEmbInit->stcCmp.u32Cmp3State));
        DDL_ASSERT(IS_EMB_PORT1_STAT(pstcEmbInit->stcPort.stcPort1.u32PortState));
        DDL_ASSERT(IS_EMB_PORT1_DETECT_LVL(pstcEmbInit->stcPort.stcPort1.u32PortLevel));
        DDL_ASSERT(IS_EMB_PORT1_FILTER_DIV(pstcEmbInit->stcPort.stcPort1.u32PortFilterDiv));
        DDL_ASSERT(IS_EMB_PORT1_FILTER_STAT(pstcEmbInit->stcPort.stcPort1.u32PortFilterState));
        DDL_ASSERT(IS_EMB_TMR4_PWM_U_STAT(pstcEmbInit->stcTmr4.stcTmr4PwmU.u32PwmState));
        DDL_ASSERT(IS_EMB_DETECT_TMR4_PWM_U_LVL(pstcEmbInit->stcTmr4.stcTmr4PwmU.u32PwmLevel));
        DDL_ASSERT(IS_EMB_TMR4_PWM_V_STAT(pstcEmbInit->stcTmr4.stcTmr4PwmV.u32PwmState));
        DDL_ASSERT(IS_EMB_DETECT_TMR4_PWM_V_LVL(pstcEmbInit->stcTmr4.stcTmr4PwmV.u32PwmLevel));
        DDL_ASSERT(IS_EMB_TMR4_PWM_W_STAT(pstcEmbInit->stcTmr4.stcTmr4PwmW.u32PwmState));
        DDL_ASSERT(IS_EMB_DETECT_TMR4_PWM_W_LVL(pstcEmbInit->stcTmr4.stcTmr4PwmW.u32PwmLevel));

        /* OSC */
        u32Reg1Value = pstcEmbInit->stcOsc.u32OscState;
        u32Reg2Value = 0UL;

        /* PWM */
        u32Reg1Value |= (pstcEmbInit->stcTmr4.stcTmr4PwmU.u32PwmState | pstcEmbInit->stcTmr4.stcTmr4PwmV.u32PwmState | \
                         pstcEmbInit->stcTmr4.stcTmr4PwmW.u32PwmState);
        u32Reg2Value |= (pstcEmbInit->stcTmr4.stcTmr4PwmU.u32PwmLevel | pstcEmbInit->stcTmr4.stcTmr4PwmV.u32PwmLevel | \
                         pstcEmbInit->stcTmr4.stcTmr4PwmW.u32PwmLevel);

        /* CMP */
        u32Reg1Value |= (pstcEmbInit->stcCmp.u32Cmp1State | pstcEmbInit->stcCmp.u32Cmp2State | \
                         pstcEmbInit->stcCmp.u32Cmp3State);

        /* PORT */
        u32Reg1Value |= (pstcEmbInit->stcPort.stcPort1.u32PortState     | pstcEmbInit->stcPort.stcPort1.u32PortLevel | \
                         pstcEmbInit->stcPort.stcPort1.u32PortFilterDiv | pstcEmbInit->stcPort.stcPort1.u32PortFilterState);

        WRITE_REG32(EMBx->PWMLV, u32Reg2Value);
        WRITE_REG32(EMBx->CTL, u32Reg1Value);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Set the fields of structure stc_emb_tmr6_init_t to default values
 * @param  [out] pstcEmbInit            Pointer to a @ref stc_emb_tmr6_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcEmbInit value is NULL.
 */
int32_t EMB_TMR6_StructInit(stc_emb_tmr6_init_t *pstcEmbInit)
{
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcEmbInit) {
        /* OSC */
        pstcEmbInit->stcOsc.u32OscState = EMB_OSC_DISABLE;

        /* CMP */
        pstcEmbInit->stcCmp.u32Cmp1State = EMB_CMP1_DISABLE;
        pstcEmbInit->stcCmp.u32Cmp2State = EMB_CMP2_DISABLE;
        pstcEmbInit->stcCmp.u32Cmp3State = EMB_CMP3_DISABLE;

        /* Port */
        pstcEmbInit->stcPort.stcPort1.u32PortState = EMB_PORT1_DISABLE;
        pstcEmbInit->stcPort.stcPort1.u32PortLevel = EMB_PORT1_DETECT_LVL_HIGH;
        pstcEmbInit->stcPort.stcPort1.u32PortFilterDiv = EMB_PORT1_FILTER_CLK_DIV1;
        pstcEmbInit->stcPort.stcPort1.u32PortFilterState = EMB_PORT1_FILTER_DISABLE;

        /* PWM */
        pstcEmbInit->stcTmr6.stcTmr6_1.u32PwmLevel = EMB_DETECT_TMR6_1_PWM_BOTH_LOW;
        pstcEmbInit->stcTmr6.stcTmr6_1.u32PwmState = EMB_TMR6_1_PWM_DISABLE;
        pstcEmbInit->stcTmr6.stcTmr6_2.u32PwmLevel = EMB_DETECT_TMR6_2_PWM_BOTH_LOW;
        pstcEmbInit->stcTmr6.stcTmr6_2.u32PwmState = EMB_TMR6_2_PWM_DISABLE;
        pstcEmbInit->stcTmr6.stcTmr6_3.u32PwmLevel = EMB_DETECT_TMR6_3_PWM_BOTH_LOW;
        pstcEmbInit->stcTmr6.stcTmr6_3.u32PwmState = EMB_TMR6_3_PWM_DISABLE;

        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  Initialize EMB for TMR6.
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMBx:              EMB group instance register base
 * @param  [in] pstcEmbInit             Pointer to a @ref stc_emb_tmr6_init_t structure
 * @retval int32_t:
 *           - LL_OK:                   Initialize successfully.
 *           - LL_ERR_INVD_PARAM:       The pointer pstcEmbInit value is NULL.
 */
int32_t EMB_TMR6_Init(CM_EMB_TypeDef *EMBx, const stc_emb_tmr6_init_t *pstcEmbInit)
{
    uint32_t u32Reg1Value;
    uint32_t u32Reg2Value;
    int32_t i32Ret = LL_ERR_INVD_PARAM;

    if (NULL != pstcEmbInit) {
        DDL_ASSERT(IS_EMB_TMR6_GROUP(EMBx));
        DDL_ASSERT(IS_EMB_OSC_STAT(pstcEmbInit->stcOsc.u32OscState));
        DDL_ASSERT(IS_EMB_CMP1_STAT(pstcEmbInit->stcCmp.u32Cmp1State));
        DDL_ASSERT(IS_EMB_CMP2_STAT(pstcEmbInit->stcCmp.u32Cmp2State));
        DDL_ASSERT(IS_EMB_CMP3_STAT(pstcEmbInit->stcCmp.u32Cmp3State));
        DDL_ASSERT(IS_EMB_PORT1_STAT(pstcEmbInit->stcPort.stcPort1.u32PortState));
        DDL_ASSERT(IS_EMB_PORT1_DETECT_LVL(pstcEmbInit->stcPort.stcPort1.u32PortLevel));
        DDL_ASSERT(IS_EMB_PORT1_FILTER_DIV(pstcEmbInit->stcPort.stcPort1.u32PortFilterDiv));
        DDL_ASSERT(IS_EMB_PORT1_FILTER_STAT(pstcEmbInit->stcPort.stcPort1.u32PortFilterState));
        DDL_ASSERT(IS_EMB_TMR6_1_PWM_STAT(pstcEmbInit->stcTmr6.stcTmr6_1.u32PwmState));
        DDL_ASSERT(IS_EMB_DETECT_TMR6_1_PWM_LVL(pstcEmbInit->stcTmr6.stcTmr6_1.u32PwmLevel));
        DDL_ASSERT(IS_EMB_TMR6_2_PWM_STAT(pstcEmbInit->stcTmr6.stcTmr6_2.u32PwmState));
        DDL_ASSERT(IS_EMB_DETECT_TMR6_2_PWM_LVL(pstcEmbInit->stcTmr6.stcTmr6_2.u32PwmLevel));
        DDL_ASSERT(IS_EMB_TMR6_3_PWM_STAT(pstcEmbInit->stcTmr6.stcTmr6_3.u32PwmState));
        DDL_ASSERT(IS_EMB_DETECT_TMR6_3_PWM_LVL(pstcEmbInit->stcTmr6.stcTmr6_3.u32PwmLevel));

        /* OSC */
        u32Reg2Value = 0UL;
        u32Reg1Value = pstcEmbInit->stcOsc.u32OscState;

        /* PWM */
        u32Reg1Value |= (pstcEmbInit->stcTmr6.stcTmr6_1.u32PwmState | pstcEmbInit->stcTmr6.stcTmr6_2.u32PwmState | \
                         pstcEmbInit->stcTmr6.stcTmr6_3.u32PwmState);
        u32Reg2Value |= (pstcEmbInit->stcTmr6.stcTmr6_1.u32PwmLevel | pstcEmbInit->stcTmr6.stcTmr6_2.u32PwmLevel | \
                         pstcEmbInit->stcTmr6.stcTmr6_3.u32PwmLevel);

        /* CMP */
        u32Reg1Value |= (pstcEmbInit->stcCmp.u32Cmp1State | pstcEmbInit->stcCmp.u32Cmp2State | \
                         pstcEmbInit->stcCmp.u32Cmp3State);

        /* PORT */
        u32Reg1Value |= (pstcEmbInit->stcPort.stcPort1.u32PortState | pstcEmbInit->stcPort.stcPort1.u32PortFilterDiv | \
                         pstcEmbInit->stcPort.stcPort1.u32PortLevel | pstcEmbInit->stcPort.stcPort1.u32PortFilterState);

        WRITE_REG32(EMBx->PWMLV, u32Reg2Value);
        WRITE_REG32(EMBx->CTL, u32Reg1Value);
        i32Ret = LL_OK;
    }

    return i32Ret;
}

/**
 * @brief  De-Initialize EMB function
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMBx:              EMB group instance register base
 * @retval None
 */
void EMB_DeInit(CM_EMB_TypeDef *EMBx)
{
    DDL_ASSERT(IS_EMB_GROUP(EMBx));

    WRITE_REG32(EMBx->SOE, 0x00UL);
    WRITE_REG32(EMBx->INTEN, 0x00UL);
}

/**
 * @brief  Set the EMB interrupt function
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMBx:              EMB group instance register base
 * @param  [in] u32IntType              EMB interrupt source
 *         This parameter can be any composed value of the macros group @ref EMB_Interrupt.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EMB_IntCmd(CM_EMB_TypeDef *EMBx, uint32_t u32IntType, en_functional_state_t enNewState)
{
    DDL_ASSERT(IS_EMB_GROUP(EMBx));
    DDL_ASSERT(IS_VALID_EMB_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (ENABLE == enNewState) {
        SET_REG32_BIT(EMBx->INTEN, u32IntType);
    } else {
        CLR_REG32_BIT(EMBx->INTEN, u32IntType);
    }
}

/**
 * @brief  Get EMB flag status.
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMBx:              EMB group instance register base
 * @param  [in] u32Flag                 EMB flag
 *         This parameter can be any composed value(prefix with EMB_FLAG) of the macros group @ref EMB_Flag_State.
 * @retval None
 * @note This parameter u32Flag prefix with EMB_FLAG(eg EMB_FLAG_CMP) of the macros group @ref EMB_Flag_State.
 */
void EMB_ClearStatus(CM_EMB_TypeDef *EMBx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_EMB_GROUP(EMBx));
    DDL_ASSERT(IS_EMB_FLAG(u32Flag));

    SET_REG32_BIT(EMBx->STATCLR, u32Flag);
}

/**
 * @brief  Clear EMB flag status.
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMBx:              EMB group instance register base
 * @param  [in] u32Flag                 EMB flag
 *         This parameter can be any composed value of the macros group @ref EMB_Flag_State.
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t EMB_GetStatus(const CM_EMB_TypeDef *EMBx, uint32_t u32Flag)
{
    DDL_ASSERT(IS_EMB_GROUP(EMBx));
    DDL_ASSERT(IS_EMB_FLAG(u32Flag));

    return (READ_REG32_BIT(EMBx->STAT, u32Flag) == 0UL) ? RESET : SET;
}

/**
 * @brief  Start/stop EMB brake by software control
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg CM_EMBx:              EMB group instance register base
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void EMB_SWBrake(CM_EMB_TypeDef *EMBx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_EMB_GROUP(EMBx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(EMBx->SOE, enNewState);
}

/**
 * @}
 */

#endif /* LL_EMB_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
