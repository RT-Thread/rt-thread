/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#ifndef __RH850_CPU_H__
#define __RH850_CPU_H__

#include <rtdef.h>
#include "rh850_sysreg.h"

#define rh850_stsr_(id, sel)                                                \
    ({                                                                      \
        rt_uint32_t v_;                                                     \
        __asm__ volatile("stsr %1, %0, %2" : "=r"(v_) : "i"(id), "i"(sel)); \
        v_;                                                                 \
    })
#define RH850_STSR(sr) rh850_stsr_(sr)

rt_inline void rh850_di(void)
{
    __asm__ volatile("di" ::: "memory");
}

rt_inline void rh850_ei(void)
{
    __asm__ volatile("ei" ::: "memory");
}

rt_inline void rh850_syncp(void)
{
    __asm__ volatile("syncp" ::: "memory");
}

rt_inline void rh850_halt(void)
{
    __asm__ volatile("halt" ::: "memory");
}

/* Layout of SAVE_CONTEXT in context_gcc.S and of the fault entries */
struct rt_hw_stack_frame
{
    rt_ubase_t eipc;
    rt_ubase_t eipsw;
    rt_ubase_t fpsr;
    rt_ubase_t fpepc;
    rt_ubase_t r31_r4[28];
    rt_ubase_t r2;
    rt_ubase_t r1;
};

#define FRAME_GPR(n) r31_r4[31 - (n)]

extern volatile rt_ubase_t rt_interrupt_from_thread;
extern volatile rt_ubase_t rt_interrupt_to_thread;
extern volatile rt_ubase_t rt_thread_switch_interrupt_flag;

void rt_hw_interrupt_dispatch(rt_uint32_t eiic);

#endif
