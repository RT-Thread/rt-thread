/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#ifndef __PULSE_ENCODER_CONFIG_H__
#define __PULSE_ENCODER_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(RT_USING_PULSE_ENCODER)

#ifdef BSP_USING_PULSE_ENCODER_TMRA_1
#ifndef PULSE_ENCODER_TMRA_1_CONFIG
#define PULSE_ENCODER_TMRA_1_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMRA_1,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMRA_1,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u16CountUpCond     = TMRA_CNT_UP_COND_CLKA_HIGH_CLKB_RISING,       \
            .u16CountDownCond   = TMRA_CNT_DOWN_COND_CLKB_HIGH_CLKA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMRA_1_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMRA_1_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMRA_1_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMRA_1_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMRA_1_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMRA_1_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue      = 1000UL,                                           \
       .name                = "pulse_a1"                                        \
    }
#endif /* PULSE_ENCODER_TMRA_1_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMRA_1 */

#ifdef BSP_USING_PULSE_ENCODER_TMRA_2
#ifndef PULSE_ENCODER_TMRA_2_CONFIG
#define PULSE_ENCODER_TMRA_2_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMRA_2,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMRA_2,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u16CountUpCond     = TMRA_CNT_UP_COND_CLKA_HIGH_CLKB_RISING,       \
            .u16CountDownCond   = TMRA_CNT_DOWN_COND_CLKB_HIGH_CLKA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMRA_2_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMRA_2_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMRA_2_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMRA_2_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMRA_2_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMRA_2_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_a2"                                            \
    }
#endif /* PULSE_ENCODER_TMRA_2_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMRA_2 */

#ifdef BSP_USING_PULSE_ENCODER_TMRA_3
#ifndef PULSE_ENCODER_TMRA_3_CONFIG
#define PULSE_ENCODER_TMRA_3_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMRA_3,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMRA_3,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u16CountUpCond     = TMRA_CNT_UP_COND_CLKA_HIGH_CLKB_RISING,       \
            .u16CountDownCond   = TMRA_CNT_DOWN_COND_CLKB_HIGH_CLKA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMRA_3_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMRA_3_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMRA_3_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMRA_3_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMRA_3_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMRA_3_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_a3"                                            \
    }
#endif /* PULSE_ENCODER_TMRA_3_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMRA_3 */

#ifdef BSP_USING_PULSE_ENCODER_TMRA_4
#ifndef PULSE_ENCODER_TMRA_4_CONFIG
#define PULSE_ENCODER_TMRA_4_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMRA_4,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMRA_4,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u16CountUpCond     = TMRA_CNT_UP_COND_CLKA_HIGH_CLKB_RISING,       \
            .u16CountDownCond   = TMRA_CNT_DOWN_COND_CLKB_HIGH_CLKA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMRA_4_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMRA_4_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMRA_4_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMRA_4_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMRA_4_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMRA_4_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_a4"                                            \
    }
#endif /* PULSE_ENCODER_TMRA_4_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMRA_4 */

#ifdef BSP_USING_PULSE_ENCODER_TMRA_5
#ifndef PULSE_ENCODER_TMRA_5_CONFIG
#define PULSE_ENCODER_TMRA_5_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMRA_5,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMRA_5,                                   \
       .hw_count =                                                              \
        {                                                                       \
            .u16CountUpCond     = TMRA_CNT_UP_COND_CLKA_HIGH_CLKB_RISING,       \
            .u16CountDownCond   = TMRA_CNT_DOWN_COND_CLKB_HIGH_CLKA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMRA_5_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMRA_5_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMRA_5_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMRA_5_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMRA_5_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMRA_5_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_a5"                                            \
    }
#endif /* PULSE_ENCODER_TMRA_5_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMRA_5 */

#ifdef BSP_USING_PULSE_ENCODER_TMRA_6
#ifndef PULSE_ENCODER_TMRA_6_CONFIG
#define PULSE_ENCODER_TMRA_6_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMRA_6,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMRA_6,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u16CountUpCond     = TMRA_CNT_UP_COND_CLKA_HIGH_CLKB_RISING,       \
            .u16CountDownCond   = TMRA_CNT_DOWN_COND_CLKB_HIGH_CLKA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMRA_6_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMRA_6_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMRA_6_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMRA_6_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMRA_6_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMRA_6_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_a6"                                            \
    }
#endif /* PULSE_ENCODER_TMRA_6_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMRA_6 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_1
#ifndef PULSE_ENCODER_TMR6_1_CONFIG
#define PULSE_ENCODER_TMR6_1_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMR6_1,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_1,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_1_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_1_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_1_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMR6_1_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_1_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_1_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_61"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_1_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_1 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_2
#ifndef PULSE_ENCODER_TMR6_2_CONFIG
#define PULSE_ENCODER_TMR6_2_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMR6_2,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_2,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_2_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_2_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_2_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMR6_2_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_2_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_2_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_62"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_2_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_2 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_3
#ifndef PULSE_ENCODER_TMR6_3_CONFIG
#define PULSE_ENCODER_TMR6_3_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMR6_3,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_3,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_3_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_3_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_3_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMR6_3_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_3_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_3_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_63"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_3_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_3 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_4
#ifndef PULSE_ENCODER_TMR6_4_CONFIG
#define PULSE_ENCODER_TMR6_4_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMR6_4,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_4,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_4_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_4_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_4_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMR6_4_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_4_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_4_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_64"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_4_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_4 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_5
#ifndef PULSE_ENCODER_TMR6_5_CONFIG
#define PULSE_ENCODER_TMR6_5_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMR6_5,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_5,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_5_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_5_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_5_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMR6_5_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_5_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_5_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_65"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_5_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_5 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_6
#ifndef PULSE_ENCODER_TMR6_6_CONFIG
#define PULSE_ENCODER_TMR6_6_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMR6_6,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_6,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_6_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_6_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_6_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMR6_6_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_6_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_6_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_66"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_6_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_6 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_7
#ifndef PULSE_ENCODER_TMR6_7_CONFIG
#define PULSE_ENCODER_TMR6_7_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMR6_7,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_7,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_7_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_7_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_7_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMR6_7_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_7_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_7_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_67"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_7_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_7 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_8
#ifndef PULSE_ENCODER_TMR6_8_CONFIG
#define PULSE_ENCODER_TMR6_8_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMR6_8,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_8,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_8_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_8_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_8_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMR6_8_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_8_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_8_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_68"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_8_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_8 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_9
#ifndef PULSE_ENCODER_TMR6_9_CONFIG
#define PULSE_ENCODER_TMR6_9_CONFIG                                             \
    {                                                                           \
       .tmr_handler     = CM_TMR6_9,                                            \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_9,                                   \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_9_OVF,                               \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_9_OVF_IRQ_NUM,             \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_9_OVF_IRQ_PRIO,            \
            .enIntSrc_Udf   = INT_SRC_TMR6_9_UDF,                               \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_9_UDF_IRQ_NUM,             \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_9_UDF_IRQ_PRIO,            \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_69"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_9_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_9 */

#ifdef BSP_USING_PULSE_ENCODER_TMR6_10
#ifndef PULSE_ENCODER_TMR6_10_CONFIG
#define PULSE_ENCODER_TMR6_10_CONFIG                                            \
    {                                                                           \
       .tmr_handler     = CM_TMR6_10,                                           \
       .u32PeriphClock  = FCG2_PERIPH_TMR6_10,                                  \
       .hw_count =                                                              \
       {                                                                        \
            .u32CountUpCond     = TMR6_CNT_UP_COND_PWMA_HIGH_PWMB_RISING,       \
            .u32CountDownCond   = TMR6_CNT_DOWN_COND_PWMB_HIGH_PWMA_RISING,     \
       },                                                                       \
       .isr =                                                                   \
       {                                                                        \
            .enIntSrc_Ovf   = INT_SRC_TMR6_10_OVF,                              \
            .enIRQn_Ovf     = BSP_PULSE_ENCODER_TMR6_10_OVF_IRQ_NUM,            \
            .u8Int_Prio_Ovf = BSP_PULSE_ENCODER_TMR6_10_OVF_IRQ_PRIO,           \
            .enIntSrc_Udf   = INT_SRC_TMR6_10_UDF,                              \
            .enIRQn_Udf     = BSP_PULSE_ENCODER_TMR6_10_UDF_IRQ_NUM,            \
            .u8Int_Prio_Udf = BSP_PULSE_ENCODER_TMR6_10_UDF_IRQ_PRIO,           \
       },                                                                       \
       .u32PeriodValue  = 1000UL,                                               \
       .name            = "pulse_6a"                                            \
    }
#endif /* PULSE_ENCODER_TMR6_10_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER_TMR6_10 */

#endif /* RT_USING_PULSE_ENCODER */

#endif /* __PULSE_ENCODER_CONFIG_H__ */
