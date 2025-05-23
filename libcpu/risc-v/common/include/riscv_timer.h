/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-28     Bernard      The unify RISC-V porting code.
 */

#ifndef __RISCV_TIMER_H__
#define __RISCV_TIMER_H__

#include <rtdef.h>

void riscv_timer_set_frequency(rt_uint32_t freq);
rt_uint32_t riscv_timer_get_frequency(void);

rt_uint64_t riscv_timer_rdtime(void);

void riscv_timer_isr(void);

void riscv_timer_init(void);
void riscv_timer_probe(void *clint_timer_cmp, void *clint_timer_val);

void riscv_timer_us_delay(rt_uint32_t us);

#endif /* __RISCV_TIMER_H__ */
