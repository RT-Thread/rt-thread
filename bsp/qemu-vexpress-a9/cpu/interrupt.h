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

void rt_hw_interrupt_control(int vector, int priority, int route);

void rt_hw_interrupt_init(void);

#endif
