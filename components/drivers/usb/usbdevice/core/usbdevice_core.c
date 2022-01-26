/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-10-01     Yi Qiu       first version
 * 2012-12-12     heyuanjie87  change endpoint and function handler
 * 2012-12-30     heyuanjie87  change inferface handler
 * 2013-04-26     aozima       add DEVICEQUALIFIER support.
 * 2013-07-25     Yi Qiu       update for USB CV test
 * 2017-11-15     ZYH          fix ep0 transform error
 */

#include <rtthread.h>
#include "drivers/usb_common.h"
#include "drivers/usb_device.h"

static rt_list_t device_list;

static rt_size_t rt_usbd_ep_write(udevice_t device, uep_t ep, void *buffer, rt_size_t size);
static rt_size_t rt_usbd_ep_read_prepare(udevice_t device, uep_t ep, void *buffer, rt_size_t size);
static rt_err_t rt_usbd_ep_assign(udevice_t device, uep_t ep);
rt_err_t rt_usbd_ep_unassign(udevice_t device, uep_t ep);

/**
 * This function will handle get_device_descriptor bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_device_descriptor(struct udevice* device, ureq_t setup)
{
    rt_size_t size;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_device_descriptor\n"));

    /* device descriptor wLength should less than USB_DESC_LENGTH_DEVICE*/
    size = (setup->wLength > USB_DESC_LENGTH_DEVICE) ?
           USB_DESC_LENGTH_DEVICE : setup->wLength;

    /* send device descriptor to endpoint 0 */
    rt_usbd_ep0_write(device, (rt_uint8_t*) &device->dev_desc, size);

    return RT_EOK;
}

/**
 * This function will handle get_config_descriptor bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_config_descriptor(struct udevice* device, ureq_t setup)
{
    rt_size_t size;
    ucfg_desc_t cfg_desc;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_config_descriptor\n"));

    cfg_desc = &device->curr_cfg->cfg_desc;
    size = (setup->wLength > cfg_desc->wTotalLength) ?
           cfg_desc->wTotalLength : setup->wLength;

    /* send configuration descriptor to endpoint 0 */
    rt_usbd_ep0_write(device, (rt_uint8_t*)cfg_desc, size);

    return RT_EOK;
}

/**
 * This function will handle get_string_descriptor bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful, -RT_ERROR on invalid bRequest.
 */
static rt_err_t _get_string_descriptor(struct udevice* device, ureq_t setup)
{
    struct ustring_descriptor str_desc;
    rt_uint8_t index, i;
    rt_uint32_t len;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_string_descriptor\n"));

    str_desc.type = USB_DESC_TYPE_STRING;
    index = setup->wValue & 0xFF;

    if(index == 0xEE)
    {
        index = USB_STRING_OS_INDEX;
    }

    if(index > USB_STRING_MAX)
    {
        rt_kprintf("unknown string index\n");
        rt_usbd_ep0_set_stall(device);
        return -RT_ERROR;
    }
    else if(index == USB_STRING_LANGID_INDEX)
    {
        str_desc.bLength = 4;
        str_desc.String[0] = 0x09;
        str_desc.String[1] = 0x04;
    }
    else
    {
        if(index < 5)
            len = rt_strlen(device->str[index]);
        else
            len = rt_strlen(device->str_intf[index]);
        str_desc.bLength = len*2 + 2;

        for(i=0; i<len; i++)
        {
            if(index < 5)
                str_desc.String[i*2] = device->str[index][i];
            else
                str_desc.String[i*2] = device->str_intf[index][i];
            str_desc.String[i*2 + 1] = 0;
        }
    }

    if (setup->wLength > str_desc.bLength)
        len = str_desc.bLength;
    else
        len = setup->wLength;

    /* send string descriptor to endpoint 0 */
    rt_usbd_ep0_write(device, (rt_uint8_t*)&str_desc, len);

    return RT_EOK;
}

static rt_err_t _get_qualifier_descriptor(struct udevice* device, ureq_t setup)
{
    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_qualifier_descriptor\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    if(device->dev_qualifier && device->dcd->device_is_hs)
    {
        /* send device qualifier descriptor to endpoint 0 */
        rt_usbd_ep0_write(device, (rt_uint8_t*)device->dev_qualifier,
                     sizeof(struct usb_qualifier_descriptor));
    }
    else
    {
        rt_usbd_ep0_set_stall(device);
    }

    return RT_EOK;
}

/**
 * This function will handle get_descriptor bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_descriptor(struct udevice* device, ureq_t setup)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    if(setup->request_type == USB_REQ_TYPE_DIR_IN)
    {
        switch(setup->wValue >> 8)
        {
        case USB_DESC_TYPE_DEVICE:
            _get_device_descriptor(device, setup);
            break;
        case USB_DESC_TYPE_CONFIGURATION:
            _get_config_descriptor(device, setup);
            break;
        case USB_DESC_TYPE_STRING:
            _get_string_descriptor(device, setup);
            break;
        case USB_DESC_TYPE_DEVICEQUALIFIER:
            /* If a full-speed only device (with a device descriptor version number equal to 0200H) receives a
            GetDescriptor() request for a device_qualifier, it must respond with a request error. The host must not make
            a request for an other_speed_configuration descriptor unless it first successfully retrieves the
            device_qualifier descriptor. */
            if(device->dcd->device_is_hs)
            {
                _get_qualifier_descriptor(device, setup);
            }
            else
            {
                rt_usbd_ep0_set_stall(device);
            }
            break;
        case USB_DESC_TYPE_OTHERSPEED:
            _get_config_descriptor(device, setup);
            break;
        default:
            rt_kprintf("unsupported descriptor request\n");
            rt_usbd_ep0_set_stall(device);
            break;
        }
    }
    else
    {
        rt_kprintf("request direction error\n");
        rt_usbd_ep0_set_stall(device);
    }

    return RT_EOK;
}

/**
 * This function will handle get_interface bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_interface(struct udevice* device, ureq_t setup)
{
    rt_uint8_t value;
    uintf_t intf;
    ufunction_t func;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_interface\n"));

    if (device->state != USB_STATE_CONFIGURED)
    {
        rt_usbd_ep0_set_stall(device);
        return -RT_ERROR;
    }

    /* find the specified interface and its alternate setting */
    intf = rt_usbd_find_interface(device, setup->wIndex & 0xFF, &func);
    value = intf->curr_setting->intf_desc->bAlternateSetting;

    /* send the interface alternate setting to endpoint 0*/
    rt_usbd_ep0_write(device, &value, 1);

    if (intf->handler)
    {
        intf->handler(func, setup);
    }

    return RT_EOK;
}

/**
 * This function will handle set_interface bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _set_interface(struct udevice* device, ureq_t setup)
{
    ufunction_t func;
    uintf_t intf;
    uep_t ep;
    struct rt_list_node* i;
    ualtsetting_t setting;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_set_interface\n"));

    if (device->state != USB_STATE_CONFIGURED)
    {
        rt_usbd_ep0_set_stall(device);
        return -RT_ERROR;
    }

    /* find the specified interface */
    intf = rt_usbd_find_interface(device, setup->wIndex & 0xFF, &func);

    /* set alternate setting to the interface */
    rt_usbd_set_altsetting(intf, setup->wValue & 0xFF);
    setting = intf->curr_setting;

    /* start all endpoints of the interface alternate setting */
    for(i=setting->ep_list.next; i != &setting->ep_list; i=i->next)
    {
        ep = (uep_t)rt_list_entry(i, struct uendpoint, list);
        dcd_ep_disable(device->dcd, ep);
        dcd_ep_enable(device->dcd, ep);
    }
    dcd_ep0_send_status(device->dcd);

    if (intf->handler)
    {
        intf->handler(func, setup);
    }

    return RT_EOK;
}

/**
 * This function will handle get_config bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_config(struct udevice* device, ureq_t setup)
{
    rt_uint8_t value;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);
    RT_ASSERT(device->curr_cfg != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_config\n"));

    if (device->state == USB_STATE_CONFIGURED)
    {
        /* get current configuration */
        value = device->curr_cfg->cfg_desc.bConfigurationValue;
    }
    else
    {
        value = 0;
    }
    /* write the current configuration to endpoint 0 */
    rt_usbd_ep0_write(device, &value, 1);

    return RT_EOK;
}

/**
 * This function will handle set_config bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _set_config(struct udevice* device, ureq_t setup)
{
    struct rt_list_node *i, *j, *k;
    uconfig_t cfg;
    uintf_t intf;
    ualtsetting_t setting;
    uep_t ep;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_set_config\n"));

    if (setup->wValue > device->dev_desc.bNumConfigurations)
    {
        rt_usbd_ep0_set_stall(device);
        return -RT_ERROR;
    }

    if (setup->wValue == 0)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("address state\n"));
        device->state = USB_STATE_ADDRESS;

        goto _exit;
    }

    /* set current configuration */
    rt_usbd_set_config(device, setup->wValue);
    cfg = device->curr_cfg;

    for (i=cfg->func_list.next; i!=&cfg->func_list; i=i->next)
    {
        /* run all functiones and their endpoints in the configuration */
        ufunction_t func = (ufunction_t)rt_list_entry(i, struct ufunction, list);
        for(j=func->intf_list.next; j!=&func->intf_list; j=j->next)
        {
            intf = (uintf_t)rt_list_entry(j, struct uinterface, list);
            setting = intf->curr_setting;
            for(k=setting->ep_list.next; k != &setting->ep_list; k=k->next)
            {
                ep = (uep_t)rt_list_entry(k, struct uendpoint, list);

                /* first disable then enable an endpoint */
                dcd_ep_disable(device->dcd, ep);
                dcd_ep_enable(device->dcd, ep);
            }
        }
        /* after enabled endpoints, then enable function */
        FUNC_ENABLE(func);
    }

    device->state = USB_STATE_CONFIGURED;

_exit:
    /* issue status stage */
    dcd_ep0_send_status(device->dcd);

    return RT_EOK;
}

/**
 * This function will handle set_address bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _set_address(struct udevice* device, ureq_t setup)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    /* set address in device control driver */
    dcd_set_address(device->dcd, setup->wValue);

    /* issue status stage */
    dcd_ep0_send_status(device->dcd);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_set_address\n"));

    device->state = USB_STATE_ADDRESS;

    return RT_EOK;
}

/**
 * This function will handle standard bRequest to
 * interface that defined in function-specifics
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _request_interface(struct udevice* device, ureq_t setup)
{
    uintf_t intf;
    ufunction_t func;
    rt_err_t ret;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_request_interface\n"));

    intf = rt_usbd_find_interface(device, setup->wIndex & 0xFF, &func);
    if (intf != RT_NULL)
    {
        ret = intf->handler(func, setup);
    }
    else
    {
        ret = -RT_ERROR;
    }

    return ret;
}

/**
 * This function will handle standard bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _standard_request(struct udevice* device, ureq_t setup)
{
    udcd_t dcd;
    rt_uint16_t value = 0;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    dcd = device->dcd;

    switch(setup->request_type & USB_REQ_TYPE_RECIPIENT_MASK)
    {
    case USB_REQ_TYPE_DEVICE:
        switch(setup->bRequest)
        {
        case USB_REQ_GET_STATUS:
            rt_usbd_ep0_write(device, &value, 2);
            break;
        case USB_REQ_CLEAR_FEATURE:
            rt_usbd_clear_feature(device, setup->wValue, setup->wIndex);
            dcd_ep0_send_status(dcd);
            break;
        case USB_REQ_SET_FEATURE:
            rt_usbd_set_feature(device, setup->wValue, setup->wIndex);
            break;
        case USB_REQ_SET_ADDRESS:
            _set_address(device, setup);
            break;
        case USB_REQ_GET_DESCRIPTOR:
            _get_descriptor(device, setup);
            break;
        case USB_REQ_SET_DESCRIPTOR:
            rt_usbd_ep0_set_stall(device);
            break;
        case USB_REQ_GET_CONFIGURATION:
            _get_config(device, setup);
            break;
        case USB_REQ_SET_CONFIGURATION:
            _set_config(device, setup);
            break;
        default:
            rt_kprintf("unknown device request\n");
            rt_usbd_ep0_set_stall(device);
            break;
        }
        break;
    case USB_REQ_TYPE_INTERFACE:
        switch(setup->bRequest)
        {
        case USB_REQ_GET_INTERFACE:
            _get_interface(device, setup);
            break;
        case USB_REQ_SET_INTERFACE:
            _set_interface(device, setup);
            break;
        default:
            if (_request_interface(device, setup) != RT_EOK)
            {
                rt_kprintf("unknown interface request\n");
                rt_usbd_ep0_set_stall(device);
                return - RT_ERROR;
            }
            else
                break;
        }
        break;
    case USB_REQ_TYPE_ENDPOINT:
        switch(setup->bRequest)
        {
        case USB_REQ_GET_STATUS:
        {
            uep_t ep;

            ep = rt_usbd_find_endpoint(device, RT_NULL, setup->wIndex);
            value = ep->stalled;
            rt_usbd_ep0_write(device, &value, 2);
        }
        break;
        case USB_REQ_CLEAR_FEATURE:
        {
            uep_t ep;
            uio_request_t req;
            struct rt_list_node *node;

            ep = rt_usbd_find_endpoint(device, RT_NULL, setup->wIndex);
            if(USB_EP_HALT == setup->wValue && ep->stalled == RT_TRUE)
            {
                rt_usbd_clear_feature(device, setup->wValue, setup->wIndex);
                dcd_ep0_send_status(dcd);
                ep->stalled = RT_FALSE;

                for (node = ep->request_list.next; node != &ep->request_list; node = node->next)
                {
                    req = (uio_request_t)rt_list_entry(node, struct uio_request, list);
                    rt_usbd_io_request(device, ep, req);
                    RT_DEBUG_LOG(RT_DEBUG_USB, ("fired a request\n"));
                }

                rt_list_init(&ep->request_list);
            }
        }
        break;
        case USB_REQ_SET_FEATURE:
        {
            uep_t ep;

            if(USB_EP_HALT == setup->wValue)
            {
                ep = rt_usbd_find_endpoint(device, RT_NULL, setup->wIndex);
                ep->stalled = RT_TRUE;
                rt_usbd_set_feature(device, setup->wValue, setup->wIndex);
                dcd_ep0_send_status(dcd);
            }
        }
        break;
        case USB_REQ_SYNCH_FRAME:
            break;
        default:
            rt_kprintf("unknown endpoint request\n");
            rt_usbd_ep0_set_stall(device);
            break;
        }
        break;
    case USB_REQ_TYPE_OTHER:
        rt_kprintf("unknown other type request\n");
        rt_usbd_ep0_set_stall(device);
        break;
    default:
        rt_kprintf("unknown type request\n");
        rt_usbd_ep0_set_stall(device);
        break;
    }

    return RT_EOK;
}

/**
 * This function will handle function bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful, -RT_ERROR on invalid bRequest.
 */
static rt_err_t _function_request(udevice_t device, ureq_t setup)
{
    uintf_t intf;
    ufunction_t func;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    /* verify bRequest wValue */
    if(setup->wIndex > device->curr_cfg->cfg_desc.bNumInterfaces)
    {
        rt_usbd_ep0_set_stall(device);
        return -RT_ERROR;
    }

    switch(setup->request_type & USB_REQ_TYPE_RECIPIENT_MASK)
    {
    case USB_REQ_TYPE_INTERFACE:
        intf = rt_usbd_find_interface(device, setup->wIndex & 0xFF, &func);
        if(intf == RT_NULL)
        {
            rt_kprintf("unkwown interface request\n");
            rt_usbd_ep0_set_stall(device);
        }
        else
        {
            intf->handler(func, setup);
        }
        break;
    case USB_REQ_TYPE_ENDPOINT:
        break;
    default:
        rt_kprintf("unknown function request type\n");
        rt_usbd_ep0_set_stall(device);
        break;
    }

    return RT_EOK;
}
static rt_err_t _vendor_request(udevice_t device, ureq_t setup)
{
    static rt_uint8_t * usb_comp_id_desc = RT_NULL;
    static rt_uint32_t  usb_comp_id_desc_size = 0;
    usb_os_func_comp_id_desc_t func_comp_id_desc;
    uintf_t intf;
    ufunction_t func;
    switch(setup->bRequest)
    {
        case 'A':
        switch(setup->wIndex)
        {
            case 0x04:
                if(rt_list_len(&device->os_comp_id_desc->func_desc) == 0)
                {
                    rt_usbd_ep0_set_stall(device);
                    return RT_EOK;
                }
                if(usb_comp_id_desc == RT_NULL)
                {
                    rt_uint8_t * pusb_comp_id_desc;
                    rt_list_t *p;
                    usb_comp_id_desc_size = sizeof(struct usb_os_header_comp_id_descriptor) +
                    (sizeof(struct usb_os_function_comp_id_descriptor)-sizeof(rt_list_t))*rt_list_len(&device->os_comp_id_desc->func_desc);

                    usb_comp_id_desc = (rt_uint8_t *)rt_malloc(usb_comp_id_desc_size);
                    RT_ASSERT(usb_comp_id_desc != RT_NULL);
                    device->os_comp_id_desc->head_desc.dwLength = usb_comp_id_desc_size;
                    pusb_comp_id_desc = usb_comp_id_desc;
                    rt_memcpy((void *)pusb_comp_id_desc,(void *)&device->os_comp_id_desc->head_desc,sizeof(struct usb_os_header_comp_id_descriptor));
                    pusb_comp_id_desc += sizeof(struct usb_os_header_comp_id_descriptor);

                    for (p = device->os_comp_id_desc->func_desc.next; p != &device->os_comp_id_desc->func_desc; p = p->next)
                    {
                        func_comp_id_desc = rt_list_entry(p,struct usb_os_function_comp_id_descriptor,list);
                        rt_memcpy(pusb_comp_id_desc,(void *)&func_comp_id_desc->bFirstInterfaceNumber,
                        sizeof(struct usb_os_function_comp_id_descriptor)-sizeof(rt_list_t));
                        pusb_comp_id_desc += sizeof(struct usb_os_function_comp_id_descriptor)-sizeof(rt_list_t);
                    }
                }
                rt_usbd_ep0_write(device, (void*)usb_comp_id_desc, setup->wLength);
            break;
            case 0x05:
                intf = rt_usbd_find_interface(device, setup->wValue & 0xFF, &func);
                if(intf != RT_NULL)
                {
                    intf->handler(func, setup);
                }
                break;
        }

        break;
    }
    return RT_EOK;
}
static rt_err_t _dump_setup_packet(ureq_t setup)
{
    RT_DEBUG_LOG(RT_DEBUG_USB, ("[\n"));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("  setup_request : 0x%x\n",
                                setup->request_type));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("  value         : 0x%x\n", setup->wValue));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("  length        : 0x%x\n", setup->wLength));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("  index         : 0x%x\n", setup->wIndex));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("  request       : 0x%x\n", setup->bRequest));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("]\n"));

    return RT_EOK;
}

/**
 * This function will handle setup bRequest.
 *
 * @param device the usb device object.
 * @param setup the setup bRequest.
 *
 * @return RT_EOK on successful, -RT_ERROR on invalid bRequest.
 */
static rt_err_t _setup_request(udevice_t device, ureq_t setup)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    _dump_setup_packet(setup);

    switch((setup->request_type & USB_REQ_TYPE_MASK))
    {
    case USB_REQ_TYPE_STANDARD:
        _standard_request(device, setup);
        break;
    case USB_REQ_TYPE_CLASS:
        _function_request(device, setup);
        break;
    case USB_REQ_TYPE_VENDOR:
        _vendor_request(device, setup);
        break;
    default:
        rt_kprintf("unknown setup request type\n");
        rt_usbd_ep0_set_stall(device);
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * This function will hanle data notify event.
 *
 * @param device the usb device object.
 * @param ep_msg the endpoint message.
 *
 * @return RT_EOK.
 */
static rt_err_t _data_notify(udevice_t device, struct ep_msg* ep_msg)
{
    uep_t ep;
    ufunction_t func;
    rt_size_t size = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(ep_msg != RT_NULL);

    if (device->state != USB_STATE_CONFIGURED)
    {
        return -RT_ERROR;
    }

    ep = rt_usbd_find_endpoint(device, &func, ep_msg->ep_addr);
    if(ep == RT_NULL)
    {
        rt_kprintf("invalid endpoint\n");
        return -RT_ERROR;
    }

    if(EP_ADDRESS(ep) & USB_DIR_IN)
    {
        size = ep_msg->size;
        if(ep->request.remain_size >= EP_MAXPACKET(ep))
        {
            dcd_ep_write(device->dcd, EP_ADDRESS(ep), ep->request.buffer, EP_MAXPACKET(ep));
            ep->request.remain_size -= EP_MAXPACKET(ep);
            ep->request.buffer += EP_MAXPACKET(ep);
        }
        else if(ep->request.remain_size > 0)
        {
            dcd_ep_write(device->dcd, EP_ADDRESS(ep), ep->request.buffer, ep->request.remain_size);
            ep->request.remain_size = 0;
        }
        else
        {
            EP_HANDLER(ep, func, size);
        }
    }
    else
    {
        size = ep_msg->size;
        if(ep->request.remain_size == 0)
        {
            return RT_EOK;
        }

        if(size == 0)
        {
            size = dcd_ep_read(device->dcd, EP_ADDRESS(ep), ep->request.buffer);
        }
        ep->request.remain_size -= size;
        ep->request.buffer += size;

        if(ep->request.req_type == UIO_REQUEST_READ_BEST)
        {
            EP_HANDLER(ep, func, size);
        }
        else if(ep->request.remain_size == 0)
        {
            EP_HANDLER(ep, func, ep->request.size);
        }
        else
        {
            dcd_ep_read_prepare(device->dcd, EP_ADDRESS(ep), ep->request.buffer, ep->request.remain_size > EP_MAXPACKET(ep) ? EP_MAXPACKET(ep) : ep->request.remain_size);
        }
    }

    return RT_EOK;
}

static rt_err_t _ep0_out_notify(udevice_t device, struct ep_msg* ep_msg)
{
    uep_t ep0;
    rt_size_t size;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(ep_msg != RT_NULL);
    RT_ASSERT(device->dcd != RT_NULL);

    ep0 = &device->dcd->ep0;
    size = ep_msg->size;

    if(ep0->request.remain_size == 0)
    {
        return RT_EOK;
    }
    if(size == 0)
    {
        size = dcd_ep_read(device->dcd, EP0_OUT_ADDR, ep0->request.buffer);
        if(size == 0)
        {
            return RT_EOK;
        }
    }

    ep0->request.remain_size -= size;
    ep0->request.buffer += size;
    if(ep0->request.remain_size == 0)
    {
        /* invoke callback */
        if(ep0->rx_indicate != RT_NULL)
        {
            ep0->rx_indicate(device, size);
        }
    }
    else
    {
        rt_usbd_ep0_read(device, ep0->request.buffer, ep0->request.remain_size,ep0->rx_indicate);
    }

    return RT_EOK;
}

/**
 * This function will notity sof event to all of function.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK.
 */
static rt_err_t _sof_notify(udevice_t device)
{
    struct rt_list_node *i;
    ufunction_t func;

    RT_ASSERT(device != RT_NULL);

    /* to notity every function that sof event comes */
    for (i=device->curr_cfg->func_list.next;
            i!=&device->curr_cfg->func_list; i=i->next)
    {
        func = (ufunction_t)rt_list_entry(i, struct ufunction, list);
        if(func->ops->sof_handler != RT_NULL)
            func->ops->sof_handler(func);
    }

    return RT_EOK;
}

/**
 * This function will disable all USB functions.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK.
 */
static rt_err_t _stop_notify(udevice_t device)
{
    struct rt_list_node *i;
    ufunction_t func;

    RT_ASSERT(device != RT_NULL);

    /* to notity every function */
    for (i  = device->curr_cfg->func_list.next;
         i != &device->curr_cfg->func_list;
         i  = i->next)
    {
        func = (ufunction_t)rt_list_entry(i, struct ufunction, list);
        FUNC_DISABLE(func);
    }

    return RT_EOK;
}

static rt_size_t rt_usbd_ep_write(udevice_t device, uep_t ep, void *buffer, rt_size_t size)
{
    rt_uint16_t maxpacket;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->dcd != RT_NULL);
    RT_ASSERT(ep != RT_NULL);

    rt_enter_critical();
    maxpacket = EP_MAXPACKET(ep);
    if(ep->request.remain_size >= maxpacket)
    {
        dcd_ep_write(device->dcd, EP_ADDRESS(ep), ep->request.buffer, maxpacket);
        ep->request.remain_size -= maxpacket;
        ep->request.buffer += maxpacket;
    }
    else
    {
        dcd_ep_write(device->dcd, EP_ADDRESS(ep), ep->request.buffer,
            ep->request.remain_size);
        ep->request.remain_size = 0;
    }
    rt_exit_critical();
    return size;
}

static rt_size_t rt_usbd_ep_read_prepare(udevice_t device, uep_t ep, void *buffer, rt_size_t size)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->dcd != RT_NULL);
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    return dcd_ep_read_prepare(device->dcd, EP_ADDRESS(ep), buffer, size > EP_MAXPACKET(ep) ? EP_MAXPACKET(ep) : size);
}

/**
 * This function will create an usb device object.
 *
 * @param ustring the usb string array to contain string descriptor.
 *
 * @return an usb device object on success, RT_NULL on fail.
 */
udevice_t rt_usbd_device_new(void)
{
    udevice_t udevice;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_device_new\n"));

    /* allocate memory for the object */
    udevice = (udevice_t)rt_malloc(sizeof(struct udevice));
    if(udevice == RT_NULL)
    {
        rt_kprintf("alloc memory failed\n");
        return RT_NULL;
    }
    rt_memset(udevice, 0, sizeof(struct udevice));

    /* to initialize configuration list */
    rt_list_init(&udevice->cfg_list);

    /* insert the device object to device list */
    rt_list_insert_before(&device_list, &udevice->list);

    return udevice;
}

/**
 * This function will set usb device string description.
 *
 * @param device the usb device object.
 * @param ustring pointer to string pointer array.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_device_set_string(udevice_t device, const char** ustring)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(ustring != RT_NULL);

    /* set string descriptor array to the device object */
    device->str = ustring;

    return RT_EOK;
}

/**
 * This function will set usb device interface string description.
 *
 * @param device the usb device object.
 * @param index of interface string
 * @param string pointer to interface string description.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_device_set_interface_string(udevice_t device, int index, const char* string)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(string != RT_NULL);
    RT_ASSERT(index < MAX_INTF_STR);

    /* set string descriptor array to the device object */
    device->str_intf[index] = string;

    return RT_EOK;
}

rt_err_t rt_usbd_device_set_os_comp_id_desc(udevice_t device, usb_os_comp_id_desc_t os_comp_id_desc)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(os_comp_id_desc != RT_NULL);

    /* set string descriptor array to the device object */
    device->os_comp_id_desc = os_comp_id_desc;
    rt_list_init(&device->os_comp_id_desc->func_desc);
    return RT_EOK;
}

rt_err_t rt_usbd_device_set_qualifier(udevice_t device, struct usb_qualifier_descriptor* qualifier)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(qualifier != RT_NULL);

    device->dev_qualifier = qualifier;

    return RT_EOK;
}

/**
 * This function will set an usb controller driver to a device.
 *
 * @param device the usb device object.
 * @param dcd the usb device controller driver.
 *
 * @return RT_EOK on successful.
 */
rt_err_t rt_usbd_device_set_controller(udevice_t device, udcd_t dcd)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(dcd != RT_NULL);

    /* set usb device controller driver to the device */
    device->dcd = dcd;

    return RT_EOK;
}

/**
 * This function will set an usb device descriptor to a device.
 *
 * @param device the usb device object.
 * @param dev_desc the usb device descriptor.
 *
 * @return RT_EOK on successful.
 */
rt_err_t rt_usbd_device_set_descriptor(udevice_t device, udev_desc_t dev_desc)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(dev_desc != RT_NULL);

    /* copy the usb device descriptor to the device */
    rt_memcpy((void *)&device->dev_desc, (void *)dev_desc, USB_DESC_LENGTH_DEVICE);

    return RT_EOK;
}

/**
 * This function will create an usb configuration object.
 *
 * @param none.
 *
 * @return an usb configuration object.
 */
uconfig_t rt_usbd_config_new(void)
{
    uconfig_t cfg;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_config_new\n"));

    /* allocate memory for the object */
    cfg = (uconfig_t)rt_malloc(sizeof(struct uconfig));
    if(cfg == RT_NULL)
    {
        rt_kprintf("alloc memory failed\n");
        return RT_NULL;
    }
    rt_memset(cfg, 0, sizeof(struct uconfig));

    /* set default wValue */
    cfg->cfg_desc.bLength = USB_DESC_LENGTH_CONFIG;
    cfg->cfg_desc.type = USB_DESC_TYPE_CONFIGURATION;
    cfg->cfg_desc.wTotalLength = USB_DESC_LENGTH_CONFIG;
    cfg->cfg_desc.bmAttributes = 0xC0;
    cfg->cfg_desc.MaxPower = 0x32;

    /* to initialize function object list */
    rt_list_init(&cfg->func_list);

    return cfg;
}

/**
 * This function will create an usb interface object.
 *
 * @param device the usb device object.
 * @handler the callback handler of object
 *
 * @return an usb interface object on success, RT_NULL on fail.
 */
uintf_t rt_usbd_interface_new(udevice_t device, uintf_handler_t handler)
{
    uintf_t intf;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_interface_new\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* allocate memory for the object */
    intf = (uintf_t)rt_malloc(sizeof(struct uinterface));
    if(intf == RT_NULL)
    {
        rt_kprintf("alloc memory failed\n");
        return RT_NULL;
    }
    intf->intf_num = device->nr_intf;
    device->nr_intf++;
    intf->handler = handler;
    intf->curr_setting = RT_NULL;

    /* to initialize the alternate setting object list */
    rt_list_init(&intf->setting_list);

    return intf;
}

/**
 * This function will create an usb alternate setting object.
 *
 * @param intf_desc the interface descriptor.
 * @desc_size the size of the interface descriptor.
 *
 * @return an usb alternate setting object on success, RT_NULL on fail.
 */
ualtsetting_t rt_usbd_altsetting_new(rt_size_t desc_size)
{
    ualtsetting_t setting;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_altsetting_new\n"));

    /* parameter check */
    RT_ASSERT(desc_size > 0);

    /* allocate memory for the object */
    setting = (ualtsetting_t)rt_malloc(sizeof(struct ualtsetting));
    if(setting == RT_NULL)
    {
        rt_kprintf("alloc memory failed\n");
        return RT_NULL;
    }
    /* allocate memory for the desc */
    setting->desc = rt_malloc(desc_size);
    if (setting->desc == RT_NULL)
    {
        rt_kprintf("alloc desc memory failed\n");
        rt_free(setting);
        return RT_NULL;
    }

    setting->desc_size = desc_size;
    setting->intf_desc = RT_NULL;

    /* to initialize endpoint list */
    rt_list_init(&setting->ep_list);

    return setting;
}

/**
 * This function will config an desc in alternate setting object.
 *
 * @param setting the altsetting to be config.
 * @param desc use it to init desc in setting.
 * @param intf_pos the offset of interface descriptor in desc.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_altsetting_config_descriptor(ualtsetting_t setting, const void* desc, rt_off_t intf_pos)
{
    RT_ASSERT(setting != RT_NULL);
    RT_ASSERT(setting->desc !=RT_NULL);

    rt_memcpy(setting->desc, desc, setting->desc_size);
    setting->intf_desc = (uintf_desc_t)((char*)setting->desc + intf_pos);

    return RT_EOK;
}

/**
 * This function will create an usb function object.
 *
 * @param device the usb device object.
 * @param dev_desc the device descriptor.
 * @param ops the operation set.
 *
 * @return an usb function object on success, RT_NULL on fail.
 */
ufunction_t rt_usbd_function_new(udevice_t device, udev_desc_t dev_desc,
                              ufunction_ops_t ops)
{
    ufunction_t func;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_function_new\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(dev_desc != RT_NULL);

    /* allocate memory for the object */
    func = (ufunction_t)rt_malloc(sizeof(struct ufunction));
    if(func == RT_NULL)
    {
        rt_kprintf("alloc memory failed\n");
        return RT_NULL;
    }
    func->dev_desc = dev_desc;
    func->ops = ops;
    func->device = device;
    func->enabled = RT_FALSE;

    /* to initialize interface list */
    rt_list_init(&func->intf_list);

    return func;
}

/**
 * This function will create an usb endpoint object.
 *
 * @param ep_desc the endpoint descriptor.
 * @handler the callback handler of object
 *
 * @return an usb endpoint object on success, RT_NULL on fail.
 */
uep_t rt_usbd_endpoint_new(uep_desc_t ep_desc, udep_handler_t handler)
{
    uep_t ep;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_endpoint_new\n"));

    /* parameter check */
    RT_ASSERT(ep_desc != RT_NULL);

    /* allocate memory for the object */
    ep = (uep_t)rt_malloc(sizeof(struct uendpoint));
    if(ep == RT_NULL)
    {
        rt_kprintf("alloc memory failed\n");
        return RT_NULL;
    }
    ep->ep_desc = ep_desc;
    ep->handler = handler;
    ep->buffer  = RT_NULL;
    ep->stalled = RT_FALSE;
    rt_list_init(&ep->request_list);

    return ep;
}

/**
 * This function will find an usb device object.
 *
 * @dcd usd device controller driver.
 *
 * @return an usb device object on found or RT_NULL on not found.
 */
udevice_t rt_usbd_find_device(udcd_t dcd)
{
    struct rt_list_node* node;
    udevice_t device;

    /* parameter check */
    RT_ASSERT(dcd != RT_NULL);

    /* search a device in the the device list */
    for (node = device_list.next; node != &device_list; node = node->next)
    {
        device = (udevice_t)rt_list_entry(node, struct udevice, list);
        if(device->dcd == dcd) return device;
    }

    rt_kprintf("can't find device\n");
    return RT_NULL;
}

/**
 * This function will find an usb configuration object.
 *
 * @param device the usb device object.
 * @param wValue the configuration number.
 *
 * @return an usb configuration object on found or RT_NULL on not found.
 */
uconfig_t rt_usbd_find_config(udevice_t device, rt_uint8_t value)
{
    struct rt_list_node* node;
    uconfig_t cfg = RT_NULL;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_find_config\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value <= device->dev_desc.bNumConfigurations);

    /* search a configration in the the device */
    for (node = device->cfg_list.next; node != &device->cfg_list; node = node->next)
    {
        cfg = (uconfig_t)rt_list_entry(node, struct udevice, list);
        if(cfg->cfg_desc.bConfigurationValue == value)
        {
            return cfg;
        }
    }

    rt_kprintf("can't find configuration %d\n", value);
    return RT_NULL;
}

/**
 * This function will find an usb interface object.
 *
 * @param device the usb device object.
 * @param wValue the interface number.
 *
 * @return an usb configuration object on found or RT_NULL on not found.
 */
uintf_t rt_usbd_find_interface(udevice_t device, rt_uint8_t value, ufunction_t *pfunc)
{
    struct rt_list_node *i, *j;
    ufunction_t func;
    uintf_t intf;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_find_interface\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value < device->nr_intf);

    /* search an interface in the current configuration */
    for (i=device->curr_cfg->func_list.next;
            i!=&device->curr_cfg->func_list; i=i->next)
    {
        func = (ufunction_t)rt_list_entry(i, struct ufunction, list);
        for(j=func->intf_list.next; j!=&func->intf_list; j=j->next)
        {
            intf = (uintf_t)rt_list_entry(j, struct uinterface, list);
            if(intf->intf_num == value)
            {
                if (pfunc != RT_NULL)
                    *pfunc = func;
                return intf;
            }
        }
    }

    rt_kprintf("can't find interface %d\n", value);
    return RT_NULL;
}

/**
 * This function will find an usb interface alternate setting object.
 *
 * @param device the usb device object.
 * @param wValue the alternate setting number.
 *
 * @return an usb interface alternate setting object on found or RT_NULL on not found.
 */
ualtsetting_t rt_usbd_find_altsetting(uintf_t intf, rt_uint8_t value)
{
    struct rt_list_node *i;
    ualtsetting_t setting;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_find_altsetting\n"));

    /* parameter check */
    RT_ASSERT(intf != RT_NULL);

    if(intf->curr_setting != RT_NULL)
    {
        /* if the wValue equal to the current alternate setting, then do not search */
        if(intf->curr_setting->intf_desc->bAlternateSetting == value)
            return intf->curr_setting;
    }

    /* search a setting in the alternate setting list */
    for(i=intf->setting_list.next; i!=&intf->setting_list; i=i->next)
    {
        setting =(ualtsetting_t)rt_list_entry(i, struct ualtsetting, list);
        if(setting->intf_desc->bAlternateSetting == value)
            return setting;
    }

    rt_kprintf("can't find alternate setting %d\n", value);
    return RT_NULL;
}

/**
 * This function will find an usb endpoint object.
 *
 * @param device the usb device object.
 * @param ep_addr endpoint address.
 *
 * @return an usb endpoint object on found or RT_NULL on not found.
 */
uep_t rt_usbd_find_endpoint(udevice_t device, ufunction_t* pfunc, rt_uint8_t ep_addr)
{
    uep_t ep;
    struct rt_list_node *i, *j, *k;
    ufunction_t func;
    uintf_t intf;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* search a endpoint in the current configuration */
    for (i=device->curr_cfg->func_list.next; i!=&device->curr_cfg->func_list; i=i->next)
    {
        func = (ufunction_t)rt_list_entry(i, struct ufunction, list);
        for(j=func->intf_list.next; j!=&func->intf_list; j=j->next)
        {
            intf = (uintf_t)rt_list_entry(j, struct uinterface, list);
            for(k=intf->curr_setting->ep_list.next;
                    k!=&intf->curr_setting->ep_list; k=k->next)
            {
                ep = (uep_t)rt_list_entry(k, struct uendpoint, list);
                if(EP_ADDRESS(ep) == ep_addr)
                {
                    if (pfunc != RT_NULL)
                        *pfunc = func;
                    return ep;
                }
            }
        }
    }

    rt_kprintf("can't find endpoint 0x%x\n", ep_addr);
    return RT_NULL;
}

/**
 * This function will add a configuration to an usb device.
 *
 * @param device the usb device object.
 * @param cfg the configuration object.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_device_add_config(udevice_t device, uconfig_t cfg)
{
    struct rt_list_node *i, *j, *k, *m;
    ufunction_t func;
    uintf_t intf;
    ualtsetting_t altsetting;
    uep_t ep;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_device_add_config\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    /* set configuration number to the configuration descriptor */
    cfg->cfg_desc.bConfigurationValue = device->dev_desc.bNumConfigurations + 1;
    device->dev_desc.bNumConfigurations++;

    for (i=cfg->func_list.next; i!=&cfg->func_list; i=i->next)
    {
        func = (ufunction_t)rt_list_entry(i, struct ufunction, list);

        for(j=func->intf_list.next; j!=&func->intf_list; j=j->next)
        {
            intf = (uintf_t)rt_list_entry(j, struct uinterface, list);
            cfg->cfg_desc.bNumInterfaces++;

            for(k=intf->setting_list.next; k!=&intf->setting_list;k=k->next)
            {
                altsetting = (ualtsetting_t)rt_list_entry(k, struct ualtsetting, list);

                /* allocate address for every endpoint in the interface alternate setting */
                for(m=altsetting->ep_list.next; m!=&altsetting->ep_list; m=m->next)
                {
                    ep = (uep_t)rt_list_entry(m, struct uendpoint, list);
                    if(rt_usbd_ep_assign(device, ep) != RT_EOK)
                    {
                        rt_kprintf("endpoint assign error\n");
                    }
                }

                /* construct complete configuration descriptor */
                rt_memcpy((void*)&cfg->cfg_desc.data[cfg->cfg_desc.wTotalLength - USB_DESC_LENGTH_CONFIG],
                            (void*)altsetting->desc,
                            altsetting->desc_size);
                cfg->cfg_desc.wTotalLength += altsetting->desc_size;
            }
        }
    }

    /* insert the configuration to the list */
    rt_list_insert_before(&device->cfg_list, &cfg->list);

    return RT_EOK;
}

/**
 * This function will add a function to a configuration.
 *
 * @param cfg the configuration object.
 * @param func the function object.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_config_add_function(uconfig_t cfg, ufunction_t func)
{
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_config_add_function\n"));

    /* parameter check */
    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(func != RT_NULL);

    /* insert the function to the list */
    rt_list_insert_before(&cfg->func_list, &func->list);

    return RT_EOK;
}

/**
 * This function will add an interface to a function.
 *
 * @param func the function object.
 * @param intf the interface object.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_function_add_interface(ufunction_t func, uintf_t intf)
{

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_function_add_interface\n"));

    /* parameter check */
    RT_ASSERT(func != RT_NULL);
    RT_ASSERT(intf != RT_NULL);

    /* insert the interface to the list */
    rt_list_insert_before(&func->intf_list, &intf->list);

    return RT_EOK;
}

/**
 * This function will add an alternate setting to an interface.
 *
 * @param intf the interface object.
 * @param setting the alternate setting object.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_interface_add_altsetting(uintf_t intf, ualtsetting_t setting)
{
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_interface_add_altsetting\n"));

    /* parameter check */
    RT_ASSERT(intf != RT_NULL);
    RT_ASSERT(setting != RT_NULL);

    setting->intf_desc->bInterfaceNumber = intf->intf_num;

    /* insert the alternate setting to the list */
    rt_list_insert_before(&intf->setting_list, &setting->list);

    return RT_EOK;
}

/**
 * This function will add an endpoint to an alternate setting.
 *
 * @param setting the alternate setting object.
 * @param ep the endpoint object.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_altsetting_add_endpoint(ualtsetting_t setting, uep_t ep)
{
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_altsetting_add_endpoint\n"));

    /* parameter check */
    RT_ASSERT(setting != RT_NULL);
    RT_ASSERT(ep != RT_NULL);

    /* insert the endpoint to the list */
    rt_list_insert_before(&setting->ep_list, &ep->list);

    return RT_EOK;
}

rt_err_t rt_usbd_os_comp_id_desc_add_os_func_comp_id_desc(usb_os_comp_id_desc_t os_comp_id_desc, usb_os_func_comp_id_desc_t os_func_comp_id_desc)
{
    RT_ASSERT(os_comp_id_desc != RT_NULL);
    RT_ASSERT(os_func_comp_id_desc != RT_NULL);
    rt_list_insert_before(&os_comp_id_desc->func_desc, &os_func_comp_id_desc->list);
    os_comp_id_desc->head_desc.bCount++;
    return RT_EOK;
}

/**
 * This function will set an alternate setting for an interface.
 *
 * @param intf_desc the interface descriptor.
 * @param wValue the alternate setting number.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_set_altsetting(uintf_t intf, rt_uint8_t value)
{
    ualtsetting_t setting;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_set_altsetting\n"));

    /* parameter check */
    RT_ASSERT(intf != RT_NULL);

    /* find an alternate setting */
    setting = rt_usbd_find_altsetting(intf, value);

    /* set as current alternate setting */
    intf->curr_setting = setting;

    return RT_EOK;
}

/**
 * This function will set a configuration for an usb device.
 *
 * @param device the usb device object.
 * @param wValue the configuration number.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_set_config(udevice_t device, rt_uint8_t value)
{
    uconfig_t cfg;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_set_config\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value <= device->dev_desc.bNumConfigurations);

    /* find a configuration */
    cfg = rt_usbd_find_config(device, value);

    /* set as current configuration */
    device->curr_cfg = cfg;

    dcd_set_config(device->dcd, value);

    return RT_TRUE;
}

/**
 * This function will bRequest an IO transaction.
 *
 * @param device the usb device object.
 * @param ep the endpoint object.
 * @param req IO bRequest.
 *
 * @return RT_EOK.
 */
rt_size_t rt_usbd_io_request(udevice_t device, uep_t ep, uio_request_t req)
{
    rt_size_t size = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(req != RT_NULL);

    if(ep->stalled == RT_FALSE)
    {
        switch(req->req_type)
        {
        case UIO_REQUEST_READ_BEST:
        case UIO_REQUEST_READ_FULL:
            ep->request.remain_size = ep->request.size;
            size = rt_usbd_ep_read_prepare(device, ep, req->buffer, req->size);
            break;
        case UIO_REQUEST_WRITE:
            ep->request.remain_size = ep->request.size;
            size = rt_usbd_ep_write(device, ep, req->buffer, req->size);
            break;
        default:
            rt_kprintf("unknown request type\n");
            break;
        }
    }
    else
    {
        rt_list_insert_before(&ep->request_list, &req->list);
        RT_DEBUG_LOG(RT_DEBUG_USB, ("suspend a request\n"));
    }

    return size;
}

/**
 * This function will set feature for an usb device.
 *
 * @param device the usb device object.
 * @param wValue the configuration number.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_set_feature(udevice_t device, rt_uint16_t value, rt_uint16_t index)
{
    RT_ASSERT(device != RT_NULL);

    if (value == USB_FEATURE_DEV_REMOTE_WAKEUP)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("set feature remote wakeup\n"));
    }
    else if (value == USB_FEATURE_ENDPOINT_HALT)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("set feature stall\n"));
        dcd_ep_set_stall(device->dcd, (rt_uint32_t)(index & 0xFF));
    }

    return RT_EOK;
}

/**
 * This function will clear feature for an usb device.
 *
 * @param device the usb device object.
 * @param wValue the configuration number.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_clear_feature(udevice_t device, rt_uint16_t value, rt_uint16_t index)
{
    RT_ASSERT(device != RT_NULL);

    if (value == USB_FEATURE_DEV_REMOTE_WAKEUP)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("clear feature remote wakeup\n"));
    }
    else if (value == USB_FEATURE_ENDPOINT_HALT)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("clear feature stall\n"));
        dcd_ep_clear_stall(device->dcd, (rt_uint32_t)(index & 0xFF));
    }

    return RT_EOK;
}

rt_err_t rt_usbd_ep0_set_stall(udevice_t device)
{
    RT_ASSERT(device != RT_NULL);

    return dcd_ep_set_stall(device->dcd, 0);
}

rt_err_t rt_usbd_ep0_clear_stall(udevice_t device)
{
    RT_ASSERT(device != RT_NULL);

    return dcd_ep_clear_stall(device->dcd, 0);
}

rt_err_t rt_usbd_ep_set_stall(udevice_t device, uep_t ep)
{
    rt_err_t ret;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    ret = dcd_ep_set_stall(device->dcd, EP_ADDRESS(ep));
    if(ret == RT_EOK)
    {
        ep->stalled = RT_TRUE;
    }

    return ret;
}

rt_err_t rt_usbd_ep_clear_stall(udevice_t device, uep_t ep)
{
    rt_err_t ret;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    ret = dcd_ep_clear_stall(device->dcd, EP_ADDRESS(ep));
    if(ret == RT_EOK)
    {
        ep->stalled = RT_FALSE;
    }

    return ret;
}

static rt_err_t rt_usbd_ep_assign(udevice_t device, uep_t ep)
{
    int i = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->dcd != RT_NULL);
    RT_ASSERT(device->dcd->ep_pool != RT_NULL);
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    while(device->dcd->ep_pool[i].addr != 0xFF)
    {
        if(device->dcd->ep_pool[i].status == ID_UNASSIGNED &&
            ep->ep_desc->bmAttributes == device->dcd->ep_pool[i].type && (EP_ADDRESS(ep) & 0x80) == device->dcd->ep_pool[i].dir)
        {
            EP_ADDRESS(ep) |= device->dcd->ep_pool[i].addr;
            ep->id = &device->dcd->ep_pool[i];
            device->dcd->ep_pool[i].status = ID_ASSIGNED;

            RT_DEBUG_LOG(RT_DEBUG_USB, ("assigned %d\n", device->dcd->ep_pool[i].addr));
            return RT_EOK;
        }

        i++;
    }

    return -RT_ERROR;
}

rt_err_t rt_usbd_ep_unassign(udevice_t device, uep_t ep)
{
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->dcd != RT_NULL);
    RT_ASSERT(device->dcd->ep_pool != RT_NULL);
    RT_ASSERT(ep != RT_NULL);
    RT_ASSERT(ep->ep_desc != RT_NULL);

    ep->id->status = ID_UNASSIGNED;

    return RT_EOK;
}

rt_err_t rt_usbd_ep0_setup_handler(udcd_t dcd, struct urequest* setup)
{
    struct udev_msg msg;
    rt_size_t size;

    RT_ASSERT(dcd != RT_NULL);

    if(setup == RT_NULL)
    {
        size = dcd_ep_read(dcd, EP0_OUT_ADDR, (void*)&msg.content.setup);
        if(size != sizeof(struct urequest))
        {
            rt_kprintf("read setup packet error\n");
            return -RT_ERROR;
        }
    }
    else
    {
        rt_memcpy((void*)&msg.content.setup, (void*)setup, sizeof(struct urequest));
    }

    msg.type = USB_MSG_SETUP_NOTIFY;
    msg.dcd = dcd;
    rt_usbd_event_signal(&msg);

    return RT_EOK;
}

rt_err_t rt_usbd_ep0_in_handler(udcd_t dcd)
{
    rt_int32_t remain, mps;

    RT_ASSERT(dcd != RT_NULL);

    if (dcd->stage != STAGE_DIN)
        return RT_EOK;

    mps = dcd->ep0.id->maxpacket;
    dcd->ep0.request.remain_size -= mps;
    remain = dcd->ep0.request.remain_size;

    if (remain > 0)
    {
        if (remain >= mps)
        {
            remain = mps;
        }

        dcd->ep0.request.buffer += mps;
        dcd_ep_write(dcd, EP0_IN_ADDR, dcd->ep0.request.buffer, remain);
    }
    else
    {
        /* last packet is MPS multiple, so send ZLP packet */
        if ((remain == 0) && (dcd->ep0.request.size > 0))
        {
            dcd->ep0.request.size = 0;
            dcd_ep_write(dcd, EP0_IN_ADDR, RT_NULL, 0);
        }
        else
        {
            /* receive status */
            dcd->stage = STAGE_STATUS_OUT;
            dcd_ep_read_prepare(dcd, EP0_OUT_ADDR, RT_NULL, 0);
        }
    }

    return RT_EOK;
}

rt_err_t rt_usbd_ep0_out_handler(udcd_t dcd, rt_size_t size)
{
    struct udev_msg msg;

    RT_ASSERT(dcd != RT_NULL);

    msg.type = USB_MSG_EP0_OUT;
    msg.dcd = dcd;
    msg.content.ep_msg.size = size;
    rt_usbd_event_signal(&msg);

    return RT_EOK;
}

rt_err_t rt_usbd_ep_in_handler(udcd_t dcd, rt_uint8_t address, rt_size_t size)
{
    struct udev_msg msg;

    RT_ASSERT(dcd != RT_NULL);

    msg.type = USB_MSG_DATA_NOTIFY;
    msg.dcd = dcd;
    msg.content.ep_msg.ep_addr = address;
    msg.content.ep_msg.size = size;
    rt_usbd_event_signal(&msg);

    return RT_EOK;
}

rt_err_t rt_usbd_ep_out_handler(udcd_t dcd, rt_uint8_t address, rt_size_t size)
{
    struct udev_msg msg;

    RT_ASSERT(dcd != RT_NULL);

    msg.type = USB_MSG_DATA_NOTIFY;
    msg.dcd = dcd;
    msg.content.ep_msg.ep_addr = address;
    msg.content.ep_msg.size = size;
    rt_usbd_event_signal(&msg);

    return RT_EOK;
}

rt_err_t rt_usbd_reset_handler(udcd_t dcd)
{
    struct udev_msg msg;

    RT_ASSERT(dcd != RT_NULL);

    msg.type = USB_MSG_RESET;
    msg.dcd = dcd;
    rt_usbd_event_signal(&msg);

    return RT_EOK;
}

rt_err_t rt_usbd_connect_handler(udcd_t dcd)
{
    struct udev_msg msg;

    RT_ASSERT(dcd != RT_NULL);

    msg.type = USB_MSG_PLUG_IN;
    msg.dcd = dcd;
    rt_usbd_event_signal(&msg);

    return RT_EOK;
}

rt_err_t rt_usbd_disconnect_handler(udcd_t dcd)
{
    struct udev_msg msg;

    RT_ASSERT(dcd != RT_NULL);

    msg.type = USB_MSG_PLUG_OUT;
    msg.dcd = dcd;
    rt_usbd_event_signal(&msg);

    return RT_EOK;
}

rt_err_t rt_usbd_sof_handler(udcd_t dcd)
{
    struct udev_msg msg;

    RT_ASSERT(dcd != RT_NULL);

    msg.type = USB_MSG_SOF;
    msg.dcd = dcd;
    rt_usbd_event_signal(&msg);

    return RT_EOK;
}

rt_size_t rt_usbd_ep0_write(udevice_t device, void *buffer, rt_size_t size)
{
    uep_t ep0;
    rt_size_t sent_size = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->dcd != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);
    RT_ASSERT(size > 0);

    ep0 = &device->dcd->ep0;
    ep0->request.size = size;
    ep0->request.buffer = (rt_uint8_t *)buffer;
    ep0->request.remain_size = size;
    if(size >= ep0->id->maxpacket)
    {
        sent_size = ep0->id->maxpacket;
    }
    else
    {
        sent_size = size;
    }
    device->dcd->stage = STAGE_DIN;

    return dcd_ep_write(device->dcd, EP0_IN_ADDR, ep0->request.buffer, sent_size);
}

rt_size_t rt_usbd_ep0_read(udevice_t device, void *buffer, rt_size_t size,
    rt_err_t (*rx_ind)(udevice_t device, rt_size_t size))
{
    uep_t ep0;
    rt_size_t read_size = 0;

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(device->dcd != RT_NULL);
    RT_ASSERT(buffer != RT_NULL);

    ep0 = &device->dcd->ep0;
    ep0->request.buffer = (rt_uint8_t *)buffer;
    ep0->request.remain_size = size;
    ep0->rx_indicate = rx_ind;
    if(size >= ep0->id->maxpacket)
    {
        read_size = ep0->id->maxpacket;
    }
    else
    {
        read_size = size;
    }
    device->dcd->stage = STAGE_DOUT;
    dcd_ep_read_prepare(device->dcd, EP0_OUT_ADDR, buffer, read_size);

    return size;
}

static struct rt_messagequeue usb_mq;

/**
 * This function is the main entry of usb device thread, it is in charge of
 * processing all messages received from the usb message buffer.
 *
 * @param parameter the parameter of the usb device thread.
 *
 * @return none.
 */
static void rt_usbd_thread_entry(void* parameter)
{
    while(1)
    {
        struct udev_msg msg;
        udevice_t device;

        /* receive message */
        if(rt_mq_recv(&usb_mq, &msg, sizeof(struct udev_msg),
                    RT_WAITING_FOREVER) != RT_EOK )
            continue;

        device = rt_usbd_find_device(msg.dcd);
        if(device == RT_NULL)
        {
            rt_kprintf("invalid usb device\n");
            continue;
        }

        RT_DEBUG_LOG(RT_DEBUG_USB, ("message type %d\n", msg.type));

        switch (msg.type)
        {
        case USB_MSG_SOF:
            _sof_notify(device);
            break;
        case USB_MSG_DATA_NOTIFY:
            /* some buggy drivers will have USB_MSG_DATA_NOTIFY before the core
             * got configured. */
            _data_notify(device, &msg.content.ep_msg);
            break;
        case USB_MSG_SETUP_NOTIFY:
            _setup_request(device, &msg.content.setup);
            break;
        case USB_MSG_EP0_OUT:
            _ep0_out_notify(device, &msg.content.ep_msg);
            break;
        case USB_MSG_RESET:
            RT_DEBUG_LOG(RT_DEBUG_USB, ("reset %d\n", device->state));
            if (device->state == USB_STATE_ADDRESS || device->state == USB_STATE_CONFIGURED)
                _stop_notify(device);
            device->state = USB_STATE_NOTATTACHED;
            break;
        case USB_MSG_PLUG_IN:
            device->state = USB_STATE_ATTACHED;
            break;
        case USB_MSG_PLUG_OUT:
            device->state = USB_STATE_NOTATTACHED;
            _stop_notify(device);
            break;
        default:
            rt_kprintf("unknown msg type %d\n", msg.type);
            break;
        }
    }
}

/**
 * This function will post an message to usb message queue,
 *
 * @param msg the message to be posted
 * @param size the size of the message .
 *
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbd_event_signal(struct udev_msg* msg)
{
    RT_ASSERT(msg != RT_NULL);

    /* send message to usb message queue */
    return rt_mq_send(&usb_mq, (void*)msg, sizeof(struct udev_msg));
}


ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t usb_thread_stack[RT_USBD_THREAD_STACK_SZ];
static struct rt_thread usb_thread;
#define USBD_MQ_MSG_SZ  32
#define USBD_MQ_MAX_MSG 16
/* internal of the message queue: every message is associated with a pointer,
 * so in order to recveive USBD_MQ_MAX_MSG messages, we have to allocate more
 * than USBD_MQ_MSG_SZ*USBD_MQ_MAX_MSG memory. */
static rt_uint8_t usb_mq_pool[(USBD_MQ_MSG_SZ+sizeof(void*))*USBD_MQ_MAX_MSG];

/**
 * This function will initialize usb device thread.
 *
 * @return none.
 *
 */
rt_err_t rt_usbd_core_init(void)
{
    rt_list_init(&device_list);

    /* create an usb message queue */
    rt_mq_init(&usb_mq,
               "usbd",
               usb_mq_pool, USBD_MQ_MSG_SZ,
               sizeof(usb_mq_pool),
               RT_IPC_FLAG_FIFO);

    /* init usb device thread */
    rt_thread_init(&usb_thread,
                   "usbd",
                   rt_usbd_thread_entry, RT_NULL,
                   usb_thread_stack, RT_USBD_THREAD_STACK_SZ,
                   RT_USBD_THREAD_PRIO, 20);
    /* rt_thread_init should always be OK, so start the thread without further
     * checking. */
    return rt_thread_startup(&usb_thread);
}

