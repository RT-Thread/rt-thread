/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef BOARD_SMP_H__
#define BOARD_SMP_H__

#define V861_HART1_STACK_SIZE 4096

/* Kept for startup_gcc.S secondary path before RT_USING_SMP flag release. */
int rt_hw_hart_power_on(unsigned int hartid, unsigned long entry_addr);

#endif
