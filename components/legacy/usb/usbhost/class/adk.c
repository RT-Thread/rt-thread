/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-12     Yi Qiu      first version
 */

#include <rtthread.h>
#include <drivers/usb_host.h>
#include "adk.h"

#ifdef RT_USBH_ADK

#define DBG_TAG           "usbhost.adk"
#define DBG_LVL           DBG_INFO
#include <rtdbg.h>

static struct uclass_driver adk_driver;
static const char* _adk_manufacturer = RT_NULL;
static const char* _adk_model = RT_NULL;
static const char* _adk_description = RT_NULL;
static const char* _adk_version = RT_NULL;
static const char* _adk_uri = RT_NULL;
static const char* _adk_serial = RT_NULL;

rt_err_t rt_usbh_adk_set_string(const char* manufacturer, const char* model,
    const char* description, const char* _version, const char* uri,
    const char* serial)
{
    _adk_manufacturer = manufacturer;
    _adk_model = model;
    _adk_description = description;
    _adk_version = _version;
    _adk_uri = uri;
    _adk_serial = serial;

    return RT_EOK;
}

#ifdef RT_USING_MODULE
#include <rtm.h>

RTM_EXPORT(rt_usbh_adk_set_string);
#endif

/**
 * This function will do USB_REQ_GET_PROTOCOL request to set idle period to the usb adk device
 *
 * @param intf the interface instance.
 * @duration the idle period of requesting data.
 * @report_id the report id
 *
 * @return the error code, RT_EOK on successfully.
*/
static rt_err_t rt_usbh_adk_get_protocol(struct uintf* intf, rt_uint16_t *protocol)
{
    struct urequest setup;
    uinst_t device;
    int timeout = USB_TIMEOUT_BASIC;

        /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    device = intf->device;

    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_VENDOR |
        USB_REQ_TYPE_DEVICE;
    setup.request = USB_REQ_GET_PROTOCOL;
    setup.index = 0;
    setup.length = 2;
    setup.value = 0;

    if(rt_usb_hcd_control_xfer(device->hcd, device, &setup, (void*)protocol, 2,
        timeout) == 0) return RT_EOK;
    else return -RT_FALSE;
}

/**
 * This function will do USB_REQ_SEND_STRING request to set idle period to the usb adk device
 *
 * @param intf the interface instance.
 * @duration the idle period of requesting data.
 * @report_id the report id
 *
 * @return the error code, RT_EOK on successfully.
*/
static rt_err_t rt_usbh_adk_send_string(struct uintf* intf, rt_uint16_t index,
    const char* str)
{
    struct urequest setup;
    uinst_t device;
    int timeout = USB_TIMEOUT_BASIC;

        /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    device = intf->device;

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_VENDOR |
        USB_REQ_TYPE_DEVICE;
    setup.request = USB_REQ_SEND_STRING;
    setup.index = index;
    setup.length = rt_strlen(str) + 1;
    setup.value = 0;

    if(rt_usb_hcd_control_xfer(device->hcd, device, &setup, (void*)str,
        rt_strlen(str) + 1, timeout) == 0) return RT_EOK;
    else return -RT_FALSE;
}

/**
 * This function will do USB_REQ_START request to set idle period to the usb adk device
 *
 * @param intf the interface instance.
 * @duration the idle period of requesting data.
 * @report_id the report id
 *
 * @return the error code, RT_EOK on successfully.
*/
static rt_err_t rt_usbh_adk_start(struct uintf* intf)
{
    struct urequest setup;
    uinst_t device;
    int timeout = USB_TIMEOUT_BASIC;

        /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    device = intf->device;

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_VENDOR |
        USB_REQ_TYPE_DEVICE;
    setup.request = USB_REQ_START;
    setup.index = 0;
    setup.length = 0;
    setup.value = 0;

    if(rt_usb_hcd_control_xfer(device->hcd, device, &setup, RT_NULL, 0,
        timeout) == 0) return RT_EOK;
    else return -RT_FALSE;
}

/**
 * This function will read data from usb adk device
 *
 * @param intf the interface instance.
 *
 * @return the error code, RT_EOK on successfully.
*/
static rt_ssize_t rt_usbh_adk_read(rt_device_t device, rt_off_t pos, void* buffer,
    rt_size_t size)
{
    uadk_t adk;
    rt_size_t length;
    struct uintf* intf;

    /* check parameter */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    intf = (struct uintf*)device->user_data;
    adk = (uadk_t)intf->user_data;

    length = rt_usb_hcd_bulk_xfer(intf->device->hcd, adk->pipe_in,
        buffer, size, 300);

    return length;

}

/**
 * This function will write data to usb adk device
 *
 * @param intf the interface instance.
 *
 * @return the error code, RT_EOK on successfully.
*/
static rt_ssize_t rt_usbh_adk_write (rt_device_t device, rt_off_t pos, const void* buffer,
    rt_size_t size)
{
    uadk_t adk;
    rt_size_t length;
    struct uintf* intf;

    RT_ASSERT(buffer != RT_NULL);

    intf = (struct uintf*)device->user_data;
    adk = (uadk_t)intf->user_data;

    length = rt_usb_hcd_bulk_xfer(intf->device->hcd, adk->pipe_out,
        (void*)buffer, size, 300);

    return length;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops adk_device_ops =
{
    RT_NULL;
    RT_NULL;
    RT_NULL;
    rt_usbh_adk_read;
    rt_usbh_adk_write;
    RT_NULL;
};
#endif

/**
 * This function will run adk class driver when usb device is detected and identified
 *  as a adk class device, it will continue the enumulate process.
 *
 * @param arg the argument.
 *
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usbh_adk_enable(void* arg)
{
    int i = 0;
    uadk_t adk;
    struct uintf* intf = (struct uintf*)arg;
    udev_desc_t dev_desc;
    rt_uint16_t protocol;
    rt_err_t ret;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    LOG_D("rt_usbh_adk_run");

    dev_desc = &intf->device->dev_desc;
    if(dev_desc->idVendor == USB_ACCESSORY_VENDOR_ID &&
        (dev_desc->idProduct == USB_ACCESSORY_PRODUCT_ID ||
        dev_desc->idProduct == USB_ACCESSORY_ADB_PRODUCT_ID))
    {
        if(intf->intf_desc->bInterfaceSubClass != 0xFF) return -RT_ERROR;

        LOG_D("found android accessory device");
    }
    else
    {
        LOG_D("switch device");

        if((ret = rt_usbh_adk_get_protocol(intf, &protocol)) != RT_EOK)
        {
            rt_kprintf("rt_usbh_adk_get_protocol failed\n");
            return ret;
        }

        if(protocol != 1)
        {
            rt_kprintf("read protocol failed\n");
            return -RT_ERROR;
        }

        rt_usbh_adk_send_string(intf,
            ACCESSORY_STRING_MANUFACTURER, _adk_manufacturer);
        rt_usbh_adk_send_string(intf,
            ACCESSORY_STRING_MODEL, _adk_model);
        rt_usbh_adk_send_string(intf,
            ACCESSORY_STRING_DESCRIPTION, _adk_description);
        rt_usbh_adk_send_string(intf,
            ACCESSORY_STRING_VERSION, _adk_version);
        rt_usbh_adk_send_string(intf,
            ACCESSORY_STRING_URI, _adk_uri);
        rt_usbh_adk_send_string(intf,
            ACCESSORY_STRING_SERIAL, _adk_serial);

        LOG_D("manufacturer %s", _adk_manufacturer);
        LOG_D("model %s", _adk_model);
        LOG_D("description %s", _adk_description);
        LOG_D("version %s", _adk_version);
        LOG_D("uri %s", _adk_uri);
        LOG_D("serial %s", _adk_serial);

        if((ret = rt_usbh_adk_start(intf)) != RT_EOK)
        {
            rt_kprintf("rt_usbh_adk_start failed\n");
            return ret;
        }

        return RT_EOK;
    }

    adk = rt_malloc(sizeof(struct uadkinst));
    RT_ASSERT(adk != RT_NULL);

    /* initilize the data structure */
    rt_memset(adk, 0, sizeof(struct uadkinst));
    intf->user_data = (void*)adk;

    for(i=0; i<intf->intf_desc->bNumEndpoints; i++)
    {
        uep_desc_t ep_desc;

        /* get endpoint descriptor from interface descriptor */
        rt_usbh_get_endpoint_descriptor(intf->intf_desc, i, &ep_desc);
        if(ep_desc == RT_NULL)
        {
            rt_kprintf("rt_usb_get_endpoint_descriptor error\n");
            return -RT_ERROR;
        }

        /* the endpoint type of adk class should be BULK */
        if((ep_desc->bmAttributes & USB_EP_ATTR_TYPE_MASK) != USB_EP_ATTR_BULK)
            continue;

        /* allocate pipes according to the endpoint type */
        if(ep_desc->bEndpointAddress & USB_DIR_IN)
        {
            /* allocate an in pipe for the adk instance */
            ret = rt_usb_hcd_alloc_pipe(intf->device->hcd, &adk->pipe_in,
                intf, ep_desc, RT_NULL);
            if(ret != RT_EOK) return ret;
        }
        else
        {
            /* allocate an output pipe for the adk instance */
            ret = rt_usb_hcd_alloc_pipe(intf->device->hcd, &adk->pipe_out,
                intf, ep_desc, RT_NULL);
            if(ret != RT_EOK) return ret;
        }
    }

    /* check pipes infomation */
    if(adk->pipe_in == RT_NULL || adk->pipe_out == RT_NULL)
    {
        rt_kprintf("pipe error, unsupported device\n");
        return -RT_ERROR;
    }

    /* set configuration */
    ret = rt_usbh_set_configure(intf->device, 1);
    if(ret != RT_EOK) return ret;

    /* register adk device */
    adk->device.type    = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    adk->device.ops     = &adk_device_ops;
#else
    adk->device.init    = RT_NULL;
    adk->device.open    = RT_NULL;
    adk->device.close   = RT_NULL;
    adk->device.read    = rt_usbh_adk_read;
    adk->device.write   = rt_usbh_adk_write;
    adk->device.control = RT_NULL;
#endif
    adk->device.user_data = (void*)intf;

    rt_device_register(&adk->device, "adkdev", RT_DEVICE_FLAG_RDWR);

    return RT_EOK;
}

/**
 * This function will be invoked when usb device plug out is detected and it would clean
 * and release all hub class related resources.
 *
 * @param arg the argument.
 *
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usbh_adk_disable(void* arg)
{
    uadk_t adk;
    struct uintf* intf = (struct uintf*)arg;

    RT_ASSERT(intf != RT_NULL);

    LOG_D("rt_usbh_adk_stop");

    adk = (uadk_t)intf->user_data;
    if(adk == RT_NULL)
    {
        rt_free(intf);
        return RT_EOK;
    }

    if(adk->pipe_in != RT_NULL)
        rt_usb_hcd_free_pipe(intf->device->hcd, adk->pipe_in);

    if(adk->pipe_out != RT_NULL)
        rt_usb_hcd_free_pipe(intf->device->hcd, adk->pipe_out);

    /* unregister adk device */
    rt_device_unregister(&adk->device);

    /* free adk instance */
    if(adk != RT_NULL)
    {
        rt_free(adk);
    }

    /* free interface instance */
    rt_free(intf);

    return RT_EOK;
}

/**
 * This function will register adk class driver to the usb class driver manager.
 * and it should be invoked in the usb system initialization.
 *
 * @return the error code, RT_EOK on successfully.
 */
ucd_t rt_usbh_class_driver_adk(void)
{
    adk_driver.class_code = USB_CLASS_ADK;

    adk_driver.enable = rt_usbh_adk_enable;
    adk_driver.disable = rt_usbh_adk_disable;

    return &adk_driver;
}

#endif

