/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

void platform_get_ramfb_params(rt_uint32_t *width, rt_uint32_t *height)
{
    *width = 800;
    *height = 600;
}

#include "../../../examples/test/hmi_test.c"
