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

#if defined(RT_USB_HID_KEYBOARD) || defined(RT_USB_HID_MOUSE)
#include <hid.h>
#endif

/**
 * This function will initialize the usb host stack, all the usb class driver and
 * host controller driver are also be initialized here.
 * 
 * @return none.
 */
int rt_usb_host_init(void)
{
    ucd_t drv;
#ifdef RT_USB_CLASS_HID
    uprotocal_t protocal;
#endif

    /* initialize usb hub thread */
    rt_usb_hub_thread();

    /* initialize class driver */
    rt_usb_class_driver_init();

#ifdef RT_USB_CLASS_MASS_STORAGE
    /* register mass storage class driver */
    drv = rt_usb_class_driver_storage();
    rt_usb_class_driver_register(drv);
#endif

#ifdef RT_USB_CLASS_HID
    /* register hid class driver */
    drv = rt_usb_class_driver_hid();
    rt_usb_class_driver_register(drv);

#ifdef RT_USB_HID_KEYBOARD    
    /* register hid keyboard protocal */
    protocal = rt_usb_hid_protocal_kbd();    
    rt_usb_hid_protocal_register(protocal);
#endif

#ifdef RT_USB_HID_MOUSE    
    /* register hid mouse protocal */
    protocal = rt_usb_hid_protocal_mouse();    
    rt_usb_hid_protocal_register(protocal);
#endif    
#endif

#ifdef RT_USB_CLASS_ADK
    /* register adk class driver */
    drv = rt_usb_class_driver_adk();
    rt_usb_class_driver_register(drv);
#endif

    /* register hub class driver */
    drv = rt_usb_class_driver_hub();
    rt_usb_class_driver_register(drv);

	return 0;
}
INIT_COMPONENT_EXPORT(rt_usb_host_init);

