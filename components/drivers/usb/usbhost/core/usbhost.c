/*
 * File      : usbhost.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
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
 * 2011-12-12     Yi Qiu      first version
 */
#include <rtthread.h>
#include <drivers/usb_host.h>

#define USB_HOST_CONTROLLER_NAME      "usbh"

#if defined(RT_USBH_HID_KEYBOARD) || defined(RT_USBH_HID_MOUSE)
#include <hid.h>
#endif

/**
 * This function will initialize the usb host stack, all the usb class driver and
 * host controller driver are also be initialized here.
 * 
 * @return none.
 */
rt_err_t rt_usb_host_init(void)
{
    ucd_t drv;
    rt_device_t uhc;    

    uhc = rt_device_find(USB_HOST_CONTROLLER_NAME);
    if(uhc == RT_NULL)
    {
        rt_kprintf("can't find usb host controller %s\n", USB_HOST_CONTROLLER_NAME);
        return -RT_ERROR;
    }

    /* initialize usb hub */
    rt_usbh_hub_init((uhcd_t)uhc);

    /* initialize class driver */
    rt_usbh_class_driver_init();

#ifdef RT_USBH_MSTORAGE
    /* register mass storage class driver */
    drv = rt_usbh_class_driver_storage();
    rt_usbh_class_driver_register(drv);
#endif

    /* register hub class driver */
    drv = rt_usbh_class_driver_hub();
    rt_usbh_class_driver_register(drv);

    /* initialize usb host controller */
    rt_device_init(uhc);

    return RT_EOK;
}

