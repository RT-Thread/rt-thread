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
static volatile rt_uint8_t ipi_vectors[RT_CPUS_NR] = { 0 };
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
    int cpuid = __builtin_ctz(cpu_mask); // get the bit position of the lowest set bit
    ipi_vectors[cpuid] |= (uint8_t)ipi_vector;
    sbi_send_ipi((const unsigned long *)&cpu_mask);
}

void rt_hw_ipi_init(void)
{
    static volatile rt_bool_t desc_inited = RT_FALSE;
    int idx;

    if (!desc_inited)
    {
        /* first caller (boot hart, in rt_hw_board_init) resets the table */
        desc_inited = RT_TRUE;
        for (idx = 0; idx < RT_MAX_IPI; idx++)
        {
            ipi_desc[idx].handler = RT_NULL;
            ipi_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(ipi_desc[idx].name, RT_NAME_MAX - 1, "default");
            ipi_desc[idx].counter = 0;
#endif
        }
    }

    ipi_vectors[rt_hw_cpu_id()] = 0;
    /* enable the S-mode software interrupt on the calling hart */
    set_csr(sie, SIP_SSIP);
}

void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler)
{
    if (ipi_vector < RT_MAX_IPI && ipi_isr_handler != RT_NULL)
    {
        ipi_desc[ipi_vector].handler = ipi_isr_handler;
        ipi_desc[ipi_vector].param = RT_NULL;
    }
}

void rt_hw_ipi_handler(void)
{
    int cpuid = rt_hw_cpu_id();
    rt_uint32_t ipi_vector;

    ipi_vector = ipi_vectors[cpuid];
    while (ipi_vector)
    {
        int bitpos = __builtin_ctz(ipi_vector);
        ipi_vector &= ~(1U << bitpos);
        if (bitpos < RT_MAX_IPI && ipi_desc[bitpos].handler != RT_NULL)
        {
            rt_hw_atomic_and((volatile rt_atomic_t *)&ipi_vectors[rt_cpu_get_id()], ~((rt_atomic_t)(1 << bitpos)));
            ipi_desc[bitpos].handler(bitpos, ipi_desc[bitpos].param);
        }
    }

    clear_csr(sip, SIP_SSIP);
}
#endif /* RT_USING_SMP */
