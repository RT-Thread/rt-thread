/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef  CPUPORT_H__
#define  CPUPORT_H__

#include <rtdef.h>

#ifdef rt_hw_isb
#undef rt_hw_isb
#endif
#ifdef rt_hw_dsb
#undef rt_hw_dsb
#endif

rt_inline void rt_hw_isb(void)
{
#if defined(__CC_ARM)
    __asm
    {
        ISB
    }
#elif defined(__clang__) || defined(__CLANG_ARM) || defined(__GNUC__)
    __asm volatile("isb 0xf" ::: "memory");
#elif defined(__IAR_SYSTEMS_ICC__)
    __asm("ISB");
#endif
}

rt_inline void rt_hw_dsb(void)
{
#if defined(__CC_ARM)
    __asm
    {
        DSB
    }
#elif defined(__clang__) || defined(__CLANG_ARM) || defined(__GNUC__)
    __asm volatile("dsb 0xf" ::: "memory");
#elif defined(__IAR_SYSTEMS_ICC__)
    __asm("DSB");
#endif
}

#ifdef RT_USING_SMP
typedef union {
    unsigned long slock;
    struct __arch_tickets {
        unsigned short owner;
        unsigned short next;
    } tickets;
} rt_hw_spinlock_t;
#endif

#endif  /*CPUPORT_H__*/
