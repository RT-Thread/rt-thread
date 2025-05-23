/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-03     Bernard      The first version
 */

#ifndef CPUPORT_H__
#define CPUPORT_H__

#include <opcode.h>

#ifdef RT_USING_SMP
typedef union
{
    unsigned long slock;
    struct __arch_tickets
    {
        unsigned short owner;
        unsigned short next;
    } tickets;
} rt_hw_spinlock_t;

extern int riscv_master_cpu_id;
#define rt_hw_master_cpu_id() ((rt_ubase_t)riscv_master_cpu_id)
#endif /* RT_USING_SMP */

#define RISCV_FENCE(p, s)   __asm__ volatile ("fence " #p "," #s:::"memory")

#define rt_hw_barrier(...)  RISCV_FENCE(iorw, iorw)
#define rt_hw_wmb()         RISCV_FENCE(ir, ir)
#define rt_hw_rmb()         RISCV_FENCE(ow, ow)

rt_inline void rt_hw_dsb(void)
{
    __asm__ volatile ("fence":::"memory");
}

rt_inline void rt_hw_dmb(void)
{
    __asm__ volatile ("fence":::"memory");
}

rt_inline void rt_hw_isb(void)
{
#ifndef ARCH_RISCV_DISABLE_FENCE_I
    __asm__ volatile (OPC_FENCE_I:::"memory");
#endif
}

rt_inline void rt_hw_cpu_relax(void)
{
    __asm__ volatile (OPC_PAUSE_I);
    rt_hw_barrier();
}

void _thread_start(void);

#endif /* CPUPORT_H__ */
