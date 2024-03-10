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
#include <board.h>

rt_inline void rt_vbus_tick(unsigned int target_cpu, unsigned int irqnr)
{
    __SEV();
}

/* Read memory barrier. */
rt_inline void rt_vbus_smp_rmb(void)
{
    __DMB();
}

/* Write memory barrier. */
rt_inline void rt_vbus_smp_wmb(void)
{
    __DSB();
}

/* General memory barrier. */
rt_inline void rt_vbus_smp_mb(void)
{
    __DSB();
}

#endif /* __VBUS_HW_H__ */
