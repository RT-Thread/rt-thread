/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-03-13     bigmagic     first version
 */

#ifndef __BACKTRACE_H
#define __BACKTRACE_H
#include <armv8.h>

void backtrace(struct rt_hw_exp_stack *regs);

#endif    /* __BACKTRACE_H */

