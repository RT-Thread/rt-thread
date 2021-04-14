/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author        Notes
 * 2010-11-13     weety     first version
 */


#include <rtthread.h>
#include <rthw.h>
#include "dm36x.h"

#define MAX_HANDLERS    64

extern rt_uint32_t rt_interrupt_nest;

struct rt_irq_desc irq_desc[MAX_HANDLERS];

/* exception and interrupt handler table */
rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
rt_uint32_t rt_thread_switch_interrupt_flag;

#define IRQ_BIT(irq)        ((irq) & 0x1f)

#define FIQ_REG0_OFFSET     0x0000
#define FIQ_REG1_OFFSET     0x0004
#define IRQ_REG0_OFFSET     0x0008
#define IRQ_REG1_OFFSET     0x000C
#define IRQ_ENT_REG0_OFFSET 0x0018
#define IRQ_ENT_REG1_OFFSET 0x001C
#define IRQ_INCTL_REG_OFFSET    0x0020
#define IRQ_EABASE_REG_OFFSET   0x0024
#define IRQ_INTPRI0_REG_OFFSET  0x0030
#define IRQ_INTPRI7_REG_OFFSET  0x004C

/* FIQ are pri 0-1; otherwise 2-7, with 7 lowest priority */
static const rt_uint8_t dm365_default_priorities[DAVINCI_N_AINTC_IRQ] = {
    [IRQ_DM3XX_VPSSINT0]    = 2,
    [IRQ_DM3XX_VPSSINT1]    = 6,
    [IRQ_DM3XX_VPSSINT2]    = 6,
    [IRQ_DM3XX_VPSSINT3]    = 6,
    [IRQ_DM3XX_VPSSINT4]    = 6,
    [IRQ_DM3XX_VPSSINT5]    = 6,
    [IRQ_DM3XX_VPSSINT6]    = 6,
    [IRQ_DM3XX_VPSSINT7]    = 7,
    [IRQ_DM3XX_VPSSINT8]    = 6,
    [IRQ_ASQINT]        = 6,
    [IRQ_DM365_IMXINT0] = 6,
    [IRQ_DM3XX_IMCOPINT]    = 6,
    [IRQ_USBINT]        = 4,
    [IRQ_DM3XX_RTOINT]  = 4,
    [IRQ_DM3XX_TINT5]   = 7,
    [IRQ_DM3XX_TINT6]   = 7,
    [IRQ_CCINT0]        = 5,    /* dma */
    [IRQ_DM3XX_SPINT1_0]    = 5,    /* dma */
    [IRQ_DM3XX_SPINT1_1]    = 5,    /* dma */
    [IRQ_DM3XX_SPINT2_0]    = 5,    /* dma */
    [IRQ_DM365_PSCINT]  = 7,
    [IRQ_DM3XX_SPINT2_1]    = 7,
    [IRQ_DM3XX_TINT7]   = 4,
    [IRQ_DM3XX_SDIOINT0]    = 7,
    [IRQ_DM365_MBXINT]  = 7,
    [IRQ_DM365_MBRINT]  = 7,
    [IRQ_DM3XX_MMCINT0] = 7,
    [IRQ_DM3XX_MMCINT1] = 7,
    [IRQ_DM3XX_PWMINT3] = 7,
    [IRQ_DM365_DDRINT]  = 7,
    [IRQ_DM365_AEMIFINT]    = 7,
    [IRQ_DM3XX_SDIOINT1]    = 4,
    [IRQ_DM365_TINT0]   = 2,    /* clockevent */
    [IRQ_DM365_TINT1]   = 2,    /* clocksource */
    [IRQ_DM365_TINT2]   = 7,    /* DSP timer */
    [IRQ_DM365_TINT3]   = 7,    /* system tick */
    [IRQ_PWMINT0]       = 7,
    [IRQ_PWMINT1]       = 7,
    [IRQ_DM365_PWMINT2] = 7,
    [IRQ_DM365_IICINT]  = 3,
    [IRQ_UARTINT0]      = 3,
    [IRQ_UARTINT1]      = 3,
    [IRQ_DM3XX_SPINT0_0]    = 3,
    [IRQ_DM3XX_SPINT0_1]    = 3,
    [IRQ_DM3XX_GPIO0]   = 3,
    [IRQ_DM3XX_GPIO1]   = 7,
    [IRQ_DM3XX_GPIO2]   = 4,
    [IRQ_DM3XX_GPIO3]   = 4,
    [IRQ_DM3XX_GPIO4]   = 7,
    [IRQ_DM3XX_GPIO5]   = 7,
    [IRQ_DM3XX_GPIO6]   = 7,
    [IRQ_DM3XX_GPIO7]   = 7,
    [IRQ_DM3XX_GPIO8]   = 7,
    [IRQ_DM3XX_GPIO9]   = 7,
    [IRQ_DM365_GPIO10]  = 7,
    [IRQ_DM365_GPIO11]  = 7,
    [IRQ_DM365_GPIO12]  = 7,
    [IRQ_DM365_GPIO13]  = 7,
    [IRQ_DM365_GPIO14]  = 7,
    [IRQ_DM365_GPIO15]  = 7,
    [IRQ_DM365_KEYINT]  = 7,
    [IRQ_DM365_COMMTX]  = 7,
    [IRQ_DM365_COMMRX]  = 7,
    [IRQ_EMUINT]        = 7,
};

static inline unsigned int davinci_irq_readl(int offset)
{
    return davinci_readl(DAVINCI_ARM_INTC_BASE + offset);
}

static inline void davinci_irq_writel(unsigned long value, int offset)
{
    davinci_writel(value, DAVINCI_ARM_INTC_BASE + offset);
}

/**
 * @addtogroup DM36X
 */
/*@{*/

rt_isr_handler_t rt_hw_interrupt_handle(int vector, void *param)
{
    rt_kprintf("Unhandled interrupt %d occured!!!\n", vector);
    return RT_NULL;
}

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    int i;
    register rt_uint32_t idx;
    const rt_uint8_t *priority;
    priority = dm365_default_priorities;

    /* Clear all interrupt requests */
    davinci_irq_writel(~0x0, FIQ_REG0_OFFSET);
    davinci_irq_writel(~0x0, FIQ_REG1_OFFSET);
    davinci_irq_writel(~0x0, IRQ_REG0_OFFSET);
    davinci_irq_writel(~0x0, IRQ_REG1_OFFSET);

    /* Disable all interrupts */
    davinci_irq_writel(0x0, IRQ_ENT_REG0_OFFSET);
    davinci_irq_writel(0x0, IRQ_ENT_REG1_OFFSET);

    /* Interrupts disabled immediately, IRQ entry reflects all */
    davinci_irq_writel(0x0, IRQ_INCTL_REG_OFFSET);

    /* we don't use the hardware vector table, just its entry addresses */
    davinci_irq_writel(0, IRQ_EABASE_REG_OFFSET);

    /* Clear all interrupt requests */
    davinci_irq_writel(~0x0, FIQ_REG0_OFFSET);
    davinci_irq_writel(~0x0, FIQ_REG1_OFFSET);
    davinci_irq_writel(~0x0, IRQ_REG0_OFFSET);
    davinci_irq_writel(~0x0, IRQ_REG1_OFFSET);

    for (i = IRQ_INTPRI0_REG_OFFSET; i <= IRQ_INTPRI7_REG_OFFSET; i += 4) {
        unsigned    j;
        rt_uint32_t pri;

        for (j = 0, pri = 0; j < 32; j += 4, priority++)
            pri |= (*priority & 0x07) << j;
        davinci_irq_writel(pri, i);
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
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int irq)
{
    unsigned int mask;
    rt_uint32_t l;

    mask = 1 << IRQ_BIT(irq);

    if (irq > 31) {
        l = davinci_irq_readl(IRQ_ENT_REG1_OFFSET);
        l &= ~mask;
        davinci_irq_writel(l, IRQ_ENT_REG1_OFFSET);
    } else {
        l = davinci_irq_readl(IRQ_ENT_REG0_OFFSET);
        l &= ~mask;
        davinci_irq_writel(l, IRQ_ENT_REG0_OFFSET);
    }
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int irq)
{
    unsigned int mask;
    rt_uint32_t l;

    mask = 1 << IRQ_BIT(irq);

    if (irq > 31) {
        l = davinci_irq_readl(IRQ_ENT_REG1_OFFSET);
        l |= mask;
        davinci_irq_writel(l, IRQ_ENT_REG1_OFFSET);
    } else {
        l = davinci_irq_readl(IRQ_ENT_REG0_OFFSET);
        l |= mask;
        davinci_irq_writel(l, IRQ_ENT_REG0_OFFSET);
    }
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

#ifdef RT_USING_FINSH
#ifdef RT_USING_INTERRUPT_INFO
void list_irq(void)
{
    int irq;

    rt_kprintf("number\tcount\tname\n");
    for (irq = 0; irq < MAX_HANDLERS; irq++)
    {
        if (rt_strncmp(irq_desc[irq].name, "default", sizeof("default")))
        {
            rt_kprintf("%02ld: %10ld  %s\n", irq, irq_desc[irq].counter, irq_desc[irq].name);
        }
    }
}

#include <finsh.h>
FINSH_FUNCTION_EXPORT(list_irq, list system irq);

#ifdef FINSH_USING_MSH
int cmd_list_irq(int argc, char** argv)
{
    list_irq();
    return 0;
}
FINSH_FUNCTION_EXPORT_ALIAS(cmd_list_irq, __cmd_list_irq, list system irq.);

#endif
#endif
#endif

/*@}*/
