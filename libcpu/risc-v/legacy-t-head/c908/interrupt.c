/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-19     JasonHu      first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "interrupt.h"
#include "riscv.h"
#include "plic.h"

#ifdef RT_USING_SMP
#include <rtatomic.h>
#include <encoding.h>
#include <sbi.h>

struct rt_irq_desc ipi_desc[RT_MAX_IPI];
static rt_atomic_t ipi_vectors[RT_CPUS_NR] = { 0 };
#endif /* RT_USING_SMP */

#ifndef RT_USING_SMP
extern rt_atomic_t rt_interrupt_nest;
extern rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
extern rt_uint32_t rt_thread_switch_interrupt_flag;
#endif

struct rt_irq_desc isr_table[INTERRUPTS_MAX];

static void rt_hw_interrupt_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occurred!!!\n", vector);
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    /* init interrupt controller */
    plic_init();

    rt_int32_t idx;

    rt_memset(isr_table, 0x00, sizeof(isr_table));
    for (idx = 0; idx < INTERRUPTS_MAX; idx++)
    {
        isr_table[idx].handler = rt_hw_interrupt_handler;
    }

    #ifndef RT_USING_SMP
    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest               = 0;
    rt_interrupt_from_thread        = 0;
    rt_interrupt_to_thread          = 0;
    rt_thread_switch_interrupt_flag = 0;
    #endif
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    if ((vector < 0) || (vector > IRQ_MAX_NR))
    {
        return;
    }
    plic_disable_irq(vector);
}

/**

 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    if ((vector < 0) || (vector > IRQ_MAX_NR))
    {
        return;
    }
    plic_enable_irq(vector);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param handler the interrupt service routine to be installed
 * @param param the interrupt service function parameter
 * @param name the interrupt name
 * @return old handler
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;
    if ((vector < 0) || (vector > IRQ_MAX_NR))
    {
        return old_handler;
    }

    old_handler = isr_table[IRQ_OFFSET + vector].handler;

#ifdef RT_USING_INTERRUPT_INFO
    rt_strncpy(isr_table[IRQ_OFFSET + vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
    isr_table[IRQ_OFFSET + vector].handler = handler;
    isr_table[IRQ_OFFSET + vector].param = param;

    return old_handler;
}

#ifdef RT_USING_SMP

rt_bool_t rt_hw_interrupt_is_disabled(void)
{
    /* Determine the interrupt enable state */
    rt_ubase_t sstatus;
    __asm__ volatile("csrr %0, sstatus" : "=r"(sstatus));
    return (sstatus & SSTATUS_SIE) == 0;
}

void rt_hw_spin_lock_init(rt_hw_spinlock_t *_lock)
{
    _lock->slock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    /* Ticket lock on top of the AMO atomic ops: low 16 bits of slock are
     * the owner, high 16 bits are the next-ticket allocator. */
    rt_atomic_t prev;
    rt_atomic_t ticket;
    rt_atomic_t owner;

    prev = rt_hw_atomic_add((volatile rt_atomic_t *)&lock->slock, (rt_atomic_t)(1UL << 16));
    ticket = (prev >> 16) & 0xffffUL;

    for (;;)
    {
        owner = rt_hw_atomic_load((volatile rt_atomic_t *)&lock->slock) & 0xffffUL;
        if (owner == ticket)
        {
            break;
        }
    }

    __asm__ volatile("fence rw, rw" ::: "memory");
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    __asm__ volatile("fence rw, rw" ::: "memory");

    if ((rt_hw_atomic_load((volatile rt_atomic_t *)&lock->slock) & (rt_atomic_t)0xffffUL) == (rt_atomic_t)0xffffUL)
    {
        /* owner overflow: clear the owner field, keep the ticket field */
        rt_hw_atomic_and((volatile rt_atomic_t *)&lock->slock, (rt_atomic_t)0xffff0000UL);
    }
    else
    {
        rt_hw_atomic_add((volatile rt_atomic_t *)&lock->slock, (rt_atomic_t)1);
    }

    __asm__ volatile("fence rw, rw" ::: "memory");
}

void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    unsigned long hart_mask;
    int cpuid;

    /* drop harts that do not exist or cannot take an IPI yet */
    cpu_mask &= RT_CPU_MASK;
    cpu_mask &= (unsigned int)rt_hw_atomic_load((volatile rt_atomic_t *)&rt_riscv_online_mask);

    if (ipi_vector < 0 || ipi_vector >= RT_MAX_IPI || cpu_mask == 0)
    {
        return;
    }

    for (cpuid = 0; cpuid < RT_CPUS_NR; cpuid++)
    {
        if (cpu_mask & (1U << cpuid))
        {
            rt_hw_atomic_or(&ipi_vectors[cpuid], ((rt_atomic_t)1U << ipi_vector));
        }
    }

    __asm__ volatile("fence rw, rw" ::: "memory");

    hart_mask = cpu_mask;
    sbi_send_ipi(&hart_mask);
}

void rt_hw_ipi_init(void)
{
    static rt_bool_t desc_inited = RT_FALSE;
    int cpuid = rt_hw_cpu_id();

    if (!desc_inited)
    {
        desc_inited = RT_TRUE;
        for (int idx = 0; idx < RT_MAX_IPI; idx++)
        {
            ipi_desc[idx].handler = RT_NULL;
            ipi_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(ipi_desc[idx].name, RT_NAME_MAX - 1, "default");
            ipi_desc[idx].counter = 0;
#endif
        }
    }

    rt_hw_atomic_store(&ipi_vectors[cpuid], 0);
    set_csr(sie, SIP_SSIP);

    /* the vector table and SSIP are ready, so this hart may now be targeted
     * by rt_hw_ipi_send() and by a remote sfence.vma */
    rt_hw_cpu_mark_online();
}

void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler)
{
    if (ipi_vector >= 0 && ipi_vector < RT_MAX_IPI && ipi_isr_handler != RT_NULL)
    {
        ipi_desc[ipi_vector].handler = ipi_isr_handler;
        ipi_desc[ipi_vector].param = RT_NULL;
    }
}

void rt_hw_ipi_handler(void)
{
    int cpuid = rt_hw_cpu_id();

    for (;;)
    {
        rt_atomic_t pending = rt_hw_atomic_exchange(&ipi_vectors[cpuid], 0);

        /* acquire counterpart of the release barrier in rt_hw_ipi_send() */
        __asm__ volatile("fence r, rw" ::: "memory");

        if (pending == 0)
        {
            clear_csr(sip, SIP_SSIP);
            if (rt_hw_atomic_load(&ipi_vectors[cpuid]) == 0)
            {
                break;
            }
            continue;
        }

        clear_csr(sip, SIP_SSIP);

        while (pending)
        {
            int bitpos = __builtin_ctzl((unsigned long)pending);

            pending &= ~((rt_atomic_t)1U << bitpos);
            if (bitpos < RT_MAX_IPI && ipi_desc[bitpos].handler != RT_NULL)
            {
                ipi_desc[bitpos].handler(bitpos, ipi_desc[bitpos].param);
            }
        }
    }
}
#endif /* RT_USING_SMP */
