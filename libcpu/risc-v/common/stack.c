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

#include <rtthread.h>

#include <cpu.h>
#include <csr.h>
#include <stack.h>
#include <cpuport.h>
#ifdef ARCH_MM_MMU
#include <mmu.h>
#endif

#if defined(RT_USING_CPLUSPLUS) && defined(ARCH_MM_MMU) && !defined(ARCH_RISCV_M_MODE)
extern char __tdata_start, __tdata_end;
extern char __tbss_start, __tbss_end;

static rt_size_t riscv_thread_tls_size(void)
{
    /* .tbss can have stricter alignment than .tdata.  Its linker-inserted
     * gap is part of the ABI-visible TLS layout and must be retained. */
    rt_size_t size = &__tbss_end - &__tdata_start;

    return RT_ALIGN(size, 16);
}

static void riscv_thread_tls_init(void *tls)
{
    rt_size_t tdata_size = &__tdata_end - &__tdata_start;
    rt_size_t tls_size = riscv_thread_tls_size();

    rt_memcpy(tls, &__tdata_start, tdata_size);
    rt_memset((rt_uint8_t *)tls + tdata_size, 0, tls_size - tdata_size);
}

#endif /* RT_USING_CPLUSPLUS && ARCH_MM_MMU && !ARCH_RISCV_M_MODE */

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
#if defined(RT_USING_CPLUSPLUS) && defined(ARCH_MM_MMU) && !defined(ARCH_RISCV_M_MODE)
    void *tls = (void *)RT_ALIGN_DOWN((rt_ubase_t)stack_addr - riscv_thread_tls_size(), 16);

    riscv_thread_tls_init(tls);
    stack_addr = tls;
#endif

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
#if defined(RT_USING_CPLUSPLUS) && defined(ARCH_MM_MMU) && !defined(ARCH_RISCV_M_MODE)
    frame->regs[RT_HW_SWITCH_CONTEXT_TP] = (rt_ubase_t)tls;
#endif
    /* Non-MMU and M-mode configurations keep their existing tp policy. */

    return (void *)frame;
}
