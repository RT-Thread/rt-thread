/*
 * Copyright (C) 2021, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-19     pjq          first version
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include <rtdevice.h>

#ifdef RT_USING_PIN

#define __HC_PORT(port)                 GpioPort##port
#define GET_PIN(PORT, PIN)              (((rt_uint16_t)__HC_PORT(PORT) / 0x40 * 16) + PIN)

#ifndef EXINT0_IRQ_CONFIG
#define EXINT0_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT0_INT_IRQn,          \
        .irq_prio   = EXINT0_INT_PRIO,          \
    }
#endif /* EXINT1_IRQ_CONFIG */

#ifndef EXINT1_IRQ_CONFIG
#define EXINT1_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT1_INT_IRQn,          \
        .irq_prio   = EXINT1_INT_PRIO,          \
    }
#endif /* EXINT1_IRQ_CONFIG */

#ifndef EXINT2_IRQ_CONFIG
#define EXINT2_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT2_INT_IRQn,          \
        .irq_prio   = EXINT2_INT_PRIO,          \
    }
#endif /* EXINT2_IRQ_CONFIG */

#ifndef EXINT3_IRQ_CONFIG
#define EXINT3_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT3_INT_IRQn,          \
        .irq_prio   = EXINT3_INT_PRIO,          \
    }
#endif /* EXINT3_IRQ_CONFIG */

#ifndef EXINT4_IRQ_CONFIG
#define EXINT4_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT4_INT_IRQn,          \
        .irq_prio   = EXINT4_INT_PRIO,          \
    }
#endif /* EXINT4_IRQ_CONFIG */

#ifndef EXINT5_IRQ_CONFIG
#define EXINT5_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT5_INT_IRQn,          \
        .irq_prio   = EXINT5_INT_PRIO,          \
    }
#endif /* EXINT5_IRQ_CONFIG */

#ifndef EXINT6_IRQ_CONFIG
#define EXINT6_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT6_INT_IRQn,          \
        .irq_prio   = EXINT6_INT_PRIO,          \
    }
#endif /* EXINT6_IRQ_CONFIG */

#ifndef EXINT7_IRQ_CONFIG
#define EXINT7_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT7_INT_IRQn,          \
        .irq_prio   = EXINT7_INT_PRIO,          \
    }
#endif /* EXINT7_IRQ_CONFIG */

#ifndef EXINT8_IRQ_CONFIG
#define EXINT8_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT8_INT_IRQn,          \
        .irq_prio   = EXINT8_INT_PRIO,          \
    }
#endif /* EXINT8_IRQ_CONFIG */

#ifndef EXINT9_IRQ_CONFIG
#define EXINT9_IRQ_CONFIG                       \
    {                                           \
        .irq        = EXINT9_INT_IRQn,          \
        .irq_prio   = EXINT9_INT_PRIO,          \
    }
#endif /* EXINT9_IRQ_CONFIG */

#ifndef EXINT10_IRQ_CONFIG
#define EXINT10_IRQ_CONFIG                      \
    {                                           \
        .irq        = EXINT10_INT_IRQn,         \
        .irq_prio   = EXINT10_INT_PRIO,         \
    }
#endif /* EXINT10_IRQ_CONFIG */

#ifndef EXINT11_IRQ_CONFIG
#define EXINT11_IRQ_CONFIG                      \
    {                                           \
        .irq        = EXINT11_INT_IRQn,         \
        .irq_prio   = EXINT11_INT_PRIO,         \
    }
#endif /* EXINT11_IRQ_CONFIG */

#ifndef EXINT12_IRQ_CONFIG
#define EXINT12_IRQ_CONFIG                      \
    {                                           \
        .irq        = EXINT12_INT_IRQn,         \
        .irq_prio   = EXINT12_INT_PRIO,         \
    }
#endif /* EXINT12_IRQ_CONFIG */

#ifndef EXINT13_IRQ_CONFIG
#define EXINT13_IRQ_CONFIG                      \
    {                                           \
        .irq        = EXINT13_INT_IRQn,         \
        .irq_prio   = EXINT13_INT_PRIO,         \
    }
#endif /* EXINT13_IRQ_CONFIG */

#ifndef EXINT14_IRQ_CONFIG
#define EXINT14_IRQ_CONFIG                      \
    {                                           \
        .irq        = EXINT14_INT_IRQn,         \
        .irq_prio   = EXINT14_INT_PRIO,         \
    }
#endif /* EXINT14_IRQ_CONFIG */

#ifndef EXINT15_IRQ_CONFIG
#define EXINT15_IRQ_CONFIG                      \
    {                                           \
        .irq        = EXINT15_INT_IRQn,         \
        .irq_prio   = EXINT15_INT_PRIO,         \
    }
#endif /* EXINT15_IRQ_CONFIG */

#endif

#endif /* __DRV_GPIO_H__ */
