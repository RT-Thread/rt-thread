/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */

#ifndef __DRV_PULSE_ENCODER_H__
#define __DRV_PULSE_ENCODER_H__

#include <rtthread.h>
#include "board_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_PULSE_ENCODER1
#ifndef PULSE_ENCODER1_OVF_IRQ_CONFIG
#define PULSE_ENCODER1_OVF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER1_OVF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER1_OVF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER1_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER1_UDF_IRQ_CONFIG
#define PULSE_ENCODER1_UDF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER1_UNF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER1_UNF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER1_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER1 */

#ifdef BSP_USING_PULSE_ENCODER2
#ifndef PULSE_ENCODER2_OVF_IRQ_CONFIG
#define PULSE_ENCODER2_OVF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER2_OVF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER2_OVF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER2_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER2_UDF_IRQ_CONFIG
#define PULSE_ENCODER2_UDF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER2_UNF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER2_UNF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER2_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER2 */

#ifdef BSP_USING_PULSE_ENCODER3
#ifndef PULSE_ENCODER3_OVF_IRQ_CONFIG
#define PULSE_ENCODER3_OVF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER3_OVF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER3_OVF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER3_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER3_UDF_IRQ_CONFIG
#define PULSE_ENCODER3_UDF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER3_UNF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER3_UNF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER3_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER3 */

#ifdef BSP_USING_PULSE_ENCODER4
#ifndef PULSE_ENCODER4_OVF_IRQ_CONFIG
#define PULSE_ENCODER4_OVF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER4_OVF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER4_OVF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER4_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER4_UDF_IRQ_CONFIG
#define PULSE_ENCODER4_UDF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER4_UNF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER4_UNF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER4_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER4 */

#ifdef BSP_USING_PULSE_ENCODER5
#ifndef PULSE_ENCODER5_OVF_IRQ_CONFIG
#define PULSE_ENCODER5_OVF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER5_OVF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER5_OVF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER5_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER5_UDF_IRQ_CONFIG
#define PULSE_ENCODER5_UDF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER5_UNF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER5_UNF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER5_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER5 */

#ifdef BSP_USING_PULSE_ENCODER6
#ifndef PULSE_ENCODER6_OVF_IRQ_CONFIG
#define PULSE_ENCODER6_OVF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER6_OVF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER6_OVF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER6_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER6_UDF_IRQ_CONFIG
#define PULSE_ENCODER6_UDF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER6_UNF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER6_UNF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER6_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER6 */

#ifdef BSP_USING_PULSE_ENCODER7
#ifndef PULSE_ENCODER7_OVF_IRQ_CONFIG
#define PULSE_ENCODER7_OVF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER7_OVF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER7_OVF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER7_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER7_UDF_IRQ_CONFIG
#define PULSE_ENCODER7_UDF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER7_UNF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER7_UNF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER7_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER7 */

#ifdef BSP_USING_PULSE_ENCODER8
#ifndef PULSE_ENCODER8_OVF_IRQ_CONFIG
#define PULSE_ENCODER8_OVF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER8_OVF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER8_OVF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER8_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER8_UDF_IRQ_CONFIG
#define PULSE_ENCODER8_UDF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER8_UNF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER8_UNF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER8_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER8 */

#ifdef BSP_USING_PULSE_ENCODER9
#ifndef PULSE_ENCODER9_OVF_IRQ_CONFIG
#define PULSE_ENCODER9_OVF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER9_OVF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER9_OVF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER9_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER9_UDF_IRQ_CONFIG
#define PULSE_ENCODER9_UDF_IRQ_CONFIG                                          \
    {                                                                          \
        .irq        = PULSE_ENCODER9_UNF_INT_IRQn,                             \
        .irq_prio   = PULSE_ENCODER9_UNF_INT_PRIO,                             \
    }
#endif /* PULSE_ENCODER9_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER9 */

#ifdef BSP_USING_PULSE_ENCODER10
#ifndef PULSE_ENCODER10_OVF_IRQ_CONFIG
#define PULSE_ENCODER10_OVF_IRQ_CONFIG                                         \
    {                                                                          \
        .irq        = PULSE_ENCODER10_OVF_INT_IRQn,                            \
        .irq_prio   = PULSE_ENCODER10_OVF_INT_PRIO,                            \
    }
#endif /* PULSE_ENCODER10_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER10_UDF_IRQ_CONFIG
#define PULSE_ENCODER10_UDF_IRQ_CONFIG                                         \
    {                                                                          \
        .irq        = PULSE_ENCODER10_UNF_INT_IRQn,                            \
        .irq_prio   = PULSE_ENCODER10_UNF_INT_PRIO,                            \
    }
#endif /* PULSE_ENCODER10_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER10 */

#ifdef BSP_USING_PULSE_ENCODER11
#ifndef PULSE_ENCODER11_OVF_IRQ_CONFIG
#define PULSE_ENCODER11_OVF_IRQ_CONFIG                                         \
    {                                                                          \
        .irq        = PULSE_ENCODER11_OVF_INT_IRQn,                            \
        .irq_prio   = PULSE_ENCODER11_OVF_INT_PRIO,                            \
    }
#endif /* PULSE_ENCODER11_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER11_UDF_IRQ_CONFIG
#define PULSE_ENCODER11_UDF_IRQ_CONFIG                                         \
    {                                                                          \
        .irq        = PULSE_ENCODER11_UNF_INT_IRQn,                            \
        .irq_prio   = PULSE_ENCODER11_UNF_INT_PRIO,                            \
    }
#endif /* PULSE_ENCODER11_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER11 */

#ifdef BSP_USING_PULSE_ENCODER12
#ifndef PULSE_ENCODER12_OVF_IRQ_CONFIG
#define PULSE_ENCODER12_OVF_IRQ_CONFIG                                         \
    {                                                                          \
        .irq        = PULSE_ENCODER12_OVF_INT_IRQn,                            \
        .irq_prio   = PULSE_ENCODER12_OVF_INT_PRIO,                            \
    }
#endif /* PULSE_ENCODER12_OVF_IRQ_CONFIG */

#ifndef PULSE_ENCODER12_UDF_IRQ_CONFIG
#define PULSE_ENCODER12_UDF_IRQ_CONFIG                                         \
    {                                                                          \
        .irq        = PULSE_ENCODER12_UNF_INT_IRQn,                            \
        .irq_prio   = PULSE_ENCODER12_UNF_INT_PRIO,                            \
    }
#endif /* PULSE_ENCODER12_UDF_IRQ_CONFIG */
#endif /* BSP_USING_PULSE_ENCODER12 */

#ifdef __cplusplus
}
#endif

#endif /* __DRV_PULSE_ENCODER_H__ */
