/*
 * File      : usbhost.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
void rt_usb_host_init(void)
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
}

