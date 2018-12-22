/*
 * File      : mips_excpt.h
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
 * 2016Äê9ÔÂ7ÈÕ     Urey         the first version
 */

#ifndef _MIPS_EXCPT_H_
#define _MIPS_EXCPT_H_

#include "mips_regs.h"

#ifndef __ASSEMBLY__
typedef void (* exception_func_t)(mips_reg_ctx *regs);

//extern exception_func_t mips_exception_handlers[];

int rt_hw_exception_init(void);
exception_func_t rt_set_except_vector(int n, exception_func_t func);
void install_default_execpt_handle(void);
#endif /* __ASSEMBLY__ */
#endif /* _MIPS_EXCPT_H_ */
