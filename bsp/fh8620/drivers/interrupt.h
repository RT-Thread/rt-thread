/*
 *  This file is part of FH8620 BSP for RT-Thread distribution.
 *
 *	Copyright (c) 2016 Shanghai Fullhan Microelectronics Co., Ltd. 
 *	All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *	Visit http://www.fullhan.com to get contact with Fullhan.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_
#include <rthw.h>

#define NR_INTERNAL_IRQS 56
#define NR_EXTERNAL_IRQS 64

void rt_hw_interrupt_init(void);
void rt_hw_interrupt_mask(int irq);
void rt_hw_interrupt_umask(int irq);
rt_isr_handler_t rt_hw_interrupt_install(int vector, rt_isr_handler_t handler,
		void *param, const char *name);

#endif /* INTERRUPT_H_ */
