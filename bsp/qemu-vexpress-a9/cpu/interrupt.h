/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
