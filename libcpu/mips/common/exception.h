/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-12-04     Jiaxun Yang  Initial version
 */

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include "ptrace.h"

#ifndef __ASSEMBLY__

typedef void (* exception_func_t)(struct pt_regs *regs);

extern int rt_hw_exception_init(void);
extern exception_func_t sys_exception_handlers[];
extern void rt_do_mips_cpu_irq(rt_uint32_t ip);
exception_func_t rt_set_except_vector(int n, exception_func_t func);
extern void mips_mask_cpu_irq(rt_uint32_t irq);
extern void mips_unmask_cpu_irq(rt_uint32_t irq);
#endif

#endif /* end of __EXCEPTION_H__ */
