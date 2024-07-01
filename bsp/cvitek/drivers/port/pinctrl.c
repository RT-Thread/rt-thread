/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-15     liYony       the first version
 */
#include <rtthread.h>
#include <ioremap.h>

static rt_ubase_t pinmux_base = RT_NULL;

rt_ubase_t pinmux_base_ioremap(void)
{
    if (pinmux_base == RT_NULL)
    {
        pinmux_base = (rt_size_t)rt_ioremap((void*)0x03001000, 0x1000);
    }

    return pinmux_base;
}
