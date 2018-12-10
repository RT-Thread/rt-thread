/*
 * File      : lwp_mem.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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

#ifndef __LWP_MEM_H__
#define __LWP_MEM_H__

extern void rt_lwp_mem_init(struct rt_lwp *lwp);
extern void rt_lwp_mem_deinit(struct rt_lwp *lwp);

extern void *rt_lwp_mem_malloc(rt_uint32_t size);
extern void rt_lwp_mem_free(void *addr);
extern void *rt_lwp_mem_realloc(void *rmem, rt_size_t newsize);

#endif
