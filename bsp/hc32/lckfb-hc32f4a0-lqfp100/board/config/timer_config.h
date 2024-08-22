/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-06-21     CDT               first version
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

#ifdef BSP_USING_TMRA_6
#ifndef TMRA_6_CONFIG
#define TMRA_6_CONFIG                                       \
    {                                                       \
       .tmr_handle      = CM_TMRA_6,                        \
       .clock_source    = CLK_BUS_PCLK1,                    \
       .clock           = FCG2_PERIPH_TMRA_6,               \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_6_OVF,               \
            .enIRQn     = BSP_USING_TMRA_6_IRQ_NUM,         \
            .u8Int_Prio = BSP_USING_TMRA_6_IRQ_PRIO,        \
       },                                                   \
       .name            = "tmra_6"                          \
    }
#endif /* TMRA_6_CONFIG */
#endif /* BSP_USING_TMRA_6 */

#ifdef BSP_USING_TMRA_7
#ifndef TMRA_7_CONFIG
#define TMRA_7_CONFIG                                       \
    {                                                       \
       .tmr_handle      = CM_TMRA_7,                        \
       .clock_source    = CLK_BUS_PCLK1,                    \
       .clock           = FCG2_PERIPH_TMRA_7,               \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_7_OVF,               \
            .enIRQn     = BSP_USING_TMRA_7_IRQ_NUM,         \
            .u8Int_Prio = BSP_USING_TMRA_7_IRQ_PRIO,        \
       },                                                   \
       .name            = "tmra_7"                          \
    }
#endif /* TMRA_7_CONFIG */
#endif /* BSP_USING_TMRA_7 */

#ifdef BSP_USING_TMRA_8
#ifndef TMRA_8_CONFIG
#define TMRA_8_CONFIG                                       \
    {                                                       \
       .tmr_handle      = CM_TMRA_8,                        \
       .clock_source    = CLK_BUS_PCLK1,                    \
       .clock           = FCG2_PERIPH_TMRA_8,               \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_8_OVF,               \
            .enIRQn     = BSP_USING_TMRA_8_IRQ_NUM,         \
            .u8Int_Prio = BSP_USING_TMRA_8_IRQ_PRIO,        \
       },                                                   \
       .name            = "tmra_8"                          \
    }
#endif /* TMRA_8_CONFIG */
#endif /* BSP_USING_TMRA_8 */

#ifdef BSP_USING_TMRA_9
#ifndef TMRA_9_CONFIG
#define TMRA_9_CONFIG                                       \
    {                                                       \
       .tmr_handle      = CM_TMRA_9,                        \
       .clock_source    = CLK_BUS_PCLK1,                    \
       .clock           = FCG2_PERIPH_TMRA_9,               \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_9_OVF,               \
            .enIRQn     = BSP_USING_TMRA_9_IRQ_NUM,         \
            .u8Int_Prio = BSP_USING_TMRA_9_IRQ_PRIO,        \
       },                                                   \
       .name            = "tmra_9"                          \
    }
#endif /* TMRA_9_CONFIG */
#endif /* BSP_USING_TMRA_9 */

#ifdef BSP_USING_TMRA_10
#ifndef TMRA_10_CONFIG
#define TMRA_10_CONFIG                                      \
    {                                                       \
       .tmr_handle      = CM_TMRA_10,                       \
       .clock_source    = CLK_BUS_PCLK1,                    \
       .clock           = FCG2_PERIPH_TMRA_10,              \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_10_OVF,              \
            .enIRQn     = BSP_USING_TMRA_10_IRQ_NUM,        \
            .u8Int_Prio = BSP_USING_TMRA_10_IRQ_PRIO,       \
       },                                                   \
       .name            = "tmra_10"                         \
    }
#endif /* TMRA_10_CONFIG */
#endif /* BSP_USING_TMRA_10 */

#ifdef BSP_USING_TMRA_11
#ifndef TMRA_11_CONFIG
#define TMRA_11_CONFIG                                      \
    {                                                       \
       .tmr_handle      = CM_TMRA_11,                       \
       .clock_source    = CLK_BUS_PCLK1,                    \
       .clock           = FCG2_PERIPH_TMRA_11,              \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_11_OVF,              \
            .enIRQn     = BSP_USING_TMRA_11_IRQ_NUM,        \
            .u8Int_Prio = BSP_USING_TMRA_11_IRQ_PRIO,       \
       },                                                   \
       .name            = "tmra_11"                         \
    }
#endif /* TMRA_11_CONFIG */
#endif /* BSP_USING_TMRA_11 */

#ifdef BSP_USING_TMRA_12
#ifndef TMRA_12_CONFIG
#define TMRA_12_CONFIG                                      \
    {                                                       \
       .tmr_handle      = CM_TMRA_12,                       \
       .clock_source    = CLK_BUS_PCLK1,                    \
       .clock           = FCG2_PERIPH_TMRA_12,              \
       .flag            = TMRA_FLAG_OVF,                    \
       .isr             =                                   \
       {                                                    \
            .enIntSrc   = INT_SRC_TMRA_12_OVF,              \
            .enIRQn     = BSP_USING_TMRA_12_IRQ_NUM,        \
            .u8Int_Prio = BSP_USING_TMRA_12_IRQ_PRIO,       \
       },                                                   \
       .name            = "tmra_12"                         \
    }
#endif /* TMRA_12_CONFIG */
#endif /* BSP_USING_TMRA_12 */
#endif /* __TMR_CONFIG_H__ */
