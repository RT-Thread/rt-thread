/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-19 	  WangHuachen  first version
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <rthw.h>
#include <board.h>

void rt_hw_interrupt_init(void);
void rt_hw_interrupt_mask(int vector);
void rt_hw_interrupt_umask(int vector);
int rt_hw_interrupt_get_irq(void);
void rt_hw_interrupt_trigger(int vector);
void rt_hw_interrupt_clear(int vector);
void rt_hw_interrupt_ack(int vector);

rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
        void *param, const char *name);

#endif
