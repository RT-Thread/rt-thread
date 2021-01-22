/**
 *******************************************************************************
 * @file  hc32f4a0_emb.c
 * @brief This file provides firmware functions to manage the EMB
 *        (Emergency Brake).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Hongjh          First version
   2020-07-07       Hongjh          Replace the word Timer with TMR abbreviation
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
#include "hc32f4a0_emb.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_EMB EMB
 * @brief Emergency Brake Driver Library
 * @{
 */

#if (DDL_EMB_ENABLE == DDL_ON)

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

#define IS_VALID_EMB(x)                                                        \
(   ((x) == M4_EMB0)                            ||                             \
    ((x) == M4_EMB1)                            ||                             \
    ((x) == M4_EMB2)                            ||                             \
    ((x) == M4_EMB3)                            ||                             \
    ((x) == M4_EMB4)                            ||                             \
    ((x) == M4_EMB5)                            ||                             \
    ((x) == M4_EMB6))

#define IS_VALID_EMB_TMR6(x)                                                   \
(   ((x) == M4_EMB0)                            ||                             \
    ((x) == M4_EMB1)                            ||                             \
    ((x) == M4_EMB2)                            ||                             \
    ((x) == M4_EMB3))

#define IS_VALID_EMB_TIMER4(x)                                                 \
(   ((x) == M4_EMB4)                            ||                             \
    ((x) == M4_EMB5)                            ||                             \
    ((x) == M4_EMB6))

#define IS_VALID_EMB_CMP1_SEL(x)                                               \
(   ((x) == EMB_CMP1_ENABLE)                    ||                             \
    ((x) == EMB_CMP1_DISABLE))

#define IS_VALID_EMB_CMP2_SEL(x)                                               \
(   ((x) == EMB_CMP2_ENABLE)                    ||                             \
    ((x) == EMB_CMP2_DISABLE))

#define IS_VALID_EMB_CMP3_SEL(x)                                               \
(   ((x) == EMB_CMP3_ENABLE)                    ||                             \
    ((x) == EMB_CMP3_DISABLE))

#define IS_VALID_EMB_CMP4_SEL(x)                                               \
(   ((x) == EMB_CMP4_ENABLE)                    ||                             \
    ((x) == EMB_CMP4_DISABLE))

#define IS_VALID_EMB_PORT1_SEL(x)                                              \
(   ((x) == EMB_PORT1_ENABLE)                   ||                             \
    ((x) == EMB_PORT1_DISABLE))

#define IS_VALID_EMB_PORT2_SEL(x)                                              \
(   ((x) == EMB_PORT2_ENABLE)                   ||                             \
    ((x) == EMB_PORT2_DISABLE))

#define IS_VALID_EMB_PORT3_SEL(x)                                              \
(   ((x) == EMB_PORT3_ENABLE)                   ||                             \
    ((x) == EMB_PORT3_DISABLE))

#define IS_VALID_EMB_PORT4_SEL(x)                                              \
(   ((x) == EMB_PORT4_ENABLE)                   ||                             \
    ((x) == EMB_PORT4_DISABLE))

#define IS_VALID_EMB_OSC_SEL(x)                                                \
(   ((x) == EMB_OSC_ENABLE)                     ||                             \
    ((x) == EMB_OSC_DISABLE))

#define IS_VALID_EMB_TMR4_PWM_W_SEL(x)                                         \
(   ((x) == EMB_TMR4_PWM_W_ENABLE)              ||                             \
    ((x) == EMB_TMR4_PWM_W_DISABLE))

#define IS_VALID_EMB_TMR4_PWM_V_SEL(x)                                         \
(   ((x) == EMB_TMR4_PWM_V_ENABLE)              ||                             \
    ((x) == EMB_TMR4_PWM_V_DISABLE))

#define IS_VALID_EMB_TMR4_PWM_U_SEL(x)                                         \
(   ((x) == EMB_TMR4_PWM_U_ENABLE)              ||                             \
    ((x) == EMB_TMR4_PWM_U_DISABLE))

#define IS_VALID_EMB_TMR6_1_PWM_SEL(x)                                         \
(   ((x) == EMB_TMR6_1_PWM_ENABLE)              ||                             \
    ((x) == EMB_TMR6_1_PWM_DISABLE))

#define IS_VALID_EMB_TMR6_2_PWM_SEL(x)                                         \
(   ((x) == EMB_TMR6_2_PWM_ENABLE)              ||                             \
    ((x) == EMB_TMR6_2_PWM_DISABLE))

#define IS_VALID_EMB_TMR6_3_PWM_SEL(x)                                         \
(   ((x) == EMB_TMR6_3_PWM_ENABLE)              ||                             \
    ((x) == EMB_TMR6_3_PWM_DISABLE))

#define IS_VALID_EMB_TMR6_4_PWM_SEL(x)                                         \
(   ((x) == EMB_TMR6_4_PWM_ENABLE)              ||                             \
    ((x) == EMB_TMR6_4_PWM_DISABLE))

#define IS_VALID_EMB_TMR6_5_PWM_SEL(x)                                         \
(   ((x) == EMB_TMR6_5_PWM_ENABLE)              ||                             \
    ((x) == EMB_TMR6_5_PWM_DISABLE))

#define IS_VALID_EMB_TMR6_6_PWM_SEL(x)                                         \
(   ((x) == EMB_TMR6_6_PWM_ENABLE)              ||                             \
    ((x) == EMB_TMR6_6_PWM_DISABLE))

#define IS_VALID_EMB_TMR6_7_PWM_SEL(x)                                         \
(   ((x) == EMB_TMR6_7_PWM_ENABLE)              ||                             \
    ((x) == EMB_TMR6_7_PWM_DISABLE))

#define IS_VALID_EMB_TMR6_8_PWM_SEL(x)                                         \
(   ((x) == EMB_TMR6_8_PWM_ENABLE)              ||                             \
    ((x) == EMB_TMR6_8_PWM_DISABLE))

#define IS_VALID_EMB_DETECT_PORT1_LEVEL(x)                                     \
(   ((x) == EMB_DETECT_PORT1_LEVEL_LOW)         ||                             \
    ((x) == EMB_DETECT_PORT1_LEVEL_HIGH))

#define IS_VALID_EMB_DETECT_PORT2_LEVEL(x)                                     \
(   ((x) == EMB_DETECT_PORT2_LEVEL_LOW)         ||                             \
    ((x) == EMB_DETECT_PORT2_LEVEL_HIGH))

#define IS_VALID_EMB_DETECT_PORT3_LEVEL(x)                                     \
(   ((x) == EMB_DETECT_PORT3_LEVEL_LOW)         ||                             \
    ((x) == EMB_DETECT_PORT3_LEVEL_HIGH))

#define IS_VALID_EMB_DETECT_PORT4_LEVEL(x)                                     \
(   ((x) == EMB_DETECT_PORT4_LEVEL_LOW)         ||                             \
    ((x) == EMB_DETECT_PORT4_LEVEL_HIGH))

#define IS_VALID_EMB_DETECT_TMR4_PWM_W_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR4_PWM_W_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR4_PWM_W_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR4_PWM_V_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR4_PWM_V_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR4_PWM_V_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR4_PWM_U_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR4_PWM_U_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR4_PWM_U_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR6_1_PWM_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR6_1_PWM_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR6_1_PWM_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR6_2_PWM_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR6_2_PWM_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR6_2_PWM_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR6_3_PWM_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR6_3_PWM_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR6_3_PWM_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR6_4_PWM_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR6_4_PWM_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR6_4_PWM_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR6_5_PWM_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR6_5_PWM_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR6_5_PWM_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR6_6_PWM_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR6_6_PWM_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR6_6_PWM_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR6_7_PWM_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR6_7_PWM_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR6_7_PWM_BOTH_HIGH))

#define IS_VALID_EMB_DETECT_TMR6_8_PWM_LEVEL(x)                                \
(   ((x) == EMB_DETECT_TMR6_8_PWM_BOTH_LOW)     ||                             \
    ((x) == EMB_DETECT_TMR6_8_PWM_BOTH_HIGH))

#define IS_VALID_EMB_INT(x)                                                    \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~IS_EMB_INT_MASK))))

#define IS_VALID_EMB_FLAG(x)                                                   \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~IS_EMB_FLAG_MASK))))

#define IS_VALID_EMB_STATUS(x)                                                 \
(   (0UL != (x))                                &&                             \
    (0UL == ((x) & (~IS_EMB_STATUS_MASK))))

#define IS_VALID_EMB_PORT1_FILTER_DIV(x)                                       \
(   ((x) == EMB_PORT1_FILTER_NONE)              ||                             \
    ((x) == EMB_PORT1_FILTER_CLK_DIV1)          ||                             \
    ((x) == EMB_PORT1_FILTER_CLK_DIV8)          ||                             \
    ((x) == EMB_PORT1_FILTER_CLK_DIV32)         ||                             \
    ((x) == EMB_PORT1_FILTER_CLK_DIV128))

#define IS_VALID_EMB_PORT2_FILTER_DIV(x)                                       \
(   ((x) == EMB_PORT2_FILTER_NONE)              ||                             \
    ((x) == EMB_PORT2_FILTER_CLK_DIV1)          ||                             \
    ((x) == EMB_PORT2_FILTER_CLK_DIV8)          ||                             \
    ((x) == EMB_PORT2_FILTER_CLK_DIV32)         ||                             \
    ((x) == EMB_PORT2_FILTER_CLK_DIV128))

#define IS_VALID_EMB_PORT3_FILTER_DIV(x)                                       \
(   ((x) == EMB_PORT3_FILTER_NONE)              ||                             \
    ((x) == EMB_PORT3_FILTER_CLK_DIV1)          ||                             \
    ((x) == EMB_PORT3_FILTER_CLK_DIV8)          ||                             \
    ((x) == EMB_PORT3_FILTER_CLK_DIV32)         ||                             \
    ((x) == EMB_PORT3_FILTER_CLK_DIV128))

#define IS_VALID_EMB_PORT4_FILTER_DIV(x)                                       \
(   ((x) == EMB_PORT4_FILTER_NONE)              ||                             \
    ((x) == EMB_PORT4_FILTER_CLK_DIV1)          ||                             \
    ((x) == EMB_PORT4_FILTER_CLK_DIV8)          ||                             \
    ((x) == EMB_PORT4_FILTER_CLK_DIV32)         ||                             \
    ((x) == EMB_PORT4_FILTER_CLK_DIV128))

#define IS_VALID_EMB_RELEASE_PWM_SEL(x)                                        \
(   ((x) == EMB_RELEASE_PWM_SEL_FLAG_ZERO)      ||                             \
    ((x) == EMB_RELEASE_PWM_SEL_STATE_ZERO))

#define IS_VALID_EMB_MONITOR_EVENT(x)                                          \
(   ((x) == EMB_EVENT_PWMS)                     ||                             \
    ((x) == EMB_EVENT_CMP)                      ||                             \
    ((x) == EMB_EVENT_OSC)                      ||                             \
    ((x) == EMB_EVENT_PORT1)                    ||                             \
    ((x) == EMB_EVENT_PORT2)                    ||                             \
    ((x) == EMB_EVENT_PORT3)                    ||                             \
    ((x) == EMB_EVENT_PORT4))
/**
 * @}
 */

/**
 * @defgroup EMB_INT_Mask EMB interrupt mask definition
 * @{
 */
#define IS_EMB_INT_MASK                         (EMB_INT_PWMS  |               \
                                                 EMB_INT_CMP   |               \
                                                 EMB_INT_OSC   |               \
                                                 EMB_INT_PORT1 |               \
                                                 EMB_INT_PORT2 |               \
                                                 EMB_INT_PORT3 |               \
                                                 EMB_INT_PORT4)
/**
 * @}
 */

/**
 * @defgroup EMB_Flag_Mask EMB flag mask definition
 * @{
 */
#define IS_EMB_FLAG_MASK                        (EMB_FLAG_PWMS  |              \
                                                 EMB_FLAG_CMP   |              \
                                                 EMB_FLAG_OSC   |              \
                                                 EMB_FLAG_PORT1 |              \
                                                 EMB_FLAG_PORT2 |              \
                                                 EMB_FLAG_PORT3 |              \
                                                 EMB_FLAG_PORT4)
/**
 * @}
 */

/**
 * @defgroup EMB_Status_Mask EMB status mask definition
 * @{
 */
#define IS_EMB_STATUS_MASK                      (EMB_STATE_PWMS  |             \
                                                 EMB_STATE_CMP   |             \
                                                 EMB_STATE_OSC   |             \
                                                 EMB_STATE_PORT1 |             \
                                                 EMB_STATE_PORT2 |             \
                                                 EMB_STATE_PORT3 |             \
                                                 EMB_STATE_PORT4)
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
 * @defgroup EMB_Global_Functions EMB Global Functions
 * @{
 */

/**
 * @brief  Initialize EMB for TMR4.
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_emb_tmr4_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 * @note   TMR4 feature is supported by M4_EMB4/M4_EMB5/M4_EMB6
 */
en_result_t EMB_Tmr4Init(M4_EMB_TypeDef *EMBx,
                            const stc_emb_tmr4_init_t *pstcInit)
{
    uint32_t u32RegVal;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_EMB_TIMER4(EMBx));
        DDL_ASSERT(IS_VALID_EMB_CMP1_SEL(pstcInit->u32Cmp1));
        DDL_ASSERT(IS_VALID_EMB_CMP2_SEL(pstcInit->u32Cmp2));
        DDL_ASSERT(IS_VALID_EMB_CMP3_SEL(pstcInit->u32Cmp3));
        DDL_ASSERT(IS_VALID_EMB_CMP4_SEL(pstcInit->u32Cmp4));
        DDL_ASSERT(IS_VALID_EMB_OSC_SEL(pstcInit->u32Osc));
        DDL_ASSERT(IS_VALID_EMB_PORT1_SEL(pstcInit->stcPort1.u32PortSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_PORT1_LEVEL(pstcInit->stcPort1.u32PortLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT1_FILTER_DIV(pstcInit->stcPort1.u32PortFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT2_SEL(pstcInit->stcPort2.u32PortSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_PORT2_LEVEL(pstcInit->stcPort2.u32PortLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT2_FILTER_DIV(pstcInit->stcPort2.u32PortFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT3_SEL(pstcInit->stcPort3.u32PortSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_PORT3_LEVEL(pstcInit->stcPort3.u32PortLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT3_FILTER_DIV(pstcInit->stcPort3.u32PortFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT4_SEL(pstcInit->stcPort4.u32PortSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_PORT4_LEVEL(pstcInit->stcPort4.u32PortLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT4_FILTER_DIV(pstcInit->stcPort4.u32PortFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_TMR4_PWM_U_SEL(pstcInit->stcTmr4PwmU.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR4_PWM_U_LEVEL(pstcInit->stcTmr4PwmU.u32PwmLevel));
        DDL_ASSERT(IS_VALID_EMB_TMR4_PWM_V_SEL(pstcInit->stcTmr4PwmV.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR4_PWM_V_LEVEL(pstcInit->stcTmr4PwmV.u32PwmLevel));
        DDL_ASSERT(IS_VALID_EMB_TMR4_PWM_W_SEL(pstcInit->stcTmr4PwmW.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR4_PWM_W_LEVEL(pstcInit->stcTmr4PwmW.u32PwmLevel));

        /* Set default value && clear flag */
        WRITE_REG32(EMBx->SOE, 0x00UL);
        WRITE_REG32(EMBx->RLSSEL, 0x00UL);
        WRITE_REG32(EMBx->INTEN, 0x00UL);
        WRITE_REG32(EMBx->STATCLR, (EMB_STATCLR_PWMSFCLR | \
                                    EMB_STATCLR_CMPFCLR | \
                                    EMB_STATCLR_OSFCLR | \
                                    EMB_STATCLR_PORTINFCLR1 | \
                                    EMB_STATCLR_PORTINFCLR2 | \
                                    EMB_STATCLR_PORTINFCLR3 | \
                                    EMB_STATCLR_PORTINFCLR4));

        /* Set EMB_CTL register */
        u32RegVal = (pstcInit->u32Cmp1 | \
                     pstcInit->u32Cmp2 | \
                     pstcInit->u32Cmp3 | \
                     pstcInit->u32Cmp4 | \
                     pstcInit->u32Osc | \
                     pstcInit->stcTmr4PwmW.u32PwmSel | \
                     pstcInit->stcTmr4PwmV.u32PwmSel | \
                     pstcInit->stcTmr4PwmU.u32PwmSel | \
                     pstcInit->stcPort1.u32PortSel | \
                     pstcInit->stcPort2.u32PortSel | \
                     pstcInit->stcPort3.u32PortSel | \
                     pstcInit->stcPort4.u32PortSel | \
                     pstcInit->stcPort1.u32PortLevel | \
                     pstcInit->stcPort2.u32PortLevel | \
                     pstcInit->stcPort3.u32PortLevel | \
                     pstcInit->stcPort4.u32PortLevel);
        WRITE_REG32(EMBx->CTL1, u32RegVal);

        /* Check writing EMB_CTL1 because EMB_CTL1 can write once only after reset */
        if (READ_REG32(EMBx->CTL1) == u32RegVal)
        {
            u32RegVal = (pstcInit->stcTmr4PwmW.u32PwmLevel | \
                         pstcInit->stcTmr4PwmV.u32PwmLevel | \
                         pstcInit->stcTmr4PwmU.u32PwmLevel | \
                         pstcInit->stcPort1.u32PortFilterDiv | \
                         pstcInit->stcPort2.u32PortFilterDiv | \
                         pstcInit->stcPort3.u32PortFilterDiv | \
                         pstcInit->stcPort4.u32PortFilterDiv);
            WRITE_REG32(EMBx->CTL2, u32RegVal);

            /* Check writing EMB_CTL2 because EMB_CTL2 can write once only after reset */
            if (READ_REG32(EMBx->CTL2) == u32RegVal)
            {
                 enRet = Ok;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_emb_tmr4_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_emb_tmr4_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EMB_Tmr4StructInit(stc_emb_tmr4_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32Cmp1 = EMB_CMP1_DISABLE;
        pstcInit->u32Cmp2 = EMB_CMP2_DISABLE;
        pstcInit->u32Cmp3 = EMB_CMP3_DISABLE;
        pstcInit->u32Cmp4 = EMB_CMP4_DISABLE;
        pstcInit->u32Osc = EMB_OSC_DISABLE;
        pstcInit->stcPort1.u32PortSel = EMB_PORT1_DISABLE;
        pstcInit->stcPort1.u32PortLevel = EMB_DETECT_PORT1_LEVEL_HIGH;
        pstcInit->stcPort1.u32PortFilterDiv = EMB_PORT1_FILTER_NONE;
        pstcInit->stcPort2.u32PortSel = EMB_PORT2_DISABLE;
        pstcInit->stcPort2.u32PortLevel = EMB_DETECT_PORT2_LEVEL_HIGH;
        pstcInit->stcPort2.u32PortFilterDiv = EMB_PORT2_FILTER_NONE;
        pstcInit->stcPort3.u32PortSel = EMB_PORT3_DISABLE;
        pstcInit->stcPort3.u32PortLevel = EMB_DETECT_PORT3_LEVEL_HIGH;
        pstcInit->stcPort3.u32PortFilterDiv = EMB_PORT3_FILTER_NONE;
        pstcInit->stcPort4.u32PortSel = EMB_PORT4_DISABLE;
        pstcInit->stcPort4.u32PortLevel = EMB_DETECT_PORT4_LEVEL_HIGH;
        pstcInit->stcPort4.u32PortFilterDiv = EMB_PORT4_FILTER_NONE;
        pstcInit->stcTmr4PwmU.u32PwmSel = EMB_TMR4_PWM_U_DISABLE;
        pstcInit->stcTmr4PwmU.u32PwmLevel = EMB_DETECT_TMR4_PWM_U_BOTH_LOW;
        pstcInit->stcTmr4PwmV.u32PwmSel = EMB_TMR4_PWM_V_DISABLE;
        pstcInit->stcTmr4PwmV.u32PwmLevel = EMB_DETECT_TMR4_PWM_V_BOTH_LOW;
        pstcInit->stcTmr4PwmW.u32PwmSel = EMB_TMR4_PWM_W_DISABLE;
        pstcInit->stcTmr4PwmW.u32PwmLevel = EMB_DETECT_TMR4_PWM_W_BOTH_LOW;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  Initialize EMB for TMR6.
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 0 instance register base
 *           @arg M4_EMB1:              EMB group 1 instance register base
 *           @arg M4_EMB2:              EMB group 2 instance register base
 *           @arg M4_EMB3:              EMB group 3 instance register base
 * @param  [in] pstcInit                Pointer to a @ref stc_emb_tmr6_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 * @note   TMR6 feature is supported by M4_EMB0/M4_EMB1/M4_EMB2/M4_EMB3
 */
en_result_t EMB_Tmr6Init(M4_EMB_TypeDef *EMBx,
                            const stc_emb_tmr6_init_t *pstcInit)
{
    uint32_t u32RegVal;
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_EMB_TMR6(EMBx));
        DDL_ASSERT(IS_VALID_EMB_CMP1_SEL(pstcInit->u32Cmp1));
        DDL_ASSERT(IS_VALID_EMB_CMP2_SEL(pstcInit->u32Cmp2));
        DDL_ASSERT(IS_VALID_EMB_CMP3_SEL(pstcInit->u32Cmp3));
        DDL_ASSERT(IS_VALID_EMB_CMP4_SEL(pstcInit->u32Cmp4));
        DDL_ASSERT(IS_VALID_EMB_OSC_SEL(pstcInit->u32Osc));
        DDL_ASSERT(IS_VALID_EMB_PORT1_SEL(pstcInit->stcPort1.u32PortSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_PORT1_LEVEL(pstcInit->stcPort1.u32PortLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT1_FILTER_DIV(pstcInit->stcPort1.u32PortFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT2_SEL(pstcInit->stcPort2.u32PortSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_PORT2_LEVEL(pstcInit->stcPort2.u32PortLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT2_FILTER_DIV(pstcInit->stcPort2.u32PortFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT3_SEL(pstcInit->stcPort3.u32PortSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_PORT3_LEVEL(pstcInit->stcPort3.u32PortLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT3_FILTER_DIV(pstcInit->stcPort3.u32PortFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_PORT4_SEL(pstcInit->stcPort4.u32PortSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_PORT4_LEVEL(pstcInit->stcPort4.u32PortLevel));
        DDL_ASSERT(IS_VALID_EMB_PORT4_FILTER_DIV(pstcInit->stcPort4.u32PortFilterDiv));
        DDL_ASSERT(IS_VALID_EMB_TMR6_1_PWM_SEL(pstcInit->stcTmr6_1.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR6_1_PWM_LEVEL(pstcInit->stcTmr6_1.u32PwmLevel));
        DDL_ASSERT(IS_VALID_EMB_TMR6_2_PWM_SEL(pstcInit->stcTmr6_2.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR6_2_PWM_LEVEL(pstcInit->stcTmr6_2.u32PwmLevel));
        DDL_ASSERT(IS_VALID_EMB_TMR6_3_PWM_SEL(pstcInit->stcTmr6_3.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR6_3_PWM_LEVEL(pstcInit->stcTmr6_3.u32PwmLevel));
        DDL_ASSERT(IS_VALID_EMB_TMR6_4_PWM_SEL(pstcInit->stcTmr6_4.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR6_4_PWM_LEVEL(pstcInit->stcTmr6_4.u32PwmLevel));
        DDL_ASSERT(IS_VALID_EMB_TMR6_5_PWM_SEL(pstcInit->stcTmr6_5.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR6_5_PWM_LEVEL(pstcInit->stcTmr6_5.u32PwmLevel));
        DDL_ASSERT(IS_VALID_EMB_TMR6_6_PWM_SEL(pstcInit->stcTmr6_6.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR6_6_PWM_LEVEL(pstcInit->stcTmr6_6.u32PwmLevel));
        DDL_ASSERT(IS_VALID_EMB_TMR6_7_PWM_SEL(pstcInit->stcTmr6_7.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR6_7_PWM_LEVEL(pstcInit->stcTmr6_7.u32PwmLevel));
        DDL_ASSERT(IS_VALID_EMB_TMR6_8_PWM_SEL(pstcInit->stcTmr6_8.u32PwmSel));
        DDL_ASSERT(IS_VALID_EMB_DETECT_TMR6_8_PWM_LEVEL(pstcInit->stcTmr6_8.u32PwmLevel));

        /* Set default value && clear flag */
        WRITE_REG32(EMBx->SOE, 0x00UL);
        WRITE_REG32(EMBx->RLSSEL, 0x00UL);
        WRITE_REG32(EMBx->INTEN, 0x00UL);
        WRITE_REG32(EMBx->STATCLR, (EMB_STATCLR_PWMSFCLR | \
                                    EMB_STATCLR_CMPFCLR | \
                                    EMB_STATCLR_OSFCLR | \
                                    EMB_STATCLR_PORTINFCLR1 | \
                                    EMB_STATCLR_PORTINFCLR2 | \
                                    EMB_STATCLR_PORTINFCLR3 | \
                                    EMB_STATCLR_PORTINFCLR4));

        /* Set EMB_CTL register */
        u32RegVal = (pstcInit->u32Cmp1 | \
                     pstcInit->u32Cmp2 | \
                     pstcInit->u32Cmp3 | \
                     pstcInit->u32Cmp4 | \
                     pstcInit->u32Osc | \
                     pstcInit->stcTmr6_1.u32PwmSel | \
                     pstcInit->stcTmr6_2.u32PwmSel | \
                     pstcInit->stcTmr6_3.u32PwmSel | \
                     pstcInit->stcTmr6_4.u32PwmSel | \
                     pstcInit->stcTmr6_5.u32PwmSel | \
                     pstcInit->stcTmr6_6.u32PwmSel | \
                     pstcInit->stcTmr6_7.u32PwmSel | \
                     pstcInit->stcTmr6_8.u32PwmSel | \
                     pstcInit->stcPort1.u32PortSel | \
                     pstcInit->stcPort2.u32PortSel | \
                     pstcInit->stcPort3.u32PortSel | \
                     pstcInit->stcPort4.u32PortSel | \
                     pstcInit->stcPort1.u32PortLevel | \
                     pstcInit->stcPort2.u32PortLevel | \
                     pstcInit->stcPort3.u32PortLevel | \
                     pstcInit->stcPort4.u32PortLevel);
        WRITE_REG32(EMBx->CTL1, u32RegVal);

        /* Check writing EMB_CTL1 because EMB_CTL1 can write once only after reset */
        if (READ_REG32(EMBx->CTL1) == u32RegVal)
        {
            u32RegVal = (pstcInit->stcTmr6_1.u32PwmLevel | \
                         pstcInit->stcTmr6_2.u32PwmLevel | \
                         pstcInit->stcTmr6_3.u32PwmLevel | \
                         pstcInit->stcTmr6_4.u32PwmLevel | \
                         pstcInit->stcTmr6_5.u32PwmLevel | \
                         pstcInit->stcTmr6_6.u32PwmLevel | \
                         pstcInit->stcTmr6_7.u32PwmLevel | \
                         pstcInit->stcTmr6_8.u32PwmLevel | \
                         pstcInit->stcPort1.u32PortFilterDiv | \
                         pstcInit->stcPort2.u32PortFilterDiv | \
                         pstcInit->stcPort3.u32PortFilterDiv | \
                         pstcInit->stcPort4.u32PortFilterDiv);
            WRITE_REG32(EMBx->CTL2, u32RegVal);

            /* Check writing EMB_CTL2 because EMB_CTL2 can write once only after reset */
            if (READ_REG32(EMBx->CTL2) == u32RegVal)
            {
                 enRet = Ok;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Set the fields of structure stc_emb_tmr6_init_t to default values
 * @param  [out] pstcInit               Pointer to a @ref stc_emb_tmr6_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize successfully
 *           - ErrorInvalidParameter: pstcInit = NULL
 */
en_result_t EMB_Tmr6StructInit(stc_emb_tmr6_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    /* Check structure pointer */
    if (NULL != pstcInit)
    {
        pstcInit->u32Cmp1 = EMB_CMP1_DISABLE;
        pstcInit->u32Cmp2 = EMB_CMP2_DISABLE;
        pstcInit->u32Cmp3 = EMB_CMP3_DISABLE;
        pstcInit->u32Cmp4 = EMB_CMP4_DISABLE;
        pstcInit->u32Osc = EMB_OSC_DISABLE;
        pstcInit->stcPort1.u32PortSel = EMB_PORT1_DISABLE;
        pstcInit->stcPort1.u32PortLevel = EMB_DETECT_PORT1_LEVEL_HIGH;
        pstcInit->stcPort1.u32PortFilterDiv = EMB_PORT1_FILTER_NONE;
        pstcInit->stcPort2.u32PortSel = EMB_PORT2_DISABLE;
        pstcInit->stcPort2.u32PortLevel = EMB_DETECT_PORT2_LEVEL_HIGH;
        pstcInit->stcPort2.u32PortFilterDiv = EMB_PORT2_FILTER_NONE;
        pstcInit->stcPort3.u32PortSel = EMB_PORT3_DISABLE;
        pstcInit->stcPort3.u32PortLevel = EMB_DETECT_PORT3_LEVEL_HIGH;
        pstcInit->stcPort3.u32PortFilterDiv = EMB_PORT3_FILTER_NONE;
        pstcInit->stcPort4.u32PortSel = EMB_PORT4_DISABLE;
        pstcInit->stcPort4.u32PortLevel = EMB_DETECT_PORT4_LEVEL_HIGH;
        pstcInit->stcPort4.u32PortFilterDiv = EMB_PORT4_FILTER_NONE;
        pstcInit->stcTmr6_1.u32PwmSel = EMB_TMR6_1_PWM_DISABLE;
        pstcInit->stcTmr6_1.u32PwmLevel = EMB_DETECT_TMR6_1_PWM_BOTH_LOW;
        pstcInit->stcTmr6_2.u32PwmSel = EMB_TMR6_2_PWM_DISABLE;
        pstcInit->stcTmr6_2.u32PwmLevel = EMB_DETECT_TMR6_2_PWM_BOTH_LOW;
        pstcInit->stcTmr6_3.u32PwmSel = EMB_TMR6_3_PWM_DISABLE;
        pstcInit->stcTmr6_3.u32PwmLevel = EMB_DETECT_TMR6_3_PWM_BOTH_LOW;
        pstcInit->stcTmr6_4.u32PwmSel = EMB_TMR6_4_PWM_DISABLE;
        pstcInit->stcTmr6_4.u32PwmLevel = EMB_DETECT_TMR6_4_PWM_BOTH_LOW;
        pstcInit->stcTmr6_5.u32PwmSel = EMB_TMR6_5_PWM_DISABLE;
        pstcInit->stcTmr6_5.u32PwmLevel = EMB_DETECT_TMR6_5_PWM_BOTH_LOW;
        pstcInit->stcTmr6_6.u32PwmSel = EMB_TMR6_6_PWM_DISABLE;
        pstcInit->stcTmr6_6.u32PwmLevel = EMB_DETECT_TMR6_6_PWM_BOTH_LOW;
        pstcInit->stcTmr6_7.u32PwmSel = EMB_TMR6_7_PWM_DISABLE;
        pstcInit->stcTmr6_7.u32PwmLevel = EMB_DETECT_TMR6_7_PWM_BOTH_LOW;
        pstcInit->stcTmr6_8.u32PwmSel = EMB_TMR6_8_PWM_DISABLE;
        pstcInit->stcTmr6_8.u32PwmLevel = EMB_DETECT_TMR6_8_PWM_BOTH_LOW;
        enRet = Ok;
    }

    return enRet;
}

/**
 * @brief  De-Initialize EMB function
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 0 instance register base
 *           @arg M4_EMB1:              EMB group 1 instance register base
 *           @arg M4_EMB2:              EMB group 2 instance register base
 *           @arg M4_EMB3:              EMB group 3 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @retval None
 */
void EMB_DeInit(M4_EMB_TypeDef *EMBx)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB(EMBx));

    /* Configures the registers to reset value. */
    WRITE_REG32(EMBx->SOE, 0x00UL);
    WRITE_REG32(EMBx->RLSSEL, 0x00UL);
    WRITE_REG32(EMBx->INTEN, 0x00UL);
    WRITE_REG32(EMBx->STATCLR, (EMB_STATCLR_PWMSFCLR | \
                                EMB_STATCLR_CMPFCLR | \
                                EMB_STATCLR_OSFCLR | \
                                EMB_STATCLR_PORTINFCLR1 | \
                                EMB_STATCLR_PORTINFCLR2 | \
                                EMB_STATCLR_PORTINFCLR3 | \
                                EMB_STATCLR_PORTINFCLR4));
}

/**
 * @brief  Set the EMB interrupt function
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 0 instance register base
 *           @arg M4_EMB1:              EMB group 1 instance register base
 *           @arg M4_EMB2:              EMB group 2 instance register base
 *           @arg M4_EMB3:              EMB group 3 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] u32IntSource            EMB interrupt source
 *         This parameter can be one of the following values:
 *           @arg EMB_INT_PWMS:         PWM same phase event interrupt
 *           @arg EMB_INT_CMP:          CMP result event interrupt
 *           @arg EMB_INT_OSC:          OSC stop event interrupt
 *           @arg EMB_INT_PORT1:        Port1 input event interrupt
 *           @arg EMB_INT_PORT2:        Port2 input event interrupt
 *           @arg EMB_INT_PORT3:        Port3 input event interrupt
 *           @arg EMB_INT_PORT4:        Port4 input event interrupt
 * @param  [in] enNewState              The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void EMB_IntCmd(M4_EMB_TypeDef *EMBx,
                    uint32_t u32IntSource,
                    en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB(EMBx));
    DDL_ASSERT(IS_VALID_EMB_INT(u32IntSource));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (Enable == enNewState)
    {
        SET_REG32_BIT(EMBx->INTEN, u32IntSource);
    }
    else
    {
        CLEAR_REG32_BIT(EMBx->INTEN, u32IntSource);
    }
}

/**
 * @brief  Set EMB release PWM mode
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 0 instance register base
 *           @arg M4_EMB1:              EMB group 1 instance register base
 *           @arg M4_EMB2:              EMB group 2 instance register base
 *           @arg M4_EMB3:              EMB group 3 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] u32Event                Monitor event
 *         This parameter can be any composed value of the following values:
 *           @arg EMB_EVENT_PWMS:       PWM same phase event
 *           @arg EMB_EVENT_CMP:        CMP result event
 *           @arg EMB_EVENT_OSC:        OSC stop event
 *           @arg EMB_EVENT_PORT1:      Port1 input event
 *           @arg EMB_EVENT_PORT2:      Port2 input event
 *           @arg EMB_EVENT_PORT3:      Port3 input event
 *           @arg EMB_EVENT_PORT4:      Port4 input event
 * @param  [in] u32Mode                 Release mode
 *         This parameter can be one of the following values:
 *           @arg EMB_RELEASE_PWM_SEL_FLAG_ZERO: Release PWM when flag bit is zero
 *           @arg EMB_RELEASE_PWM_SEL_STATE_ZERO: Release PWM when state bit is zero
 * @retval None
 */
void EMB_SetReleasePwmMode(M4_EMB_TypeDef *EMBx,
                                uint32_t u32Event,
                                uint32_t u32Mode)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB(EMBx));
    DDL_ASSERT(IS_VALID_EMB_MONITOR_EVENT(u32Event));
    DDL_ASSERT(IS_VALID_EMB_RELEASE_PWM_SEL(u32Mode));

    if (EMB_RELEASE_PWM_SEL_FLAG_ZERO == u32Mode)
    {
        CLEAR_REG32_BIT(EMBx->RLSSEL, u32Event);
    }
    else
    {
        SET_REG32_BIT(EMBx->RLSSEL, u32Event);
    }
}

/**
 * @brief  Get EMB status
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 0 instance register base
 *           @arg M4_EMB1:              EMB group 1 instance register base
 *           @arg M4_EMB2:              EMB group 2 instance register base
 *           @arg M4_EMB3:              EMB group 3 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] u32Flag                 EMB flag
 *         This parameter can be one of the following values:
 *           @arg EMB_FLAG_PWMS: PWM same phase trigger stop PWM
 *           @arg EMB_FLAG_CMP: CMP trigger stop PWM
 *           @arg EMB_FLAG_OSC: OSC trigger stop PWM
 *           @arg EMB_FLAG_PORT1: EMB Port1 input trigger stop PWM
 *           @arg EMB_FLAG_PORT2: EMB Port2 input trigger stop PWM
 *           @arg EMB_FLAG_PORT3: EMB Port3 input trigger stop PWM
 *           @arg EMB_FLAG_PORT4: EMB Port4 input trigger stop PWM
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t EMB_GetFlag(const M4_EMB_TypeDef *EMBx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB(EMBx));
    DDL_ASSERT(IS_VALID_EMB_FLAG(u32Flag));

    return READ_REG32_BIT(EMBx->STAT, u32Flag) ? Set : Reset;
}

/**
 * @brief  Get EMB status
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 0 instance register base
 *           @arg M4_EMB1:              EMB group 1 instance register base
 *           @arg M4_EMB2:              EMB group 2 instance register base
 *           @arg M4_EMB3:              EMB group 3 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] u32Flag                 EMB flag
 *         This parameter can be one of the following values:
 *           @arg EMB_FLAG_PWMS: PWM same phase trigger stop PWM
 *           @arg EMB_FLAG_CMP: CMP trigger stop PWM
 *           @arg EMB_FLAG_OSC: OSC trigger stop PWM
 *           @arg EMB_FLAG_PORT1: EMB Port1 input trigger stop PWM
 *           @arg EMB_FLAG_PORT2: EMB Port2 input trigger stop PWM
 *           @arg EMB_FLAG_PORT3: EMB Port3 input trigger stop PWM
 *           @arg EMB_FLAG_PORT4: EMB Port4 input trigger stop PWM
 * @retval None
 */
void EMB_ClearFlag(M4_EMB_TypeDef *EMBx, uint32_t u32Flag)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB(EMBx));
    DDL_ASSERT(IS_VALID_EMB_FLAG(u32Flag));

    SET_REG32_BIT(EMBx->STATCLR, u32Flag);
}

/**
 * @brief  Get EMB status
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 0 instance register base
 *           @arg M4_EMB1:              EMB group 1 instance register base
 *           @arg M4_EMB2:              EMB group 2 instance register base
 *           @arg M4_EMB3:              EMB group 3 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] u32Status               EMB state
 *         This parameter can be one of the following values:
 *           @arg EMB_STATE_PWMS: PWM same phase occur
 *           @arg EMB_STATE_CMP: CMP comapre event occur
 *           @arg EMB_STATE_OSC: OSC stop event occur
 *           @arg EMB_STATE_PORT1: EMB Port1 input control state
 *           @arg EMB_STATE_PORT2: EMB Port2 input control state
 *           @arg EMB_STATE_PORT3: EMB Port3 input control state
 *           @arg EMB_STATE_PORT4: EMB Port4 input control state
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t EMB_GetStatus(const M4_EMB_TypeDef *EMBx,
                                    uint32_t u32Status)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB(EMBx));
    DDL_ASSERT(IS_VALID_EMB_STATUS(u32Status));

    return READ_REG32_BIT(EMBx->STAT, u32Status) ? Set : Reset;
}

/**
 * @brief  Start/stop EMB software brake
 * @param  [in] EMBx                    Pointer to EMB instance register base
 *         This parameter can be one of the following values:
 *           @arg M4_EMB0:              EMB group 0 instance register base
 *           @arg M4_EMB1:              EMB group 1 instance register base
 *           @arg M4_EMB2:              EMB group 2 instance register base
 *           @arg M4_EMB3:              EMB group 3 instance register base
 *           @arg M4_EMB4:              EMB group 4 instance register base
 *           @arg M4_EMB5:              EMB group 5 instance register base
 *           @arg M4_EMB6:              EMB group 6 instance register base
 * @param  [in] enNewState              The function new state
 *           @arg  This parameter can be: Enable or Disable
 * @retval None
 */
void EMB_SwBrake(M4_EMB_TypeDef *EMBx, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_VALID_EMB(EMBx));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(EMBx->SOE, enNewState);
}

/**
 * @}
 */

#endif /* DDL_EMB_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
