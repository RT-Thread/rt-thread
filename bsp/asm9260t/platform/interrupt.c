/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 * 2015-04-27     ArdaFu     Port bsp from at91sam9260 to asm9260t
 */

#include <rthw.h>
#include "asm9260t.h"
#include "interrupt.h"

#define MAX_HANDLERS    (64)

extern rt_uint32_t rt_interrupt_nest;

/* exception and interrupt handler table */
struct rt_irq_desc irq_desc[MAX_HANDLERS];

rt_uint32_t rt_interrupt_from_thread;
rt_uint32_t rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;


/* --------------------------------------------------------------------
 *  Interrupt initialization
 * -------------------------------------------------------------------- */

/*
 * The default interrupt priority levels (0 = lowest, 3 = highest).
 */
static rt_uint32_t default_irq_priority[MAX_HANDLERS/4] =
{
    0x00000000UL, /* INT3 - INT0 */
    0x00000000UL, /* INT7 - INT4 */
    0x00000000UL, /* INT11 - INT8 */
    0x02000000UL, /* INT15 - INT12 */
    0x02020202UL, /* INT19 - INT16 */
    0x02020202UL, /* INT23 - INT20 */
    0x00000002UL, /* INT27 - INT24 */
    0x01010100UL, /* INT31 - INT28 */
    0x00000001UL, /* INT35 - INT32 */
    0x00000000UL, /* INT39 - INT36 */
    0x00000000UL, /* INT43 - INT40 */
    0x00000000UL, /* INT47 - INT44 */
    0x00000000UL, /* INT51 - INT48 */
    0x00000000UL, /* INT55 - INT52 */
    0x00000000UL, /* INT59 - INT56 */
    0x00000000UL, /* INT63 - INT60 */
};


void rt_hw_interrupt_mask(int irq);
void rt_hw_interrupt_umask(int irq);

rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param)
{
    rt_kprintf("UN-handled interrupt %d occurred!!!\n", vector);
    return RT_NULL;
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    register rt_uint32_t idx;
    /* Initialize the ICOLL interrupt controller */
    outl((1<<8), REG_SET(HW_AHBCLKCTRL1)); // Enable ICOLL clock
    outl((1<<8), REG_CLR(HW_PRESETCTRL1)); // Reset ICOLL start
    outl((1<<8), REG_SET(HW_PRESETCTRL1)); // Reset ICOLL stop

    for(idx = 0; idx < (MAX_HANDLERS/4); idx++)
    {
        rt_uint32_t reg = (HW_ICOLL_PRIORITY0 + 0x10*idx);
        outl(default_irq_priority[idx], REG_VAL(reg));
    }

    /* init exceptions table */
    for(idx=0; idx < MAX_HANDLERS; idx++)
    {
        irq_desc[idx].handler = (rt_isr_handler_t)rt_hw_interrupt_handle;
        irq_desc[idx].param = RT_NULL;
#ifdef RT_USING_INTERRUPT_INFO
        rt_snprintf(irq_desc[idx].name, RT_NAME_MAX - 1, "default");
        irq_desc[idx].counter = 0;
#endif
    }

    /* init interrupt nest, and context in thread sp */
    rt_interrupt_nest = 0;
    rt_interrupt_from_thread = 0;
    rt_interrupt_to_thread = 0;
    rt_thread_switch_interrupt_flag = 0;

    outl(0x00000000, REG_CLR(HW_ICOLL_VBASE)); //todo: fix this bug

    outl(0x00020000, REG_CLR(HW_ICOLL_CTRL)); // Clear CTRL REG
    outl(0x00050000, REG_SET(HW_ICOLL_CTRL));
    outl(0x00000004, HW_ICOLL_UNDEF_VECTOR);
    outl(~0UL, REG_CLR(HW_ICOLL_CLEAR0));
    outl(~0UL, REG_CLR(HW_ICOLL_CLEAR1));
}


/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int irq)
{
    rt_uint32_t reg = HW_ICOLL_PRIORITY0 + ((irq & 0x3CUL) << 2);
    rt_uint32_t bit = 4UL << ((irq & 3UL)<<3);
    outl(bit, REG_CLR(reg));
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int irq)
{
    rt_uint32_t reg = HW_ICOLL_PRIORITY0 + ((irq & 0x3CUL) << 2);
    rt_uint32_t bit = 4UL << ((irq & 3UL)<<3);
    outl(bit, REG_SET(reg));
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



rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq)
{
    //volatile rt_uint32_t irqstat;
    rt_uint32_t id;
    /* AIC need this dummy read */
    inl(HW_ICOLL_VECTOR);
    /* get irq number */
    id = inl(HW_ICOLL_STAT);
    /* clear pending register */
    //irqstat = inl(HW_ICOLL_VECTOR);
    return id;
}

void rt_hw_interrupt_ack(rt_uint32_t fiq_irq, rt_uint32_t id)
{
    rt_uint32_t reg = HW_ICOLL_PRIORITY0 + ((id & 0x3CUL) << 2);
    rt_uint32_t level = 1UL << (0x3 & (inl(REG_VAL(reg)) >>((id & 3UL)<<3)));

    if(id & 0x20)
        outl((1UL<<(id&0x1F)), REG_SET(HW_ICOLL_CLEAR1));
    else
        outl((1UL<<id), REG_SET(HW_ICOLL_CLEAR0));

    outl(level, HW_ICOLL_LEVELACK);
}

#ifdef RT_USING_FINSH
void list_irq(void)
{
    int irq;
    rt_kprintf("number\tcount\tname\n");
    for (irq = 0; irq < MAX_HANDLERS; irq++)
    {
        if (rt_strncmp(irq_desc[irq].name, "default", sizeof("default")))
        {
            rt_kprintf("%02ld: %10ld  %s\n",
                       irq, irq_desc[irq].counter, irq_desc[irq].name);
        }
    }
}

#include <finsh.h>
FINSH_FUNCTION_EXPORT(list_irq, list system irq);

#endif
