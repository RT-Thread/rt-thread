/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting code.
 * 2021-02-11     lizhirui     add gp support
 * 2021-11-19     JasonHu      add fpu support
 */

#include <rthw.h>
#include <rtthread.h>

#include "cpuport.h"
#include "stack.h"
#include <sbi.h>
#include <encoding.h>

#ifdef ARCH_RISCV_FPU
    #define K_SSTATUS_DEFAULT (SSTATUS_SPP | SSTATUS_SPIE | SSTATUS_SUM | SSTATUS_FS)
#else
    #define K_SSTATUS_DEFAULT (SSTATUS_SPP | SSTATUS_SPIE | SSTATUS_SUM)
#endif
#ifdef RT_USING_SMART
#include <lwp_arch.h>
#endif

/**
 * @brief from thread used interrupt context switch
 *
 */
volatile rt_ubase_t rt_interrupt_from_thread = 0;
/**
 * @brief to thread used interrupt context switch
 *
 */
volatile rt_ubase_t rt_interrupt_to_thread = 0;
/**
 * @brief flag to indicate context switch in interrupt or not
 *
 */
volatile rt_ubase_t rt_thread_switch_interrupt_flag = 0;

void *_rt_hw_stack_init(rt_ubase_t *sp, rt_ubase_t ra, rt_ubase_t sstatus)
{
    rt_hw_switch_frame_t frame = (rt_hw_switch_frame_t)
        ((rt_ubase_t)sp - sizeof(struct rt_hw_switch_frame));

    rt_memset(frame, 0, sizeof(struct rt_hw_switch_frame));

    frame->regs[RT_HW_SWITCH_CONTEXT_RA] = ra;
    frame->regs[RT_HW_SWITCH_CONTEXT_SSTATUS] = sstatus;

    return (void *)frame;
}

int rt_hw_cpu_id(void)
{
    return 0;
}

/**
 * This function will initialize thread stack, we assuming
 * when scheduler restore this new thread, context will restore
 * an entry to user first application
 *
 * s0-s11, ra, sstatus, a0
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void *tentry,
                             void *parameter,
                             rt_uint8_t *stack_addr,
                             void *texit)
{
    rt_ubase_t *sp = (rt_ubase_t *)stack_addr;
    // we use a strict alignment requirement for Q extension
    sp = (rt_ubase_t *)RT_ALIGN_DOWN((rt_ubase_t)sp, 16);

    (*--sp) = (rt_ubase_t)tentry;
    (*--sp) = (rt_ubase_t)parameter;
    (*--sp) = (rt_ubase_t)texit;
    --sp;   /* alignment */

    /* compatible to RESTORE_CONTEXT */
    extern void _rt_thread_entry(void);
    return (rt_uint8_t *)_rt_hw_stack_init(sp, (rt_ubase_t)_rt_thread_entry, K_SSTATUS_DEFAULT);
}

/*
 * #ifdef RT_USING_SMP
 * void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread);
 * #else
 * void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to);
 * #endif
 */
#ifndef RT_USING_SMP
void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to, rt_thread_t from_thread, rt_thread_t to_thread)
{
    if (rt_thread_switch_interrupt_flag == 0)
        rt_interrupt_from_thread = from;

    rt_interrupt_to_thread = to;
    rt_thread_switch_interrupt_flag = 1;

    return;
}
#endif /* end of RT_USING_SMP */

/** shutdown CPU */
void rt_hw_cpu_shutdown(void)
{
    rt_uint32_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();

    sbi_shutdown();

    while (1)
        ;
}

void rt_hw_set_process_id(int pid)
{
    // TODO
}
