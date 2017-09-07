/*
 * VMM Bus
 *
 * COPYRIGHT (C) 2015, Shanghai Real-Thread Technology Co., Ltd
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
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
 * 2015-01-07     Grissiom     init commit
 */

#include <rtthread.h>
#include <board.h>

rt_inline void rt_vbus_tick(unsigned int target_cpu, unsigned int irqnr)
{
    __SEV();
}

/* Read memory barrier. */
rt_inline void rt_vbus_smp_rmb(void)
{
    __DMB();
}

/* Write memory barrier. */
rt_inline void rt_vbus_smp_wmb(void)
{
    __DSB();
}

/* General memory barrier. */
rt_inline void rt_vbus_smp_mb(void)
{
    __DSB();
}
