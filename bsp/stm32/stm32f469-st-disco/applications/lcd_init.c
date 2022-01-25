/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-12     Tanek        first version
 */

#include <rtthread.h>

#if defined(PKG_USING_GUIENGINE)

#include <rtgui/driver.h>
int lcd_init(void)
{
    struct rt_device *device;
    device = rt_device_find("lcd");
    if (device)
    {
        rtgui_graphic_set_device(device);
    }

    return 0;
}
INIT_ENV_EXPORT(lcd_init);
#endif
