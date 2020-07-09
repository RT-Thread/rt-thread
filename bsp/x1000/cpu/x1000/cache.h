/*
 * File      : cache.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2012, RT-Thread Development Team
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
 * 2016Äê9ÔÂ19ÈÕ     Urey         the first version
 */

#ifndef _X1000_CACHE_H_
#define _X1000_CACHE_H_

#include "../common/mips.h"
#include "../common/mips_cache.h"


void rt_hw_icache_invalidate_all(void);
void rt_hw_icache_flush_all(void);

void rt_hw_dcache_flush_all(void);
void rt_hw_dcache_flush_range(rt_uint32_t addr, rt_uint32_t size);
void rt_hw_dcache_invalidate_all(void);
void rt_hw_dcache_invalidate_range(rt_uint32_t addr,rt_uint32_t size);

void rt_hw_flush_cache_all(void);
#endif /* _X1000_CACHE_H_ */
