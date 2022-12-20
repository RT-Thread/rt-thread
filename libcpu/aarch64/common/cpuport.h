/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef  CPUPORT_H__
#define  CPUPORT_H__

#include <armv8.h>

#ifdef RT_USING_SMP
typedef union {
    unsigned long slock;
    struct __arch_tickets {
        unsigned short owner;
        unsigned short next;
    } tickets;
} rt_hw_spinlock_t;
#endif

rt_inline void rt_hw_isb(void)
{
    asm volatile ("isb":::"memory");
}

rt_inline void rt_hw_dmb(void)
{
    asm volatile ("dmb sy":::"memory");
}

rt_inline void rt_hw_dsb(void)
{
    asm volatile ("dsb sy":::"memory");
}

#endif  /*CPUPORT_H__*/
