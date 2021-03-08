/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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

