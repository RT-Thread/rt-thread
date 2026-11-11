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

void platform_get_ramfb_params(rt_uint32_t *width, rt_uint32_t *height)
{
    *width = RT_GRAPHIC_ROMFB_WIDTH;
    *height = RT_GRAPHIC_ROMFB_HEIGHT;
}
