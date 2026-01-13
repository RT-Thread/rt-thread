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

#ifdef ARCH_MM_MMU
#include "mmu.h"
#endif

#ifdef RT_USING_SMP
#include "tick.h"
#include "interrupt.h"
#endif /* RT_USING_SMP */

#ifdef ARCH_RISCV_FPU
#define K_SSTATUS_DEFAULT_BASE (SSTATUS_SPP | SSTATUS_SPIE | SSTATUS_SUM | SSTATUS_FS)
#else
#define K_SSTATUS_DEFAULT_BASE (SSTATUS_SPP | SSTATUS_SPIE | SSTATUS_SUM)
#endif

#ifdef ARCH_RISCV_VECTOR
#define K_SSTATUS_DEFAULT (K_SSTATUS_DEFAULT_BASE | SSTATUS_VS)
#else
#define K_SSTATUS_DEFAULT K_SSTATUS_DEFAULT_BASE
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

#ifdef ARCH_MM_MMU
static rt_ubase_t *percpu_hartid;
#endif

void *_rt_hw_stack_init(rt_ubase_t *sp, rt_ubase_t ra, rt_ubase_t sstatus)
{
    rt_hw_switch_frame_t frame = (rt_hw_switch_frame_t)((rt_ubase_t)sp - sizeof(struct rt_hw_switch_frame));

    rt_memset(frame, 0, sizeof(struct rt_hw_switch_frame));

    frame->regs[RT_HW_SWITCH_CONTEXT_RA] = ra;
    frame->regs[RT_HW_SWITCH_CONTEXT_SSTATUS] = sstatus;

    return (void *)frame;
}

int rt_hw_cpu_id(void)
{
#ifndef RT_USING_SMP
    return 0;
#else
    if (rt_kmem_pvoff() != 0)
    {
        return *percpu_hartid;
    }
    else
    {
        // if not enable MMU or pvoff==0, read hartid from satp register
        rt_ubase_t hartid;
        asm volatile("csrr %0, satp" : "=r"(hartid));
        return hartid & 0xFFFF;  // Assuming hartid fits in lower 16 bits
    }
#endif /* RT_USING_SMP */
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
#else
void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread)
{
    /* Perform architecture-specific context switch. This call will
     * restore the target thread context and should not return when a
     * switch is performed. The caller (scheduler) invoked this function
     * in a context where local IRQs are disabled. */
    rt_uint32_t level;
    level = rt_hw_local_irq_disable();
    rt_hw_context_switch((rt_ubase_t)from, (rt_ubase_t)to, to_thread);
    rt_hw_local_irq_enable(level);
}
#endif /* end of RT_USING_SMP */

/** shutdown CPU */
rt_weak void rt_hw_cpu_shutdown(void)
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

#ifdef RT_USING_SMP
extern void _start(void);
extern int boot_hartid;
/* Boot secondary harts using the SBI HSM hart_start call. */
void rt_hw_secondary_cpu_up(void)
{
    rt_uint64_t entry_pa;
    int hart, ret;

    /* translate kernel virtual _start to physical address. */
#ifdef ARCH_MM_MMU
    if (rt_kmem_pvoff() != 0)
    {
        entry_pa = (rt_uint64_t)rt_kmem_v2p(&_start);
    }
    else
    {
        entry_pa = (rt_uint64_t)&_start;
    }
#else
    entry_pa = (rt_uint64_t)&_start;
#endif /* ARCH_MM_MMU */
    /* Assumes hart IDs are in range [0, RT_CPUS_NR) */
    RT_ASSERT(boot_hartid < RT_CPUS_NR);
    for (hart = 0; hart < RT_CPUS_NR; hart++)
    {
        if (hart == boot_hartid)
            continue;

        ret = sbi_hsm_hart_start((unsigned long)hart,
                                 (unsigned long)entry_pa,
                                 0UL);
        if (ret)
        {
            rt_kprintf("sbi_hsm_hart_start failed for hart %d: %d\n", hart, ret);
        }
    }
}

#ifdef ARCH_MM_MMU
void rt_hw_percpu_hartid_init(rt_ubase_t *percpu_ptr, rt_ubase_t hartid)
{
    RT_ASSERT(hartid < RT_CPUS_NR);
    rt_ubase_t *percpu_hartid_paddr;
    rt_size_t percpu_size = (rt_size_t)((rt_ubase_t)&__percpu_end - (rt_ubase_t)&__percpu_start);

    percpu_hartid = percpu_ptr;

    // from virtual address to physical address
    percpu_ptr = (rt_ubase_t *)((rt_ubase_t)percpu_ptr + (rt_ubase_t)rt_kmem_pvoff());
    percpu_hartid_paddr = percpu_ptr;

    /* Save to the real area */
    *(rt_ubase_t *)((void *)percpu_hartid_paddr + hartid * percpu_size) = hartid;
}
#endif /* ARCH_MM_MMU */

void secondary_cpu_entry(void)
{

#ifdef RT_USING_SMART
    /* switch to kernel address space */
    rt_hw_aspace_switch(&rt_kernel_space);
#endif
    /* The PLIC peripheral interrupts are currently handled by the boot_hart. */
    /* Enable the Supervisor-Timer bit in SIE */
    rt_hw_tick_init();

    /* ipi init */
    rt_hw_ipi_init();

    rt_hw_spin_lock(&_cpus_lock);
    /* invoke system scheduler start for secondary CPU */
    rt_system_scheduler_start();
}
#endif /* RT_USING_SMP */
