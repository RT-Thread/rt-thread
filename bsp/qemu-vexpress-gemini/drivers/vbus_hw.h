/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-01-07     Grissiom     init commit
 */

#ifndef __VBUS_HW_H__
#define __VBUS_HW_H__

#include <rtthread.h>
#include <stddef.h>
#include <gic.h>

rt_inline void rt_vbus_tick(unsigned int target_cpu, unsigned int irqnr)
{
    arm_gic_trigger(0, 1, irqnr);
}

/* Read memory barrier. */
rt_inline void rt_vbus_smp_rmb(void)
{
    asm volatile ("dsb" : : : "memory");
}

/* Write memory barrier. */
rt_inline void rt_vbus_smp_wmb(void)
{
    asm volatile ("dsb" : : : "memory");
}

/* General memory barrier. */
rt_inline void rt_vbus_smp_mb(void)
{
    asm volatile ("dsb" : : : "memory");
}

#endif /* __VBUS_HW_H__ */
