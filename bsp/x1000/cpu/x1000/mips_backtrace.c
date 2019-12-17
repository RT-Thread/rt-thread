/*
 * File      : mips_backtrace.c
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
 * 2016年9月11日     Urey         the first version
 */

#include <rtthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "mips.h"

/*********************************************************************************************************
  指令定义
*********************************************************************************************************/
#define ADDUI_SP_INST           0x27bd0000
#define SW_RA_INST              0xafbf0000
#define JR_RA_INST              0x03e00008

#define INST_OP_MASK            0xffff0000
#define INST_OFFSET_MASK        0x0000ffff

#define abs(s) ((s) < 0 ? -(s):(s))

int backtrace_ctx(mips_reg_ctx *ctx)
{
	unsigned long *addr;
	unsigned long *pc, *ra, *sp;
	size_t ra_offset;
	size_t stack_size;
	int depth;
	int size = 8;

	pc = (unsigned long *)(unsigned long)ctx->CP0EPC;
	ra = (unsigned long *)(unsigned long)ctx->regs[REG_RA];
	sp = (unsigned long *)(unsigned long)ctx->regs[REG_SP];

	rt_kprintf("[0x%08x]\n", pc);

	if (size == 1) return 1;

	ra_offset = stack_size = 0;

	for (addr = ra; !ra_offset || !stack_size; --addr)
	{
		switch (*addr & INST_OP_MASK) {
			case ADDUI_SP_INST:
				stack_size = abs((short)(*addr&INST_OFFSET_MASK));
				break;

			case SW_RA_INST:
				ra_offset = (short)(*addr&INST_OFFSET_MASK);
				break;

			case 0x3c1c0000:
				goto out_of_loop;

			default:
				break;
		}
	}

out_of_loop:
	if (ra_offset)  ra = *(unsigned long **)((unsigned long)sp + ra_offset);
	if (stack_size) sp = (unsigned long *)((unsigned long)sp + stack_size);

	// repeat backwar scanning
	for (depth = 1; depth < size && ra && ra != (unsigned long *)0xffffffff; ++depth)
	{
		rt_kprintf("RA[%2d] : [0x%08x]\n", depth ,ra);

		ra_offset = 0;
		stack_size = 0;

		for ( addr = ra; !ra_offset || !stack_size; -- addr )
		{
			switch( *addr & INST_OP_MASK)
			{
				case ADDUI_SP_INST:
					stack_size = abs((short)(*addr&INST_OFFSET_MASK));
					break;

				case SW_RA_INST:
					ra_offset = abs((short)(*addr&INST_OFFSET_MASK));
					break;

				case 0x3c1c0000:
					return depth +1;

				default:
					break;
			}
		}

		ra = *(unsigned long **)((unsigned long)sp + ra_offset);
		sp = (unsigned long *)((unsigned long)sp + stack_size);
	}

	return depth;
}

int backtrace(void)
{
	unsigned long *addr;
	unsigned long *ra;
	unsigned long *sp;
	int size = 8, depth;

	size_t ra_offset;
	size_t stack_size;

	// get current $a and $sp
	__asm__ __volatile__ (
			" move %0, $ra\n"
			" move %1, $sp\n"
			: "=r"(ra), "=r"(sp)
			);

	// scanning to find the size of hte current stack frame
	stack_size  = 0;

	for ( addr = (unsigned long *)backtrace; !stack_size; ++addr)
	{
		if ((*addr & INST_OP_MASK ) == ADDUI_SP_INST )
			stack_size = abs((short)(*addr&INST_OFFSET_MASK));
		else if ( *addr == JR_RA_INST )
			break;
	}

	sp = (unsigned long *) (( unsigned long )sp + stack_size);

	// repeat backwar scanning
	for ( depth = 0; depth < size && ((( unsigned long )ra > KSEG0BASE) && (( unsigned long )ra < KSEG1BASE)); ++ depth )
	{
		rt_kprintf("RA[%2d] : [0x%08x]\n", depth, ra);
		{
			extern void rt_thread_exit(void);
			if ((uint32_t)ra == (uint32_t)(rt_thread_exit))
				return depth;
		}

		ra_offset = 0;
		stack_size = 0;

		for ( addr = ra; !ra_offset || !stack_size; -- addr )
		{
			switch( *addr & INST_OP_MASK)
			{
				case ADDUI_SP_INST:
					stack_size = abs((short)(*addr&INST_OFFSET_MASK));
					break;

				case SW_RA_INST:
					ra_offset = (short)(*addr&INST_OFFSET_MASK);
					break;

				case 0x3c1c0000:
					return depth +1;

				default:
					break;
			}
		}

		ra = *(unsigned long **)((unsigned long)sp + ra_offset);
		sp = (unsigned long*) ((unsigned long)sp+stack_size );
	}

	return depth;
}

#include <rtthread.h>
extern long list_thread(void);
void assert_hook(const char* ex, const char* func, rt_size_t line)
{
	backtrace();

	list_thread();
	rt_kprintf("(%s) assertion failed at function:%s, line number:%d \n", ex, func, line);
}

int backtrace_init(void)
{
#ifdef RT_DEBUG
	rt_assert_set_hook(assert_hook);
#endif
	return 0;
}
INIT_DEVICE_EXPORT(backtrace_init);
