/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/31     Bernard      Add license info
 */

#include <rtthread.h>

#if defined(RT_USING_RTGUI) || defined(PKG_USING_GUIENGINE)

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
INIT_APP_EXPORT(lcd_init);

#endif
