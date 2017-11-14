/*
 * File      : stack.c
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
 * 2016年9月8日     Urey         the first version
 */

#include <rtthread.h>

#include "../common/mips.h"

register U32 $GP __asm__ ("$28");

rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter, rt_uint8_t *stack_addr, void *texit)
{
    static rt_uint32_t wSR=0;
    static rt_uint32_t wGP;

	mips_reg_ctx	*regCtx;
	mips_arg_ctx	*argCtx;
	rt_uint32_t i;

	if (wSR == 0)
	{
		wSR = read_c0_status();
		wSR &= 0xfffffffe;
		wSR |= 0x0403;

		wGP = $GP;
	}

	if ((rt_uint32_t) stack_addr & 0x7)
	{
		stack_addr = (rt_uint8_t *)((rt_uint32_t)stack_addr - 4);
	}

	argCtx = (mips_arg_ctx *)((rt_uint32_t)stack_addr - sizeof(mips_arg_ctx));
	regCtx = (mips_reg_ctx *)((rt_uint32_t)stack_addr - sizeof(mips_arg_ctx) - sizeof(mips_reg_ctx));

	for (i = 0; i < 4; ++i)
	{
		argCtx->args[i] = i;
	}

	//保存通用寄存器
	for (i = 0; i < 32; ++i)
	{
		regCtx->regs[i] = i;
	}

	regCtx->regs[REG_SP] = (rt_uint32_t)stack_addr;
	regCtx->regs[REG_A0] = (rt_uint32_t)parameter;
	regCtx->regs[REG_GP] = (rt_uint32_t)wGP;
	regCtx->regs[REG_FP] = (rt_uint32_t)0x0;
	regCtx->regs[REG_RA] = (rt_uint32_t)texit;

    regCtx->CP0DataLO	= 0x00;
    regCtx->CP0DataHI	= 0x00;
    regCtx->CP0Cause	= read_c0_cause();
    regCtx->CP0Status	= wSR;
    regCtx->CP0EPC		= (rt_uint32_t)tentry;
    regCtx->CP0BadVAddr= 0x00;

	return (rt_uint8_t *)(regCtx);
}
