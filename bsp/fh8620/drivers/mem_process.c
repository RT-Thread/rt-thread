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

#include <rtthread.h>
#include <rtdevice.h>
#include "mmu.h"

#define CHANGLINE_SIZE		(1)

//#define FH_DBG_MEM_PROCESS

#ifdef FH_DBG_MEM_PROCESS
void mem_input(rt_uint32_t t_addr, rt_uint32_t t_size, rt_uint8_t t_value) {

	rt_kprintf("mem process add:%x \tsize:%x\tvalue:%x\n", t_addr, t_size,
			t_value);

	rt_memset((void *) t_addr, t_value, t_size);

	mmu_clean_invalidated_dcache(t_addr, t_size);

}

void mem_output(rt_uint32_t t_addr, rt_uint32_t t_size) {

	rt_uint32_t i;
	rt_uint32_t cnt = 0;
	rt_uint32_t value;
	rt_uint32_t addr, size;

	addr = t_addr;
	if (t_size % 4) {
		rt_kprintf("mem must be alligned\n");
	}
	size = t_size / 4;
	rt_int32_t *p = (rt_uint32_t *) t_addr;

	//mmu_clean_invalidated_dcache(addr,t_size);
	rt_kprintf("mem process add:0x%x \tsize:0x%x\n", addr, t_size);
	rt_kprintf("0x%08x:", addr);
	for (i = 0; i < size; i++) {
		value = *p++;
		if ((cnt / CHANGLINE_SIZE) && (cnt % CHANGLINE_SIZE == 0)) {
			rt_kprintf("\n");
		}
		if (cnt / CHANGLINE_SIZE && (cnt % CHANGLINE_SIZE) == 0) {
			rt_kprintf("0x%08x:", addr + i * 4);
		}
		rt_kprintf("\t%08x", value);
		cnt++;

	}
	rt_kprintf("\n");

}
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>
#ifdef FH_DBG_MEM_PROCESS
FINSH_FUNCTION_EXPORT(mem_input, mem_input(addr,size,value));
FINSH_FUNCTION_EXPORT(mem_output, mem_output(add,size));
#endif
#endif
