/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/01     Bernard      The first version
 * 2018/12/27     Jesven       Change irq enable/disable to cpu0
 */
#include <plic.h>
#include <mmu.h>
#include "tick.h"
#include "encoding.h"
#include "riscv.h"
#include "interrupt.h"

struct rt_irq_desc irq_desc[MAX_HANDLERS];

static rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", vector);
    return RT_NULL;
}

int rt_hw_plic_irq_enable(int irq_number)
{
    plic_irq_enable(irq_number);
    return 0;
}

int rt_hw_plic_irq_disable(int irq_number)
{
    plic_irq_disable(irq_number);
    return 0;
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    plic_set_priority(vector, 1);

    rt_hw_plic_irq_enable(vector);
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if(vector < MAX_HANDLERS)
    {
        old_handler = irq_desc[vector].handler;
        if (handler != RT_NULL)
        {
            irq_desc[vector].handler = (rt_isr_handler_t)handler;
            irq_desc[vector].param = param;
#ifdef RT_USING_INTERRUPT_INFO
            rt_snprintf(irq_desc[vector].name, RT_NAME_MAX - 1, "%s", name);
            irq_desc[vector].counter = 0;
#endif
        }
    }

    return old_handler;
}

void rt_hw_interrupt_init()
{
    /* Enable machine external interrupts. */
    // set_csr(sie, SIP_SEIP);
    int idx = 0;
    /* init exceptions table */
    for (idx = 0; idx < MAX_HANDLERS; idx++)
    {
        irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, "default");
        irq_desc[idx].counter = 0;
#endif
    }

    plic_set_threshold(0);
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
    // union rt_hw_spinlock_t *lock = (void *)_lock;
    // _lock->slock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    // /* Use ticket lock implemented on top of the 32/64-bit atomic AMO ops.
    //  * The combined word layout (slock) maps two uint16_t fields:
    //  *   low 16 bits: owner
    //  *   high 16 bits: next (ticket allocator)
    //  * We atomically increment the "next" field by (1 << 16) and use the
    //  * returned old value to compute our ticket. Then wait until owner == ticket.
    //  */
    // rt_atomic_t prev;
    // rt_atomic_t ticket;
    // rt_atomic_t owner;

    // /* Allocate a ticket by adding (1 << 16) to slock, prev holds previous value */
    // prev = rt_hw_atomic_add((volatile rt_atomic_t *)&lock->slock, (rt_atomic_t)(1UL << 16));
    // ticket = (prev >> 16) & 0xffffUL;

    // /* Wait until owner equals our ticket */
    // for (;;)
    // {
    //     owner = rt_hw_atomic_load((volatile rt_atomic_t *)&lock->slock) & 0xffffUL;
    //     if (owner == ticket)
    //         break;
    //     /* TODO: low-power wait for interrupt while spinning */
    //     // __asm__ volatile("wfi" ::: "memory");
    // }

    // /* Ensure all following memory accesses are ordered after acquiring the lock */
    // __asm__ volatile("fence rw, rw" ::: "memory");
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    // /* Ensure memory operations before unlock are visible before owner increment */
    // __asm__ volatile("fence rw, rw" ::: "memory");

    // /* Increment owner (low 16 bits) to hand over lock to next ticket */
    // rt_hw_atomic_add((volatile rt_atomic_t *)&lock->slock, (rt_atomic_t)1);

    // // TODO: IPI interrupt to wake up other harts waiting for the lock

    // /* Make the increment visible to other harts */
    // __asm__ volatile("fence rw, rw" ::: "memory");
}

void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    
}
#endif /* RT_USING_SMP */