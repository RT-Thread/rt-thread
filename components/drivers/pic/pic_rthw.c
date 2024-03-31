/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-24     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

/**
 * This function will initialize hardware interrupt
 */
void rt_hw_interrupt_init(void)
{
    /* initialize pic */
    rt_pic_irq_init();
}

/**
 * This function will mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_mask(int vector)
{
    rt_pic_irq_mask(vector);
}

/**
 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    rt_pic_irq_unmask(vector);
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
    rt_pic_attach_irq(vector, handler, param, name, RT_IRQ_F_NONE);

    return RT_NULL;
}

/**
 * This function will install a interrupt service routine to a interrupt.
 * @param vector the interrupt number
 * @param new_handler the interrupt service routine to be installed
 * @param old_handler the old interrupt service routine
 */
void rt_hw_interrupt_uninstall(int vector, rt_isr_handler_t handler, void *param)
{
    rt_pic_detach_irq(vector, param);
}

#if defined(RT_USING_SMP) || defined(RT_USING_AMP)
void rt_hw_ipi_send(int ipi_vector, unsigned int cpu_mask)
{
    RT_BITMAP_DECLARE(cpu_masks, RT_CPUS_NR) = { cpu_mask };

    rt_pic_irq_send_ipi(ipi_vector, cpu_masks);
}

void rt_hw_ipi_handler_install(int ipi_vector, rt_isr_handler_t ipi_isr_handler)
{
    /* note: ipi_vector maybe different with irq_vector */
    rt_hw_interrupt_install(ipi_vector, ipi_isr_handler, 0, "IPI_HANDLER");
}
#endif
