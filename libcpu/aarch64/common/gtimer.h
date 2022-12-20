/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-20     GuEe-GUI     first version
 */

#ifndef __GTIMER_H__
#define __GTIMER_H__

#include <rtdef.h>

void rt_hw_gtimer_init(void);
void rt_hw_gtimer_local_enable(void);
void rt_hw_gtimer_local_disable(void);

void rt_hw_gtimer_enable();

rt_inline void rt_hw_gtimer_disable(void)
{
    __asm__ volatile ("msr CNTP_CTL_EL0, xzr":::"memory");
}

void rt_hw_set_gtimer_val(rt_uint64_t value);
rt_uint64_t rt_hw_get_gtimer_val();
rt_uint64_t rt_hw_get_cntpct_val();
rt_uint64_t rt_hw_get_gtimer_frq();
rt_uint64_t rt_hw_set_gtimer_frq(rt_uint64_t value);

#endif /* __GTIMER_H__ */
