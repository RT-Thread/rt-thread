/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */

#ifndef __DRV_HWTIMER_H__
#define __DRV_HWTIMER_H__

#include <rtthread.h>
#include "board_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_TIMER1
#ifndef TIMER1_IRQ_CONFIG
#define TIMER1_IRQ_CONFIG                       \
    {                                           \
        .irq        = TIMER1_CNT_INT_IRQn,      \
        .irq_prio   = TIMER1_CNT_INT_PRIO,      \
    }
#endif /* TIMER1_IRQ_CONFIG */
#endif /* BSP_USING_TIMER1 */

#ifdef BSP_USING_TIMER2
#ifndef TIMER2_IRQ_CONFIG
#define TIMER2_IRQ_CONFIG                       \
    {                                           \
        .irq        = TIMER2_CNT_INT_IRQn,      \
        .irq_prio   = TIMER2_CNT_INT_PRIO,      \
    }
#endif /* TIMER2_IRQ_CONFIG */
#endif /* BSP_USING_TIMER2 */

#ifdef BSP_USING_TIMER3
#ifndef TIMER3_IRQ_CONFIG
#define TIMER3_IRQ_CONFIG                       \
    {                                           \
        .irq        = TIMER3_CNT_INT_IRQn,      \
        .irq_prio   = TIMER3_CNT_INT_PRIO,      \
    }
#endif /* TIMER3_IRQ_CONFIG */
#endif /* BSP_USING_TIMER3 */

#ifdef BSP_USING_TIMER4
#ifndef TIMER4_IRQ_CONFIG
#define TIMER4_IRQ_CONFIG                       \
    {                                           \
        .irq        = TIMER4_CNT_INT_IRQn,      \
        .irq_prio   = TIMER4_CNT_INT_PRIO,      \
    }
#endif /* TIMER4_IRQ_CONFIG */
#endif /* BSP_USING_TIMER4 */

#ifdef BSP_USING_TIMER5
#ifndef TIMER5_IRQ_CONFIG
#define TIMER5_IRQ_CONFIG                       \
    {                                           \
        .irq        = TIMER5_CNT_INT_IRQn,      \
        .irq_prio   = TIMER5_CNT_INT_PRIO,      \
    }
#endif /* TIMER5_IRQ_CONFIG */
#endif /* BSP_USING_TIMER5 */

#ifdef BSP_USING_TIMER6
#ifndef TIMER6_IRQ_CONFIG
#define TIMER6_IRQ_CONFIG                       \
    {                                           \
        .irq        = TIMER6_CNT_INT_IRQn,      \
        .irq_prio   = TIMER6_CNT_INT_PRIO,      \
    }
#endif /* TIMER6_IRQ_CONFIG */
#endif /* BSP_USING_TIMER6 */

#ifdef BSP_USING_TIMER7
#ifndef TIMER7_IRQ_CONFIG
#define TIMER7_IRQ_CONFIG                       \
    {                                           \
        .irq        = TIMER7_CNT_INT_IRQn,      \
        .irq_prio   = TIMER7_CNT_INT_PRIO,      \
    }
#endif /* TIMER7_IRQ_CONFIG */
#endif /* BSP_USING_TIMER7 */

#ifdef BSP_USING_TIMER8
#ifndef TIMER8_IRQ_CONFIG
#define TIMER8_IRQ_CONFIG                       \
    {                                           \
        .irq        = TIMER8_CNT_INT_IRQn,      \
        .irq_prio   = TIMER8_CNT_INT_PRIO,      \
    }
#endif /* TIMER8_IRQ_CONFIG */
#endif /* BSP_USING_TIMER8 */

#ifdef BSP_USING_TIMER9
#ifndef TIMER9_IRQ_CONFIG
#define TIMER9_IRQ_CONFIG                       \
    {                                           \
        .irq        = TIMER9_CNT_INT_IRQn,      \
        .irq_prio   = TIMER9_CNT_INT_PRIO,      \
    }
#endif /* TIMER9_IRQ_CONFIG */
#endif /* BSP_USING_TIMER9 */

#ifdef BSP_USING_TIMER10
#ifndef TIMER10_IRQ_CONFIG
#define TIMER10_IRQ_CONFIG                      \
    {                                           \
        .irq        = TIMER10_CNT_INT_IRQn,     \
        .irq_prio   = TIMER10_CNT_INT_PRIO,     \
    }
#endif /* TIMER10_IRQ_CONFIG */
#endif /* BSP_USING_TIMER10 */

#ifdef BSP_USING_TIMER11
#ifndef TIMER11_IRQ_CONFIG
#define TIMER11_IRQ_CONFIG                      \
    {                                           \
        .irq        = TIMER11_CNT_INT_IRQn,     \
        .irq_prio   = TIMER11_CNT_INT_PRIO,     \
    }
#endif /* TIMER11_IRQ_CONFIG */
#endif /* BSP_USING_TIMER11 */

#ifdef BSP_USING_TIMER12
#ifndef TIMER12_IRQ_CONFIG
#define TIMER12_IRQ_CONFIG                      \
    {                                           \
        .irq        = TIMER12_CNT_INT_IRQn,     \
        .irq_prio   = TIMER12_CNT_INT_PRIO,     \
    }
#endif /* TIMER12_IRQ_CONFIG */
#endif /* BSP_USING_TIMER12 */

#ifdef __cplusplus
}
#endif

#endif /* __DRV_HWTIMER_H__ */
