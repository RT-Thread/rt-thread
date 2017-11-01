/*
 * File      : sched.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
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
 */

#include <sched.h>

int sched_yield(void)
{
    rt_thread_yield();

    return 0;
}
RTM_EXPORT(sched_yield);

int sched_get_priority_min(int policy)
{
    if (policy != SCHED_FIFO && policy != SCHED_RR)
        return EINVAL;

    return 0;
}
RTM_EXPORT(sched_get_priority_min);

int sched_get_priority_max(int policy)
{
    if (policy != SCHED_FIFO && policy != SCHED_RR)
        return EINVAL;

    return RT_THREAD_PRIORITY_MAX - 1;
}
RTM_EXPORT(sched_get_priority_max);

int sched_setscheduler(pid_t pid, int policy)
{
    return EOPNOTSUPP;
}
RTM_EXPORT(sched_setscheduler);
