/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rthw.h>
#include <plic_driver.h>
#include <platform.h>
#include <encoding.h>
#include <interrupt.h>

#define MAX_HANDLERS    PLIC_NUM_INTERRUPTS

/* exception and interrupt handler table */
static struct rt_irq_desc irq_desc[MAX_HANDLERS];

static plic_instance_t g_plic;

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int irq)
{
    PLIC_disable_interrupt(&g_plic, irq);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_unmask(int irq)
{
    PLIC_enable_interrupt(&g_plic, irq);
    PLIC_set_priority(&g_plic, irq, 1);
}

rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", vector);
    return RT_NULL;
}

void rt_hw_interrupt_init(void)
{
    int idx;

    /*  config interrupt vector*/
    asm volatile(
        "la t0, trap_entry\n"
        "csrw mtvec, t0"
    );

    /*  enable global interrupt*/
    PLIC_init(&g_plic,
            PLIC_CTRL_ADDR,
            PLIC_NUM_INTERRUPTS,
            PLIC_NUM_PRIORITIES);

    /* init exceptions table */
    for (idx = 0; idx < MAX_HANDLERS; idx++)
    {
        rt_hw_interrupt_mask(idx);
        irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, "default");
        irq_desc[idx].counter = 0;
#endif
    }

    // enable machine external interrupt
    set_csr(mie, MIP_MEIP);
}

rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq)
{
    return (rt_uint32_t)PLIC_claim_interrupt(&g_plic);
}

void rt_hw_interrupt_ack(rt_uint32_t fiq_irq, rt_uint32_t id)
{
    PLIC_complete_interrupt(&g_plic, id);
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

/**
 * This function will be call when external machine-level
 * interrupt from PLIC occurred.
 */
void handle_m_ext_interrupt(void)
{
    rt_isr_handler_t isr_func;
    rt_uint32_t irq;
    void *param;

    /* get irq number */
    irq = rt_hw_interrupt_get_active(0);

    /* get interrupt service routine */
    isr_func = irq_desc[irq].handler;
    param = irq_desc[irq].param;

    /* turn to interrupt service routine */
    isr_func(irq, param);
    rt_hw_interrupt_ack(0, irq);

#ifdef RT_USING_INTERRUPT_INFO
    irq_desc[irq].counter ++;
#endif
}
