/*
 * Copyright (c) 2020-2020, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/11/18     greedyhao    Bluetrum RISC-V porting code.
 */

#include <rtthread.h>
#include <stdbool.h>
#include <rthw.h>
#include "ab32vgx.h"

uint32_t irq_mask;
void *tbl_irq_vector[IRQ_TOTAL_NUM];
void (*cpu_irq_comm_hook)(void);

void set_cpu_irq_comm(void (*irq_hook)(void))
{
    cpu_irq_comm_hook = irq_hook;
}

void cpu_irq_comm_do(void)
{
	void (*pfnct)(void);
    uint32_t irq_pend = PICPND & irq_mask;
	for (int i = 0; i < IRQ_TOTAL_NUM; i++) {
        if (irq_pend & BIT(i)) {
            pfnct = tbl_irq_vector[i];
            if (pfnct) {
                pfnct();				/* call ISR */
            }
        }
	}
}

void rt_hw_irq_enable(int vector)
{
    if (vector < IRQ_TOTAL_NUM) {
        PICEN |= BIT(vector);
    }
}

void rt_hw_irq_disable(int vector)
{
    if (vector < IRQ_TOTAL_NUM) {
        PICEN &= ~BIT(vector);
    }
}

void rt_hw_interrupt_init(void)
{
}

/**
 * @brief This function will install a interrupt service routine to a interrupt.
 * 
 * @param vector 
 * @param handler 
 * @param param 
 * @param name 
 * @return rt_isr_handler_t 
 */
rt_isr_handler_t rt_hw_interrupt_install(int              vector,
                                         rt_isr_handler_t handler,
                                         void            *param,
                                         const char      *name)
{
    rt_isr_handler_t old_handler = RT_NULL;

    if (vector < IRQ_TOTAL_NUM) {
        uint32_t cpu_ie = PICCON & BIT(0);
        PICCON &= ~BIT(0);
        old_handler = tbl_irq_vector[vector];
        tbl_irq_vector[vector] = handler;
        irq_mask |= BIT(vector);
        PICCON |= cpu_ie;
        PICPR &= ~BIT(vector);
        PICEN |= BIT(vector);
    }
    return old_handler;
}
