/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-04-16                  first version
 */

#include <rtthread.h>
#include <rthw.h>

#include "board.h"

void rt_hw_board_init()
{
    rt_hw_serial_init();
    rt_console_set_device("uart1");
}
