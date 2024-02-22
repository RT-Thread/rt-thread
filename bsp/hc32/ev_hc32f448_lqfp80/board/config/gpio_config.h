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

#ifndef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif


#if defined(RT_USING_PIN)

#ifndef EXTINT0_IRQ_CONFIG
#define EXTINT0_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT0_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT0_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ0,                   \
    }
#endif /* EXTINT1_IRQ_CONFIG */

#ifndef EXTINT1_IRQ_CONFIG
#define EXTINT1_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT1_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT1_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ1,                   \
    }
#endif /* EXTINT1_IRQ_CONFIG */

#ifndef EXTINT2_IRQ_CONFIG
#define EXTINT2_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT2_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT2_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ2,                   \
    }
#endif /* EXTINT2_IRQ_CONFIG */

#ifndef EXTINT3_IRQ_CONFIG
#define EXTINT3_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT3_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT3_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ3,                   \
    }
#endif /* EXTINT3_IRQ_CONFIG */

#ifndef EXTINT4_IRQ_CONFIG
#define EXTINT4_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT4_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT4_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ4,                   \
    }
#endif /* EXTINT4_IRQ_CONFIG */

#ifndef EXTINT5_IRQ_CONFIG
#define EXTINT5_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT5_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT5_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ5,                   \
    }
#endif /* EXTINT5_IRQ_CONFIG */

#ifndef EXTINT6_IRQ_CONFIG
#define EXTINT6_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT6_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT6_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ6,                   \
    }
#endif /* EXTINT6_IRQ_CONFIG */

#ifndef EXTINT7_IRQ_CONFIG
#define EXTINT7_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT7_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT7_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ7,                   \
    }
#endif /* EXTINT7_IRQ_CONFIG */

#ifndef EXTINT8_IRQ_CONFIG
#define EXTINT8_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT8_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT8_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ8,                   \
    }
#endif /* EXTINT8_IRQ_CONFIG */

#ifndef EXTINT9_IRQ_CONFIG
#define EXTINT9_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = BSP_EXTINT9_IRQ_NUM,                  \
        .irq_prio   = BSP_EXTINT9_IRQ_PRIO,                 \
        .int_src    = INT_SRC_PORT_EIRQ9,                   \
    }
#endif /* EXTINT9_IRQ_CONFIG */

#ifndef EXTINT10_IRQ_CONFIG
#define EXTINT10_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = BSP_EXTINT10_IRQ_NUM,                 \
        .irq_prio   = BSP_EXTINT10_IRQ_PRIO,                \
        .int_src    = INT_SRC_PORT_EIRQ10,                  \
    }
#endif /* EXTINT10_IRQ_CONFIG */

#ifndef EXTINT11_IRQ_CONFIG
#define EXTINT11_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = BSP_EXTINT11_IRQ_NUM,                 \
        .irq_prio   = BSP_EXTINT11_IRQ_PRIO,                \
        .int_src    = INT_SRC_PORT_EIRQ11,                  \
    }
#endif /* EXTINT11_IRQ_CONFIG */

#ifndef EXTINT12_IRQ_CONFIG
#define EXTINT12_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = BSP_EXTINT12_IRQ_NUM,                 \
        .irq_prio   = BSP_EXTINT12_IRQ_PRIO,                \
        .int_src    = INT_SRC_PORT_EIRQ12,                  \
    }
#endif /* EXTINT12_IRQ_CONFIG */

#ifndef EXTINT13_IRQ_CONFIG
#define EXTINT13_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = BSP_EXTINT13_IRQ_NUM,                 \
        .irq_prio   = BSP_EXTINT13_IRQ_PRIO,                \
        .int_src    = INT_SRC_PORT_EIRQ13,                  \
    }
#endif /* EXTINT13_IRQ_CONFIG */

#ifndef EXTINT14_IRQ_CONFIG
#define EXTINT14_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = BSP_EXTINT14_IRQ_NUM,                 \
        .irq_prio   = BSP_EXTINT14_IRQ_PRIO,                \
        .int_src    = INT_SRC_PORT_EIRQ14,                  \
    }
#endif /* EXTINT14_IRQ_CONFIG */

#ifndef EXTINT15_IRQ_CONFIG
#define EXTINT15_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = BSP_EXTINT15_IRQ_NUM,                 \
        .irq_prio   = BSP_EXTINT15_IRQ_PRIO,                \
        .int_src    = INT_SRC_PORT_EIRQ15,                  \
    }
#endif /* EXTINT15_IRQ_CONFIG */

#endif


#ifdef __cplusplus
}
#endif

#endif /* __GPIO_CONFIG_H__ */
