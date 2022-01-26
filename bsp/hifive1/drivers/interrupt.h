/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <rthw.h>
void rt_hw_interrupt_mask(int irq);
void rt_hw_interrupt_unmask(int irq);
rt_isr_handler_t rt_hw_interrupt_handle(rt_uint32_t vector, void *param);
void rt_hw_interrupt_init(void);
rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq);
void rt_hw_interrupt_ack(rt_uint32_t fiq_irq, rt_uint32_t id);
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name);

#endif
