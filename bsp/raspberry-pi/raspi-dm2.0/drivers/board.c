/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-10-28     zhujiale     The first version
 */

#define DBG_TAG "board"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <rthw.h>
#include <rtthread.h>
#include <mm_aspace.h>
#include <setup.h>
#include "board.h"
#include "drv_uart.h"

#include "cp15.h"
#include "mmu.h"
#include <mm_page.h>

#ifdef RT_USING_SMART
#include <lwp_arch.h>
#endif
void rt_hw_board_init(void)
{
    rt_hw_common_setup();
}
