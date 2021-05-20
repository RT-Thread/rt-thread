/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include <rtthread.h>
#include <rthw.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    void rt_hw_uart_start_rx_thread();
    rt_hw_uart_start_rx_thread();
    printf("Hello RISC-V\n");

    return 0;
}
