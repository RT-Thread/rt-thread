/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

void platform_get_ramfb_params(rt_uint32_t *width, rt_uint32_t *height)
{
    *width = RT_GRAPHIC_ROMFB_WIDTH;
    *height = RT_GRAPHIC_ROMFB_HEIGHT;
}
