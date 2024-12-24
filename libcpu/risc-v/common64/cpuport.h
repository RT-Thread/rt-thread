/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-03     Bernard      The first version
 */

#ifndef CPUPORT_H__
#define CPUPORT_H__

#include <rtconfig.h>
#include <opcode.h>

#ifndef __ASSEMBLY__

#ifdef RT_USING_SMP
typedef union {
    unsigned long slock;
    struct __arch_tickets {
        unsigned short owner;
        unsigned short next;
    } tickets;
} rt_hw_spinlock_t;
#endif

#include <rtcompiler.h>

rt_inline void rt_hw_dsb(void)
{
    __asm__ volatile("fence":::"memory");
}

rt_inline void rt_hw_dmb(void)
{
    __asm__ volatile("fence":::"memory");
}

rt_inline void rt_hw_isb(void)
{
    __asm__ volatile(OPC_FENCE_I:::"memory");
}

int rt_hw_cpu_id(void);

#endif

#endif
#ifdef RISCV_U_MODE
#define RISCV_USER_ENTRY 0xFFFFFFE000000000ULL
#endif
