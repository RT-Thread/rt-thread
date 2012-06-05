/*
 * File      : usbhost.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-3-12     Yi Qiu      first version
 */

#ifndef __RT_USB_HOST_INIT_H__
#define __RT_USB_HOST_INIT_H__

#include <rtthread.h>
#include "driver.h"

#define RT_DEBUG_USB			1

void rt_usbhost_init(void);
void rt_usb_system_init(void);

/* usb class driver definition */
ucd_t rt_usb_class_driver_hid(void);
ucd_t rt_usb_class_driver_hub(void);
ucd_t rt_usb_class_driver_storage(void);
ucd_t rt_usb_class_driver_adk(void);


/* usb hid protocal definition */
uprotocal_t rt_usb_hid_protocal_kbd(void);
uprotocal_t rt_usb_hid_protocal_mouse(void);

/* usb host controller driver definition */
rt_device_t rt_usb_hcd_musb(void);
rt_device_t rt_usb_hcd_ohci(void);
rt_device_t rt_usb_hcd_susb(void);

#endif
