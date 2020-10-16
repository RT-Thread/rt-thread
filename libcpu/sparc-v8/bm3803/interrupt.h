/*
 * Copyright (c) 2020, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-16     Dystopia     the first version
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

void rt_hw_interrupt_control(int vector, int priority, int route);
int rt_hw_interrupt_get_active(int fiq_irq);
void rt_hw_interrupt_ack(int fiq_irq);
void rt_hw_interrupt_trigger(int vector);
void rt_hw_interrupt_clear(int vector);

#endif
