/*
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __GPIO_CONFIG_H__
#define __GPIO_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif


#if defined(RT_USING_PIN)

#ifndef EXTINT0_IRQ_CONFIG
#define EXTINT0_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT022_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ0,                   \
    }
#endif /* EXTINT1_IRQ_CONFIG */

#ifndef EXTINT1_IRQ_CONFIG
#define EXTINT1_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT023_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ1,                   \
    }
#endif /* EXTINT1_IRQ_CONFIG */

#ifndef EXTINT2_IRQ_CONFIG
#define EXTINT2_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT024_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ2,                   \
    }
#endif /* EXTINT2_IRQ_CONFIG */

#ifndef EXTINT3_IRQ_CONFIG
#define EXTINT3_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT025_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ3,                   \
    }
#endif /* EXTINT3_IRQ_CONFIG */

#ifndef EXTINT4_IRQ_CONFIG
#define EXTINT4_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT026_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ4,                   \
    }
#endif /* EXTINT4_IRQ_CONFIG */

#ifndef EXTINT5_IRQ_CONFIG
#define EXTINT5_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT027_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ5,                   \
    }
#endif /* EXTINT5_IRQ_CONFIG */

#ifndef EXTINT6_IRQ_CONFIG
#define EXTINT6_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT028_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ6,                   \
    }
#endif /* EXTINT6_IRQ_CONFIG */

#ifndef EXTINT7_IRQ_CONFIG
#define EXTINT7_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT029_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ7,                   \
    }
#endif /* EXTINT7_IRQ_CONFIG */

#ifndef EXTINT8_IRQ_CONFIG
#define EXTINT8_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT030_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ8,                   \
    }
#endif /* EXTINT8_IRQ_CONFIG */

#ifndef EXTINT9_IRQ_CONFIG
#define EXTINT9_IRQ_CONFIG                                  \
    {                                                       \
        .irq_num    = INT031_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ9,                   \
    }
#endif /* EXTINT9_IRQ_CONFIG */

#ifndef EXTINT10_IRQ_CONFIG
#define EXTINT10_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = INT032_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ10,                  \
    }
#endif /* EXTINT10_IRQ_CONFIG */

#ifndef EXTINT11_IRQ_CONFIG
#define EXTINT11_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = INT033_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ11,                  \
    }
#endif /* EXTINT11_IRQ_CONFIG */

#ifndef EXTINT12_IRQ_CONFIG
#define EXTINT12_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = INT034_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ12,                  \
    }
#endif /* EXTINT12_IRQ_CONFIG */

#ifndef EXTINT13_IRQ_CONFIG
#define EXTINT13_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = INT035_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ13,                  \
    }
#endif /* EXTINT13_IRQ_CONFIG */

#ifndef EXTINT14_IRQ_CONFIG
#define EXTINT14_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = INT036_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ14,                  \
    }
#endif /* EXTINT14_IRQ_CONFIG */

#ifndef EXTINT15_IRQ_CONFIG
#define EXTINT15_IRQ_CONFIG                                 \
    {                                                       \
        .irq_num    = INT037_IRQn,                          \
        .irq_prio   = DDL_IRQ_PRIO_DEFAULT,                 \
        .int_src    = INT_SRC_PORT_EIRQ15,                  \
    }
#endif /* EXTINT15_IRQ_CONFIG */

#endif


#ifdef __cplusplus
}
#endif

#endif /* __GPIO_CONFIG_H__ */
