/*
 * File      : lcd_init.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
INIT_APP_EXPORT(lcd_init);
#endif
