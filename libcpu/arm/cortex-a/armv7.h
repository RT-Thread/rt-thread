/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#ifndef __ARMV7_H__
#define __ARMV7_H__

/* the exception stack without VFP registers */
struct rt_hw_exp_stack
{
    unsigned long r0;
    unsigned long r1;
    unsigned long r2;
    unsigned long r3;
    unsigned long r4;
    unsigned long r5;
    unsigned long r6;
    unsigned long r7;
    unsigned long r8;
    unsigned long r9;
    unsigned long r10;
    unsigned long fp;
    unsigned long ip;
    unsigned long sp;
    unsigned long lr;
    unsigned long pc;
    unsigned long cpsr;
};

struct rt_hw_stack
{
    unsigned long cpsr;
    unsigned long r0;
    unsigned long r1;
    unsigned long r2;
    unsigned long r3;
    unsigned long r4;
    unsigned long r5;
    unsigned long r6;
    unsigned long r7;
    unsigned long r8;
    unsigned long r9;
    unsigned long r10;
    unsigned long fp;
    unsigned long ip;
    unsigned long lr;
    unsigned long pc;
};

#define USERMODE    0x10
#define FIQMODE     0x11
#define IRQMODE     0x12
#define SVCMODE     0x13
#define MONITORMODE 0x16
#define ABORTMODE   0x17
#define HYPMODE     0x1b
#define UNDEFMODE   0x1b
#define MODEMASK    0x1f
#define NOINT       0xc0

#define T_Bit       (1<<5)
#define F_Bit       (1<<6)
#define I_Bit       (1<<7)
#define A_Bit       (1<<8)
#define E_Bit       (1<<9)
#define J_Bit       (1<<24)

rt_inline void isb(void)
{
    asm volatile ("isb":::"memory");
}

rt_inline void dmb(void)
{
    asm volatile ("dmb":::"memory");
}

rt_inline void dsb(void)
{
    asm volatile ("dsb":::"memory");
}

rt_inline void icache_invalid_all(void)
{
    asm volatile ("mcr p15, 0, r0, c7, c5, 0":::"memory");//iciallu
    isb();
}
#endif
