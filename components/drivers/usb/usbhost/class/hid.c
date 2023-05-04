/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-12     Yi Qiu      first version
 * 2021-02-23     Leslie Lee  update with current usb api
 */

#include <rtthread.h>
#include <drivers/usb_host.h>
#include "hid.h"

#ifdef RT_USBH_HID

static struct uclass_driver hid_driver;
static rt_list_t _protocal_list;

/**
 * This function will do USB_REQ_SET_IDLE request to set idle period to the usb hid device
 *
 * @param intf the interface instance.
 * @duration the idle period of requesting data.
 * @report_id the report id
 *
 * @return the error code, RT_EOK on successfully.
*/
rt_err_t rt_usbh_hid_set_idle(struct uhintf* intf, int duration, int report_id)
{
    struct urequest setup;
    struct uinstance* device;
    int timeout = USB_TIMEOUT_BASIC;

    /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    device = intf->device;

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_CLASS |
        USB_REQ_TYPE_INTERFACE;
    setup.bRequest = USB_REQ_SET_IDLE;
    setup.wIndex = 0;
    setup.wLength = 0;
    setup.wValue = (duration << 8 )| report_id;

    if (rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) == 8)
        if (rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, RT_NULL, 0, timeout) == 0)
            return RT_EOK;

    return -RT_FALSE;
}

/**
 * This function will do USB_REQ_GET_REPORT request to get report from the usb hid device
 *
 * @param intf the interface instance.
 * @buffer the data buffer to save usb report descriptor.
 * @param nbytes the size of buffer
 *
 * @return the error code, RT_EOK on successfully.
*/
rt_err_t rt_usbh_hid_get_report(struct uhintf* intf, rt_uint8_t type,
    rt_uint8_t id, rt_uint8_t *buffer, rt_size_t size)
{
    struct urequest setup;
    struct uinstance* device;
    int timeout = USB_TIMEOUT_BASIC;

    /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    device = intf->device;

    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_CLASS |
        USB_REQ_TYPE_INTERFACE;
    setup.bRequest = USB_REQ_GET_REPORT;
    setup.wIndex = intf->intf_desc->bInterfaceNumber;
    setup.wLength = size;
    setup.wValue = (type << 8 ) + id;

    if (rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) == 8)
    {
        if (rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, buffer, size, timeout) == size)
        {
            if (rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_out, RT_NULL, 0, timeout) == 0)
            {
                return RT_EOK;
            }
        }
    }
    else
        return -RT_FALSE;
    return -RT_FALSE;
}

/**
 * This function will do USB_REQ_SET_REPORT request to set report to the usb hid device
 *
 * @param intf the interface instance.
 * @buffer the data buffer to save usb report descriptor.
 * @param nbytes the size of buffer
 *
 * @return the error code, RT_EOK on successfully.
*/
rt_err_t rt_usbh_hid_set_report(struct uhintf* intf, rt_uint8_t *buffer, rt_size_t size)
{
    struct urequest setup;
    struct uinstance* device;
    int timeout = USB_TIMEOUT_BASIC;

    /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    device = intf->device;

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_CLASS |
        USB_REQ_TYPE_INTERFACE;
    setup.bRequest = USB_REQ_SET_REPORT;
    setup.wIndex = intf->intf_desc->bInterfaceNumber;
    setup.wLength = size;
    setup.wValue = 0x02 << 8;

    if (rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) == 8)
        return RT_EOK;
    else
        return -RT_FALSE;
}

/**
 * This function will do USB_REQ_SET_PROTOCOL request to set protocal to the usb hid device.
 *
 * @param intf the interface instance.
 * @param protocol the protocol id.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hid_set_protocal(struct uhintf* intf, int protocol)
{
    struct urequest setup;
    struct uinstance* device;
    int timeout = USB_TIMEOUT_BASIC;

    /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    device = intf->device;

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_CLASS |
        USB_REQ_TYPE_INTERFACE;
    setup.bRequest = USB_REQ_SET_PROTOCOL;
    setup.wIndex = 0;
    setup.wLength = 0;
    setup.wValue = protocol;

    if (rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) == 8)
        return RT_EOK;
    else
        return -RT_FALSE;
}

/**
 * This function will do USB_REQ_GET_DESCRIPTOR request for the device instance
 * to set feature of the hub port.
 *
 * @param intf the interface instance.
 * @buffer the data buffer to save usb report descriptor.
 * @param nbytes the size of buffer
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hid_get_report_descriptor(struct uhintf* intf,
    rt_uint8_t *buffer, rt_size_t size)
{
    struct urequest setup;
    struct uinstance* device;
    int timeout = USB_TIMEOUT_BASIC;

    /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(intf->device != RT_NULL);

    device = intf->device;

    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_STANDARD|
        USB_REQ_TYPE_INTERFACE;
    setup.bRequest = USB_REQ_GET_DESCRIPTOR;
    setup.wIndex = 0;
    setup.wLength = size;
    setup.wValue = USB_DESC_TYPE_REPORT << 8;

    if (rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) == 8)
    {
        if (rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, buffer, size, timeout) == size)
        {
            if (rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_out, RT_NULL, 0, timeout) == 0)
            {
                return RT_EOK;
            }
        }
    }
    else
        return -RT_FALSE;
    return -RT_FALSE;
}

/**
 * This function will register specified hid protocal to protocal list
 *
 * @param protocal the specified protocal.
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hid_protocal_register(uprotocal_t protocal)
{
    RT_ASSERT(protocal != RT_NULL);

    if (protocal == RT_NULL) return -RT_ERROR;

    /* insert class driver into driver list */
    rt_list_insert_after(&_protocal_list, &(protocal->list));

    return RT_EOK;
}

/**
 * This function is the callback function of hid's int endpoint, it is invoked when data comes.
 *
 * @param context the context of the callback function.
 *
 * @return none.
 */
static void rt_usbh_hid_callback(void* context)
{
    upipe_t pipe;
    struct uhid* hid;
    int timeout = USB_TIMEOUT_LONG;

    /* parameter check */
    RT_ASSERT(context != RT_NULL);

    pipe = (upipe_t)context;
    hid = (struct uhid*)((struct uhintf*)pipe->inst)->user_data;

    /* invoke protocal callback function */
    hid->protocal->callback((void*)hid);

    /* parameter check */
     RT_ASSERT(((struct uhintf*)pipe->inst)->device->hcd != RT_NULL);

    rt_usb_hcd_pipe_xfer(((struct uhintf*)pipe->inst)->device->hcd, pipe,
        hid->buffer, pipe->ep.wMaxPacketSize, timeout);
}

/**
 * This function will find specified hid protocal from protocal list
 *
 * @param pro_id the protocal id.
 *
 * @return the found protocal or RT_NULL if there is no this protocal.
 */
static uprotocal_t rt_usbh_hid_protocal_find(int pro_id)
{
    struct rt_list_node *node;

    /* try to find protocal object */
    for (node = _protocal_list.next; node != &_protocal_list; node = node->next)
    {
        uprotocal_t protocal =
            (uprotocal_t)rt_list_entry(node, struct uprotocal, list);
        if (protocal->pro_id == pro_id) return protocal;
    }

    /* not found */
    return RT_NULL;
}

/**
 * This function will run hid class driver when usb device is detected and identified
 *  as a hid class device, it will continue the enumulate process.
 *
 * @param arg the argument.
 *
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usbh_hid_enable(void* arg)
{
    int i = 0, pro_id;
    uprotocal_t protocal;
    struct uhid* hid;
    struct uhintf* intf = (struct uhintf*)arg;

    /* parameter check */
    if(intf == RT_NULL)
    {
        rt_kprintf("the interface is not available\n");
        return -RT_EIO;
    }

    pro_id = intf->intf_desc->bInterfaceProtocol;

    RT_DEBUG_LOG(RT_DEBUG_USB,
                 ("HID device enable, protocal id %d\n", pro_id));

    protocal = rt_usbh_hid_protocal_find(pro_id);
    if(protocal == RT_NULL)
    {
        rt_kprintf("can't find hid protocal %d\n", pro_id);
        intf->user_data = RT_NULL;
        return -RT_ERROR;
    }

    hid = rt_malloc(sizeof(struct uhid));
    RT_ASSERT(hid != RT_NULL);

    /* initilize the data structure */
    rt_memset(hid, 0, sizeof(struct uhid));
    intf->user_data = (void*)hid;
    hid->protocal = protocal;

    for(i=0; i<intf->intf_desc->bNumEndpoints; i++)
    {
        rt_err_t ret;
        uep_desc_t ep_desc;

        /* get endpoint descriptor */
        rt_usbh_get_endpoint_descriptor(intf->intf_desc, i, &ep_desc);
        if(ep_desc == RT_NULL)
        {
            rt_kprintf("rt_usbh_get_endpoint_descriptor error\n");
            return -RT_ERROR;
        }

        if(USB_EP_ATTR(ep_desc->bmAttributes) != USB_EP_ATTR_INT)
            continue;

        if(!(ep_desc->bEndpointAddress & USB_DIR_IN)) continue;

        ret = rt_usb_hcd_alloc_pipe(intf->device->hcd, &hid->pipe_in,
            intf->device, ep_desc);
        if(ret != RT_EOK) return ret;
    }

    /* initialize hid protocal */
    hid->protocal->init((void*)intf);

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
static rt_err_t rt_usbh_hid_disable(void* arg)
{
    struct uhid* hid;
    struct uhintf* intf = (struct uhintf*)arg;

    RT_ASSERT(intf != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_hid_disable\n"));

    hid = (struct uhid*)intf->user_data;
    if(hid != RT_NULL)
    {
        if(hid->pipe_in != RT_NULL)
        {
            /* free the HID in pipe */
            rt_usb_hcd_free_pipe(intf->device->hcd, hid->pipe_in);
        }

        /* free the hid instance */
        rt_free(hid);
    }

    return RT_EOK;
}

/**
 * This function will register hid class driver to the usb class driver manager.
 * and it should be invoked in the usb system initialization.
 *
 * @return the error code, RT_EOK on successfully.
 */
ucd_t rt_usbh_class_driver_hid(void)
{
    rt_list_init(&_protocal_list);

    hid_driver.class_code = USB_CLASS_HID;

    hid_driver.enable = rt_usbh_hid_enable;
    hid_driver.disable = rt_usbh_hid_disable;

    return &hid_driver;
}

#endif

