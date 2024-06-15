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

#ifndef __TMR_CONFIG_H__
#define __TMR_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_TMRA_1
#ifndef TMRA_1_CONFIG
#define TMRA_1_CONFIG                                       \
    {                                                       \
       .tmr_handle      = CM_TMRA_1,                        \
       .clock_source    = CLK_BUS_PCLK0,                    \
       .clock           = FCG2_PERIPH_TMRA_1,               \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_1_OVF,               \
            .enIRQn     = BSP_USING_TMRA_1_IRQ_NUM,         \
            .u8Int_Prio = BSP_USING_TMRA_1_IRQ_PRIO,        \
       },                                                   \
       .name            = "tmra_1"                          \
    }
#endif /* TMRA_1_CONFIG */
#endif /* BSP_USING_TMRA_1 */

#ifdef BSP_USING_TMRA_2
#ifndef TMRA_2_CONFIG
#define TMRA_2_CONFIG                                       \
    {                                                       \
       .tmr_handle      = CM_TMRA_2,                        \
       .clock_source    = CLK_BUS_PCLK0,                    \
       .clock           = FCG2_PERIPH_TMRA_2,               \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_2_OVF,               \
            .enIRQn     = BSP_USING_TMRA_2_IRQ_NUM,         \
            .u8Int_Prio = BSP_USING_TMRA_2_IRQ_PRIO,        \
       },                                                   \
       .name            = "tmra_2"                          \
    }
#endif /* TMRA_2_CONFIG */
#endif /* BSP_USING_TMRA_2 */

#ifdef BSP_USING_TMRA_3
#ifndef TMRA_3_CONFIG
#define TMRA_3_CONFIG                                       \
    {                                                       \
       .tmr_handle      = CM_TMRA_3,                        \
       .clock_source    = CLK_BUS_PCLK0,                    \
       .clock           = FCG2_PERIPH_TMRA_3,               \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_3_OVF,               \
            .enIRQn     = BSP_USING_TMRA_3_IRQ_NUM,         \
            .u8Int_Prio = BSP_USING_TMRA_3_IRQ_PRIO,        \
       },                                                   \
       .name            = "tmra_3"                          \
    }
#endif /* TMRA_3_CONFIG */
#endif /* BSP_USING_TMRA_3 */

#ifdef BSP_USING_TMRA_4
#ifndef TMRA_4_CONFIG
#define TMRA_4_CONFIG                                       \
    {                                                       \
       .tmr_handle      = CM_TMRA_4,                        \
       .clock_source    = CLK_BUS_PCLK0,                    \
       .clock           = FCG2_PERIPH_TMRA_4,               \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_4_OVF,               \
            .enIRQn     = BSP_USING_TMRA_4_IRQ_NUM,         \
            .u8Int_Prio = BSP_USING_TMRA_4_IRQ_PRIO,        \
       },                                                   \
       .name            = "tmra_4"                          \
    }
#endif /* TMRA_4_CONFIG */
#endif /* BSP_USING_TMRA_4 */

#ifdef BSP_USING_TMRA_5
#ifndef TMRA_5_CONFIG
#define TMRA_5_CONFIG                                       \
    {                                                       \
       .tmr_handle      = CM_TMRA_5,                        \
       .clock_source    = CLK_BUS_PCLK1,                    \
       .clock           = FCG2_PERIPH_TMRA_5,               \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_5_OVF,               \
            .enIRQn     = BSP_USING_TMRA_5_IRQ_NUM,         \
            .u8Int_Prio = BSP_USING_TMRA_5_IRQ_PRIO,        \
       },                                                   \
       .name            = "tmra_5"                          \
    }
#endif /* TMRA_5_CONFIG */
#endif /* BSP_USING_TMRA_5 */
#endif /* __TMR_CONFIG_H__ */
