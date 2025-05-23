/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-28     Bernard      The unify RISC-V porting code.
 * 2021-02-11     lizhirui     add gp support
 * 2021-11-19     JasonHu      add fpu support
 * 2025-04-20     GuEe-GUI     Port for CPU ID
 */

#include <mmu.h>
#include <cpu.h>
#include <csr.h>
#include <stack.h>
#include <cpuport.h>

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
    rt_ubase_t *sp;
    rt_hw_switch_frame_t frame;

    /* We use a strict alignment requirement for Q extension */
    sp = (rt_ubase_t *)RT_ALIGN_DOWN((rt_ubase_t)stack_addr, 16);

    *(--sp) = (rt_ubase_t)tentry;
    *(--sp) = (rt_ubase_t)parameter;
    *(--sp) = (rt_ubase_t)texit;
    /* Alignment */
    --sp;

    frame = (rt_hw_switch_frame_t)((rt_ubase_t)sp - sizeof(*frame));
    rt_memset(frame, 0, sizeof(*frame));

    frame->regs[RT_HW_SWITCH_CONTEXT_RA] = (rt_ubase_t)_thread_start;
    frame->regs[RT_HW_SWITCH_CONTEXT_XSTATUS] = K_XSTATUS_DEFAULT;
#ifdef RT_USING_SMP
#ifdef ARCH_MM_MMU
    /*
     * MMU is disabled, pre-CPU is not available,
     * Well, LWP is disabled, too. We can use 'TP' to save CPU ID.
     */
    if (!ARCH_VADDR_WIDTH)
#endif /* ARCH_MM_MMU */
    {
        frame->regs[RT_HW_SWITCH_CONTEXT_TP] = rt_hw_cpu_id();
    }
#endif /* RT_USING_SMP */

    return (void *)frame;
}
