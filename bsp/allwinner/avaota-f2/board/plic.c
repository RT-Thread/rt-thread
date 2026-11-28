/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>

#include "plic.h"

/* M-mode context 0 registers of the PLIC (enable/threshold/claim). */
#define PLIC_PRIORITY_OFFSET   0x000000U
#define PLIC_ENABLE_OFFSET     0x002000U
#define PLIC_CONTEXT_OFFSET    0x200000U
#define PLIC_CONTEXT_THRESHOLD 0x00U
#define PLIC_CONTEXT_CLAIM     0x04U

struct v861_irq_desc
{
    rt_isr_handler_t handler;
    void *param;
};

static struct v861_irq_desc g_irq_desc[V861_PLIC_IRQ_NUM];

static rt_uint32_t plic_read(rt_ubase_t offset)
{
    return *(volatile rt_uint32_t *)(V861_PLIC_BASE + offset);
}

static void plic_write(rt_ubase_t offset, rt_uint32_t value)
{
    *(volatile rt_uint32_t *)(V861_PLIC_BASE + offset) = value;
}

void v861_plic_enable_irq(int irq)
{
    rt_ubase_t reg;
    rt_uint32_t bit;

    if (irq <= 0 || irq >= V861_PLIC_IRQ_NUM)
    {
        return;
    }

    /* Any priority above the 0 threshold is enough. */
    plic_write(PLIC_PRIORITY_OFFSET + (rt_ubase_t)irq * 4U, 1U);

    reg = PLIC_ENABLE_OFFSET + ((rt_ubase_t)irq / 32U) * 4U;
    bit = 1U << ((rt_ubase_t)irq % 32U);
    plic_write(reg, plic_read(reg) | bit);
}

void v861_plic_disable_irq(int irq)
{
    rt_ubase_t reg;
    rt_uint32_t bit;

    if (irq <= 0 || irq >= V861_PLIC_IRQ_NUM)
    {
        return;
    }

    reg = PLIC_ENABLE_OFFSET + ((rt_ubase_t)irq / 32U) * 4U;
    bit = 1U << ((rt_ubase_t)irq % 32U);
    plic_write(reg, plic_read(reg) & ~bit);
}

rt_isr_handler_t v861_plic_install_irq(int irq, rt_isr_handler_t handler, void *param)
{
    rt_isr_handler_t old = RT_NULL;

    if (irq <= 0 || irq >= V861_PLIC_IRQ_NUM)
    {
        return RT_NULL;
    }

    old = g_irq_desc[irq].handler;
    g_irq_desc[irq].handler = handler;
    g_irq_desc[irq].param = param;
    return old;
}

void v861_plic_init(void)
{
    rt_ubase_t irq;

    for (irq = 0; irq < V861_PLIC_IRQ_NUM; irq++)
    {
        g_irq_desc[irq].handler = RT_NULL;
        g_irq_desc[irq].param = RT_NULL;
    }

    /* Disable all sources, priority 1, threshold 0 (any interrupt passes). */
    for (irq = 1; irq < V861_PLIC_IRQ_NUM; irq++)
    {
        plic_write(PLIC_PRIORITY_OFFSET + irq * 4U, 1U);
    }
    for (irq = 0; irq < (V861_PLIC_IRQ_NUM / 32U); irq++)
    {
        plic_write(PLIC_ENABLE_OFFSET + irq * 4U, 0U);
    }
    plic_write(PLIC_CONTEXT_OFFSET + PLIC_CONTEXT_THRESHOLD, 0U);
}

void v861_plic_handle_irq(void)
{
    rt_uint32_t irq;

    while ((irq = plic_read(PLIC_CONTEXT_OFFSET + PLIC_CONTEXT_CLAIM)) != 0U)
    {
        if (irq < V861_PLIC_IRQ_NUM && g_irq_desc[irq].handler != RT_NULL)
        {
            g_irq_desc[irq].handler((int)irq, g_irq_desc[irq].param);
        }

        /* Complete: writing the ID back re-enables the source in the PLIC. */
        plic_write(PLIC_CONTEXT_OFFSET + PLIC_CONTEXT_CLAIM, irq);
    }
}
