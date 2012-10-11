/*
 * File      : usbdevice.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-02     Yi Qiu      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtservice.h>

#define RT_USB_DEVICE_CDC

const static char* ustring[] = 
{
    "Language",
    "RT-Thread Team.",
    "UDISK",
    "12345678",
    "Config",
    "Interface",
};

rt_err_t rt_usb_device_init(const char* udc_name)
{
    rt_device_t udc;
    udevice_t udevice;
    uconfig_t cfg;
    uclass_t cls;    

    RT_ASSERT(udc_name != RT_NULL);

    udc = rt_device_find(udc_name);
    if(udc == RT_NULL)
    {
        rt_kprintf("can't find usb device controller %s\n", udc_name);
        return -RT_ERROR;
    }

    /* create and startup usb device thread */
    rt_usbd_core_init();

    /* create a device object */
    udevice = rt_usbd_device_create(ustring);
    
    /* set usb controller driver to the device */
    rt_usbd_device_set_controller(udevice, (udcd_t)udc);

    /* create a configuration object */
    cfg = rt_usbd_config_create();

#if defined RT_USB_DEVICE_MASS_STORAGE
    /* create a mass storage class object */
    cls = rt_usbd_class_mass_storage_create(udevice);    
#elif defined RT_USB_DEVICE_CDC
    /* create a cdc class object */
    cls = rt_usbd_class_cdc_create(udevice);    
#else
    #error
#endif

    /* set device descriptor to the device */
    rt_usbd_device_set_descriptor(udevice, cls->dev_desc);

    /* add the class to the configuration */
    rt_usbd_config_add_class(cfg, cls);
    
    /* add the configuration to the device */
    rt_usbd_device_add_config(udevice, cfg);
    
    /* set default configuration to 1 */
    rt_usbd_set_config(udevice, 1);

    /* initialize usb device controller */
    rt_device_init(udc);

    return RT_EOK;
}

