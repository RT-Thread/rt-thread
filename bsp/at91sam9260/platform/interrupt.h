/*
 * File      : interrupt.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-06     Bernard      first version
 */

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define INT_IRQ     0x00
#define INT_FIQ     0x01


rt_uint32_t rt_hw_interrupt_get_active(rt_uint32_t fiq_irq, rt_uint32_t* id);
void rt_hw_interrupt_ack(rt_uint32_t fiq_irq);

#endif
