/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting code.
 */

#ifndef TICK_H__
#define TICK_H__

int tick_isr(void);
int rt_hw_tick_init(void);

#endif
