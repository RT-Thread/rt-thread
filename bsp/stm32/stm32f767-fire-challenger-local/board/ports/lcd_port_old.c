/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-22     greedyhao    first version
 */

#include <rtthread.h>

#ifdef BSP_USING_LCD

#include <board.h>
#include "lcd_port.h"
#include <rtdevice.h>
#include <rthw.h>
#include <finsh.h>

//#define DRV_DEBUG
#define LOG_TAG             "app.lcd"
#include <drv_log.h>

#ifdef PKG_USING_GUIENGINE
#include <rtgui/driver.h>
#endif

int lcd_init(void)
{

    struct rt_device *device;
    // while (rt_device_find("sd0") == RT_NULL)
    //     rt_thread_delay(100);
    device = rt_device_find("lcd");
    if (device)
    {
        rtgui_graphic_set_device(device);
    }

    return 0;
}
// INIT_APP_EXPORT(lcd_init);

#endif /* BSP_USING_LCD */
