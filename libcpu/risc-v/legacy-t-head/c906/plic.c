/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-19     JasonHu      first version
 * 2021-11-12     JasonHu      fix bug that not intr on f133
 * 2023-04-22     flyingcys    add plic register ioremap
 */

#include <rtthread.h>

#include <rtdbg.h>

#include "plic.h"
#include "interrupt.h"
#include "io.h"
#include "encoding.h"
#include "ioremap.h"

static void *c906_plic_regs = RT_NULL;
extern struct rt_irq_desc isr_table[];

struct plic_handler
{
    rt_bool_t present;
    void *hart_base;
    void *enable_base;
};

rt_inline void plic_toggle(struct plic_handler *handler, int hwirq, int enable);
struct plic_handler c906_plic_handlers[C906_NR_CPUS];
static void *c906_irq_priority[INTERRUPTS_MAX] = {RT_NULL};

rt_inline void plic_irq_toggle(int hwirq, int enable)
{
    int cpu = 0;
    void *priority_addr;

    /* set priority of interrupt, interrupt 0 is zero. */
    priority_addr = (void *)((rt_size_t)c906_plic_regs + PRIORITY_BASE + hwirq * PRIORITY_PER_ID);
#ifdef RT_USING_SMART
    if (c906_irq_priority[hwirq] == RT_NULL)
    {
        c906_irq_priority[hwirq] = (void *)rt_ioremap(priority_addr, 0x1000);
    }
    priority_addr = c906_irq_priority[hwirq];
#endif
    writel(enable, priority_addr);
    struct plic_handler *handler = &c906_plic_handlers[cpu];

    if (handler->present)
    {
        plic_toggle(handler, hwirq, enable);
    }
}

static void generic_handle_irq(int irq)
{
    rt_isr_handler_t isr;
    void *param;

    if (irq < 0 || irq >= IRQ_MAX_NR)
    {
        LOG_E("bad irq number %d!\n", irq);
        return;
    }

    if (!irq)   // irq = 0 => no irq
    {
        LOG_W("no irq!\n");
        return;
    }
    isr = isr_table[IRQ_OFFSET + irq].handler;
    param = isr_table[IRQ_OFFSET + irq].param;
    if (isr != RT_NULL)
    {
        isr(irq, param);
    }
    /* complete irq. */
    plic_complete(irq);
}

void plic_complete(int irqno)
{
    int cpu = 0;
    struct plic_handler *handler = &c906_plic_handlers[cpu];

    writel(irqno, (void *)((rt_size_t)handler->hart_base + CONTEXT_CLAIM));
}

void plic_disable_irq(int irqno)
{
    plic_irq_toggle(irqno, 0);
}

void plic_enable_irq(int irqno)
{
    plic_irq_toggle(irqno, 1);
}

/*
 * Handling an interrupt is a two-step process: first you claim the interrupt
 * by reading the claim register, then you complete the interrupt by writing
 * that source ID back to the same claim register.  This automatically enables
 * and disables the interrupt, so there's nothing else to do.
 */
void plic_handle_irq(void)
{
    int cpu = 0;
    unsigned int irq;

    struct plic_handler *handler = &c906_plic_handlers[cpu];
    void *claim = (void *)((rt_size_t)handler->hart_base + CONTEXT_CLAIM);

    if (c906_plic_regs == RT_NULL || !handler->present)
    {
        LOG_E("plic state not initialized.");
        return;
    }

    clear_csr(sie, SIE_SEIE);

    while ((irq = readl(claim)))
    {
        /* ID0 is diabled permantually from spec. */
        if (irq == 0)
        {
            LOG_E("irq no is zero.");
        }
        else
        {
            generic_handle_irq(irq);
        }
    }
    set_csr(sie, SIE_SEIE);
}

rt_inline void plic_toggle(struct plic_handler *handler, int hwirq, int enable)
{
    uint32_t  *reg = (uint32_t *)((rt_size_t)handler->enable_base + (hwirq / 32) * sizeof(uint32_t));
    uint32_t hwirq_mask = 1 << (hwirq % 32);

    if (enable)
    {
        writel(readl(reg) | hwirq_mask, reg);
    }
    else
    {
        writel(readl(reg) & ~hwirq_mask, reg);
    }
}

void plic_init(void)
{
    int nr_irqs;
    int nr_context;
    int i;
    unsigned long hwirq;
    int cpu = 0;

    if (c906_plic_regs)
    {
        LOG_E("plic already initialized!");
        return;
    }

    nr_context = C906_NR_CONTEXT;

    c906_plic_regs = (void *)C906_PLIC_PHY_ADDR;
    if (!c906_plic_regs)
    {
        LOG_E("fatal error, plic is reg space is null.");
        return;
    }

    nr_irqs = C906_PLIC_NR_EXT_IRQS;

    for (i = 0; i < nr_context; i ++)
    {
        struct plic_handler *handler;
        uint32_t threshold = 0;

        cpu = 0;

        /* skip contexts other than supervisor external interrupt */
        if (i == 0)
        {
            continue;
        }

        // we always use CPU0 M-mode target register.
        handler = &c906_plic_handlers[cpu];
        if (handler->present)
        {
            threshold  = 0xffffffff;
            goto done;
        }

        handler->present = RT_TRUE;
        handler->hart_base = (void *)((rt_size_t)c906_plic_regs + CONTEXT_BASE + i * CONTEXT_PER_HART);
        handler->enable_base = (void *)((rt_size_t)c906_plic_regs + ENABLE_BASE + i * ENABLE_PER_HART);
#ifdef RT_USING_SMART
        handler->hart_base = (void *)rt_ioremap(handler->hart_base, 0x1000);
        handler->enable_base = (void *)rt_ioremap(handler->enable_base, 0x1000);
#endif
done:
        /* priority must be > threshold to trigger an interrupt */
        writel(threshold, (void *)((rt_size_t)handler->hart_base + CONTEXT_THRESHOLD));
        for (hwirq = 1; hwirq <= nr_irqs; hwirq++)
        {
            plic_toggle(handler, hwirq, 0);
        }
    }

    /* Enable supervisor external interrupts. */
    set_csr(sie, SIE_SEIE);
}
