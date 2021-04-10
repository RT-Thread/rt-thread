/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2016-9-7       Urey         the first version
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
