/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/12/11     flyingcys    The first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "encoding.h"

#include "interrupt.h"

extern rt_atomic_t rt_interrupt_nest;
extern rt_uint32_t rt_interrupt_from_thread, rt_interrupt_to_thread;
extern rt_uint32_t rt_thread_switch_interrupt_flag;

#define CONFIG_IRQ_NUM              64U

struct rt_irq_desc isr_table[CONFIG_IRQ_NUM];

static void plic_set_priority(int irq, int priority)
{
    csi_vic_set_prio((int32_t)irq, priority);
}
void plic_init(void)
{
    int i;

    for (i = 0; i < CONFIG_IRQ_NUM; i++)
    {
        PLIC->PLIC_PRIO[i] = 31;
    }

    for (i = 0; i < (CONFIG_IRQ_NUM + 32) / 32; i++)
    {
        PLIC->PLIC_IP[i] = 0;
    }

    for (i = 0; i < (CONFIG_IRQ_NUM + 32) / 32; i++)
    {
        PLIC->PLIC_H0_MIE[i] = 0;
        PLIC->PLIC_H0_SIE[i] = 0;
    }

    /* set hart threshold 0, enable all interrupt */
    PLIC->PLIC_H0_MTH = 0;
    PLIC->PLIC_H0_STH = 0;

    for (i = 0; i < CONFIG_IRQ_NUM; i++)
    {
        PLIC->PLIC_H0_MCLAIM = i;
        PLIC->PLIC_H0_SCLAIM = i;
    }

    /* set PLIC_PER */
    PLIC->PLIC_PER = 0x1;

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
    for (idx = 0; idx < CONFIG_IRQ_NUM; idx++)
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
    if ((vector < 0) || (vector > CONFIG_IRQ_NUM))
    {
        return;
    }
    csi_vic_disable_irq(vector);
}
/**

 * This function will un-mask a interrupt.
 * @param vector the interrupt number
 */
void rt_hw_interrupt_umask(int vector)
{
    if ((vector < 0) || (vector > CONFIG_IRQ_NUM))
    {
        return;
    }

    csi_vic_enable_irq(vector);
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
    if ((vector < 0) || (vector > CONFIG_IRQ_NUM))
    {
        return old_handler;
    }

    old_handler = isr_table[vector].handler;

#ifdef RT_USING_INTERRUPT_INFO
    rt_strncpy(isr_table[vector].name, name, RT_NAME_MAX);
#endif /* RT_USING_INTERRUPT_INFO */
    isr_table[vector].handler = handler;
    isr_table[vector].param = param;

    /* set highest priority*/
    csi_vic_set_prio(vector, 7);

    return old_handler;
}
void rt_hw_irq_isr(void)
{
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    int irq = PLIC_Hn_MSCLAIM_VAL(&PLIC->PLIC_H0_SCLAIM, csi_get_cpu_id());
#else
    int irq = PLIC_Hn_MSCLAIM_VAL(&PLIC->PLIC_H0_MCLAIM, csi_get_cpu_id());
#endif
    rt_isr_handler_t isr;
    void *param;

    if (irq < 0 || irq >= CONFIG_IRQ_NUM)
    {
        rt_kprintf("bad irq number %d!\n", irq);
        return;
    }

    if (!irq)   /* irq = 0 => no irq*/
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

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    PLIC_Hn_MSCLAIM_VAL(&PLIC->PLIC_H0_SCLAIM, csi_get_cpu_id()) = irq;
#else
    PLIC_Hn_MSCLAIM_VAL(&PLIC->PLIC_H0_MCLAIM, csi_get_cpu_id()) = irq;
#endif
}