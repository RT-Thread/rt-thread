/*
 *  VMM vector handle
 *
 * COPYRIGHT (C) 2013-2014, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *  Maintainer: bernard.xiong <bernard.xiong at gmail.com>
 *
 *  All rights reserved.
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
 * Change Logs:
 * Date           Author       Notes
 * 2013-06-15     Bernard      the first verion
 */
#include <rthw.h>
#include <rtthread.h>
#include <interrupt.h>
#include "vmm.h"

void vmm_guest_isr(int irqno, void* parameter)
{
    /* nothing, let GuestOS to handle it */
    rt_hw_interrupt_clear(irqno);
}

void vmm_vector_init(void)
{
	rt_hw_interrupt_install(RT_VMM_VIRQ_TRIGGER, vmm_guest_isr, RT_NULL, "virq");
	rt_hw_interrupt_umask(RT_VMM_VIRQ_TRIGGER);

	return;
}

