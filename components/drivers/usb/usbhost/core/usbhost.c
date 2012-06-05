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
 * 2011-3-12     Yi Qiu      first version
 */
#include <rtthread.h>
#include "usbhost.h"
#include "core.h"
#include "hub.h"

#if defined(RT_USB_HID_KEYBOARD) || defined(RT_USB_HID_MOUSE)
#include <hid.h>
#endif

/**
 * This function will initialize the usb host stack, all the usb class driver and
 * host controller driver are also be initialized here.
 * 
 * @return none.
 */
void rt_usbhost_init(void)
{
	ucd_t drv;
	rt_device_t dev;
#ifdef RT_USB_CLASS_HID
	uprotocal_t protocal;
#endif

	/* initialize usb hub */
	rt_usb_system_init();

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

#ifdef RT_USB_HCD_MUSB
	/* register musb host controller driver */
	dev = rt_usb_hcd_musb();
	rt_device_register(dev, "musb", 0);
	rt_device_init(dev);
#endif
	
#ifdef RT_USB_HCD_OHCI
	/* register ohci host controller driver */
	dev = rt_usb_hcd_ohci();
	rt_device_register(dev, "ohci", 0);
	rt_device_init(dev);	
#endif

#ifdef RT_USB_HCD_STM32
	/* register ohci host controller driver */
	dev = rt_usb_hcd_susb();
	rt_device_register(dev, "susb", 0);
	rt_device_init(dev);	
#endif

}

