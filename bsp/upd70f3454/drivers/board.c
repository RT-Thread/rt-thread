/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-29     lgnq         the first version
 *
 * For       : NEC V850E
 * Toolchain : IAR Embedded Workbench for V850 v3.71
*/

#include <rthw.h>
#include <rtthread.h>

#include "uart.h"
#include "board.h"

void rt_hw_board_init(void)
{
#ifdef RT_USING_UART0
    rt_hw_uart_init();
    rt_console_set_device("uart0");
#endif

    rt_kprintf("\r\n\r\nSystemInit......\r\n");
}
