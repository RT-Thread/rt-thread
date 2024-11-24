/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/01/11     flyingcys    The first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "interrupt.h"
#include "encoding.h"
#include "mmio.h"

extern rt_atomic_t rt_interrupt_nest;
extern rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
extern rt_uint32_t rt_thread_switch_interrupt_flag;

struct rt_irq_desc isr_table[INTERRUPTS_MAX];

static void plic_enable_irq(int irq)
{
    uint32_t mask = (irq);
    uint32_t value = 0;

    if(irq < 16) {
        rt_kprintf("unmask irq_num is %d\n",irq);
        return;
    }
    value = mmio_read_32(PLIC_ENABLE1 + 4 * (mask / 32));
    value |= (0x1 << (mask % 32));
    mmio_write_32((PLIC_ENABLE1 + (mask / 32) * 4), value);
}

static void plic_disable_irq(int irq)
{
    uint32_t mask = (irq);
    uint32_t value = 0;

    if(irq < 16) {
        rt_kprintf("mask irq_num is %d\n", irq);
        return;
    }
    value = mmio_read_32(PLIC_ENABLE1 + 4 * (mask / 32));
    value &= ~(0x1 << (mask % 32));
    mmio_write_32((PLIC_ENABLE1 + (mask / 32) * 4), value);
}

static void plic_set_priority(int irq, int priority)
{
    mmio_write_32((PLIC_PRIORITY0 + irq * 4), priority);
}

static void plic_set_threshold(uint32_t threshold)
{
    mmio_write_32((PLIC_THRESHOLD), threshold);
}

void plic_init(void)
{
    int i;

    for (i = 0; i < IRQ_MAX_NR / 4; i = i + 4)
    {
        mmio_write_32(((uintptr_t) PLIC_PRIORITY0 + i), 0);
    }

    for ( i = 0; i < IRQ_MAX_NR / 32; i ++)
    {
        mmio_write_32((PLIC_PENDING1  + i * 4), 0);
        mmio_write_32((PLIC_ENABLE1  + i * 4), 0);
    }
    plic_set_threshold(0);

    /* Enable machine external interrupts. */
    set_csr(mie, MIP_MEIP);
}

static void rt_hw_interrupt_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
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

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest               = 0;
    rt_interrupt_from_thread        = 0;
    rt_interrupt_to_thread          = 0;
    rt_thread_switch_interrupt_flag = 0;
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

    old_handler = isr_table[vector].handler;

#ifdef RT_USING_INTERRUPT_INFO
    rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
    isr_table[vector].handler = handler;
    isr_table[vector].param = param;

    // set highest priority
    plic_set_priority(vector, 7);

    return old_handler;
}

void rt_hw_irq_isr(void)
{
    int irq = mmio_read_32(PLIC_CLAIM);
    rt_isr_handler_t isr;
    void *param;

    if (irq < 0 || irq >= IRQ_MAX_NR)
    {
        rt_kprintf("bad irq number %d!\n", irq);
        return;
    }

    if (!irq)   // irq = 0 => no irq
    {
        rt_kprintf("no irq!\n");
        return;
    }
    isr = isr_table[irq].handler;
    param = isr_table[irq].param;
    if (isr != RT_NULL)
    {
        isr(irq, param);
    }

    mmio_write_32(PLIC_CLAIM, irq);

    // clear external interrupt pending
    clear_csr(mip, MIP_MEIP);
}
