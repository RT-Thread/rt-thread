/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-11-20     Bernard    the first version
 * 2018-11-22     Jesven     add rt_hw_spin_lock
 *                           add rt_hw_spin_unlock
 *                           add smp ipi init
 */

#include <mmu.h>
#include <board.h>
#include <mm_aspace.h>
#include <mm_page.h>
#include <setup.h>

extern size_t MMUTable[];

void rt_hw_board_init(void)
{
    rt_hw_common_setup();
}
