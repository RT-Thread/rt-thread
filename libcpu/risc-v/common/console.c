/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Bernard      port from FreeBSD
 */

#include <sbi.h>

void rt_hw_console_output(const char *str)
{
    while (*str)
    {
        sbi_console_putchar(*str++);
    }
}
