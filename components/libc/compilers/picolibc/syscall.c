/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-17     Flybreak     the first version
 */

#include <rtthread.h>

int pico_get_errno(void)
{
    return rt_get_errno();
}
