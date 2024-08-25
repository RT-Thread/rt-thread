/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-05     bigmagic     Initial version
 */

/**
 * @addtogroup ls2k
 */

/*@{*/

#include <rtthread.h>
#include <rthw.h>
#include <exception.h>
#include <drivers/dev_pin.h>
#include "ls2k1000.h"
#include "interrupt.h"

static struct rt_irq_desc irq_handle_table[MAX_INTR];

static void rt_hw_interrupt_handler(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
}

static void liointc_init(void)
{
    int i;
    /* Router for LIOINTC0, to Core 0, INT0 (CPU IP2) */
    for (i = 0; i < 32; i ++)
    {
        HWREG8(LIOINTC0_BASE + i) = LIOINTC_COREx_INTy(0, 0);
    }

    /* Router for LIOINTC1, to Core 0, INT1 (CPU IP3) */
    for (i = 0; i < 32; i ++)
    {
        HWREG8(LIOINTC1_BASE + i) = LIOINTC_COREx_INTy(0, 1);
    }

    /* Disable all IRQs */
    HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_DISABLE) = 0xffffffff;
    HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_DISABLE) = 0xffffffff;

    /* Set all IRQs to low level triggered (Default?) */
    HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_POL) = 0x0;
    HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_EDGE) = 0x0;

    HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_POL) = 0x0;
    HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_EDGE) = 0x0;
}

//set irq mode
void liointc_set_irq_mode(int irq, int mode)
{
    if (irq < 32)
    {
        if (mode == PIN_IRQ_MODE_RISING)
        {
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_POL)  |= (0x0 << (irq));
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_EDGE) |= (0x1 << (irq));
        }
        else if (mode == PIN_IRQ_MODE_FALLING)
        {
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_POL)  |= (0x1 << (irq));
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_EDGE) |= (0x1 << (irq));
        }
        else if (mode == PIN_IRQ_MODE_HIGH_LEVEL)
        {
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_POL)  |= (0x1 << (irq));
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_EDGE) |= (0x0 << (irq));
        }
        else if (mode == PIN_IRQ_MODE_LOW_LEVEL)
        {
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_POL)  |= (0x0 << (irq));
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_EDGE) |= (0x0 << (irq));
        }
        else
        {
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_POL)  |= (0x1 << (irq));
            HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_EDGE) |= (0x1 << (irq));
        }
    }
    else
    {
        if (mode == PIN_IRQ_MODE_RISING)
        {
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_POL)  |= (0x0 << (irq - 32));
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_EDGE) |= (0x1 << (irq - 32));
        }
        else if (mode == PIN_IRQ_MODE_FALLING)
        {
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_POL)  |= (0x1 << (irq - 32));
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_EDGE) |= (0x1 << (irq - 32));
        }
        else if (mode == PIN_IRQ_MODE_HIGH_LEVEL)
        {
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_POL)  |= (0x1 << (irq - 32));
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_EDGE) |= (0x0 << (irq - 32));
        }
        else if (mode == PIN_IRQ_MODE_LOW_LEVEL)
        {
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_POL)  |= (0x0 << (irq - 32));
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_EDGE) |= (0x0 << (irq - 32));
        }
        else
        {
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_POL)  |= (0x1 << (irq - 32));
            HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_EDGE) |= (0x1 << (irq - 32));
        }
    }
}

static void liointc_isr(rt_ubase_t reg_base, rt_ubase_t isr_base,
                        int irq_base)
{
    rt_uint32_t isr, tmp;
    int intx;
    /* Mask to clear ISR */
    isr = HWREG32(isr_base);

    tmp = isr;
    /* Handle each of them */
    while (tmp)
    {
        rt_isr_handler_t irq_func;
        void *param;
        int irq;

        intx = __rt_ffs(isr) - 1;
        tmp &= ~(1 << intx);

        irq = intx + irq_base;

        irq_func = irq_handle_table[irq].handler;
        param = irq_handle_table[irq].param;
        irq_func(irq, param);
#ifdef RT_USING_INTERRUPT_INFO
        irq_handle_table[irq].counter++;
#endif
    }

    /* Enable them again */
    HWREG32(reg_base + LIOINTC_REG_INTC_ENABLE) = isr;
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    rt_uint32_t idx;

    rt_memset(irq_handle_table, 0x00, sizeof(irq_handle_table));
    for (idx = 0; idx < MAX_INTR; idx ++)
    {
        irq_handle_table[idx].handler = rt_hw_interrupt_handler;
    }

    liointc_init();
}

rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector >= 0 && vector < MAX_INTR)
    {
        old_handler = irq_handle_table[vector].handler;

#ifdef RT_USING_INTERRUPT_INFO
        rt_strncpy(irq_handle_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
        irq_handle_table[vector].handler = handler;
        irq_handle_table[vector].param = param;
    }

    if (vector <= 32)
    {
        mips_unmask_cpu_irq(2);
    }
    else
    {
        mips_unmask_cpu_irq(3);
    }

    return old_handler;
}

void rt_do_mips_cpu_irq(rt_uint32_t ip)
{
    void *param;
    rt_isr_handler_t irq_func;
    if (ip == 7)
    {
        rt_hw_timer_handler();
    }
    else if (ip == 2)
    {
        liointc_isr(LIOINTC0_BASE, CORE0_INTISR0, LIOINTC0_IRQBASE);
    }
    else if (ip == 3)
    {
        liointc_isr(LIOINTC1_BASE, CORE0_INTISR1, LIOINTC1_IRQBASE);
    }
}

void rt_hw_interrupt_umask(int irq)
{
    if (irq < LIOINTC0_IRQBASE + 32)
    {
        HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_ENABLE) = (1 << irq);
    }
    else if (irq < LIOINTC1_IRQBASE + 32)
    {
        HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_ENABLE) = (1 << (irq - 32));
    }
}

void rt_hw_interrupt_mask(int irq)
{
    if (irq < LIOINTC0_IRQBASE + 32)
    {
        HWREG32(LIOINTC0_BASE + LIOINTC_REG_INTC_DISABLE) = (1 << irq);
    }
    else if (irq < LIOINTC1_IRQBASE + 32)
    {
        HWREG32(LIOINTC1_BASE + LIOINTC_REG_INTC_DISABLE) = (1 << (irq - 32));
    }
}
/*@}*/
