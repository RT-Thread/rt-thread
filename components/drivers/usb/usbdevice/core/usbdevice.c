/*
 * File      : usbdevice.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2012, RT-Thread Development Team
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
 * 2012-10-02     Yi Qiu       first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rtservice.h>

#ifdef RT_USING_USB_DEVICE

#ifdef RT_USB_DEVICE_COMPOSITE
const static char* ustring[] =
{
    "Language",
    "RT-Thread Team.",
    "RTT Composite Device",
    "1.1.0",
    "Configuration",
    "Interface",
};
#endif

#ifdef RT_USB_DEVICE_COMPOSITE
static struct udevice_descriptor compsit_desc =
{
    USB_DESC_LENGTH_DEVICE,     //bLength;
    USB_DESC_TYPE_DEVICE,       //type;
    USB_BCD_VERSION,            //bcdUSB;
    USB_CLASS_MISC,             //bDeviceClass;
    0x02,                       //bDeviceSubClass;
    0x01,                       //bDeviceProtocol;
    0x40,                       //bMaxPacketSize0;
    _VENDOR_ID,                 //idVendor;
    _PRODUCT_ID,                //idProduct;
    USB_BCD_DEVICE,             //bcdDevice;
    USB_STRING_MANU_INDEX,      //iManufacturer;
    USB_STRING_PRODUCT_INDEX,   //iProduct;
    USB_STRING_SERIAL_INDEX,    //iSerialNumber;
    USB_DYNAMIC,                //bNumConfigurations;
};
#endif

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
    udevice = rt_usbd_device_create();

    /* set usb controller driver to the device */
    rt_usbd_device_set_controller(udevice, (udcd_t)udc);

    /* create a configuration object */
    cfg = rt_usbd_config_create();

#ifdef RT_USB_DEVICE_MSTORAGE
    /* create a mass storage class object */
    cls = rt_usbd_class_mstorage_create(udevice);

    /* add the class to the configuration */
    rt_usbd_config_add_class(cfg, cls);
#endif
#ifdef RT_USB_DEVICE_CDC
    /* create a cdc class object */
    cls = rt_usbd_class_cdc_create(udevice);

    /* add the class to the configuration */
    rt_usbd_config_add_class(cfg, cls);
#endif
#ifdef RT_USB_DEVICE_RNDIS
    /* create a rndis class object */
    cls = rt_usbd_class_rndis_create(udevice);

    /* add the class to the configuration */
    rt_usbd_config_add_class(cfg, cls);
#endif

    /* set device descriptor to the device */
#ifdef RT_USB_DEVICE_COMPOSITE
    rt_usbd_device_set_descriptor(udevice, &compsit_desc);
    rt_usbd_device_set_string(udevice, ustring);
#else
    rt_usbd_device_set_descriptor(udevice, cls->dev_desc);
#endif

    /* add the configuration to the device */
    rt_usbd_device_add_config(udevice, cfg);

    /* set default configuration to 1 */
    rt_usbd_set_config(udevice, 1);

    /* initialize usb device controller */
    rt_device_init(udc);

    return RT_EOK;
}

#endif
