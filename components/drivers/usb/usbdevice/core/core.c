/*
 * File      : core.c
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
 * 2012-10-01     Yi Qiu       first version
 * 2012-12-12     heyuanjie87  change endpoint and class handler
 * 2012-12-30     heyuanjie87  change inferface handler
 */

#include <rtthread.h>
#include <rtdevice.h>

static rt_list_t device_list;

/**
 * This function will handle get_device_descriptor request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_device_descriptor(struct udevice *device, ureq_t setup)
{
    rt_size_t size;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_device_descriptor\n"));

    /* device descriptor length should less than USB_DESC_LENGTH_DEVICE*/
    size = (setup->length > USB_DESC_LENGTH_DEVICE) ?
           USB_DESC_LENGTH_DEVICE : setup->length;

    /* send device descriptor to endpoint 0 */
    dcd_ep_write(device->dcd, 0, (rt_uint8_t *)&device->dev_desc, size);

    return RT_EOK;
}

/**
 * This function will handle get_config_descriptor request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_config_descriptor(struct udevice *device, ureq_t setup)
{
    rt_size_t size;
    ucfg_desc_t cfg_desc;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_config_descriptor\n"));

    cfg_desc = &device->curr_cfg->cfg_desc;
    size = (setup->length > cfg_desc->wTotalLength) ?
           cfg_desc->wTotalLength : setup->length;

    /* send configuration descriptor to endpoint 0 */
    dcd_ep_write(device->dcd, 0, (rt_uint8_t *)cfg_desc, size);

    return RT_EOK;
}

/**
 * This function will handle get_string_descriptor request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful, -RT_ERROR on invalid request.
 */
static rt_err_t _get_string_descriptor(struct udevice *device, ureq_t setup)
{
    struct ustring_descriptor str_desc;
    rt_uint8_t index, i;
    rt_uint32_t len;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_string_descriptor\n"));

    str_desc.type = USB_DESC_TYPE_STRING;
    index = setup->value & 0xFF;

    if (index > USB_STRING_INTERFACE_INDEX)
    {
        rt_kprintf("unknown string index\n");
        dcd_ep_stall(device->dcd, 0);

        return -RT_ERROR;
    }
    if (index == 0)
    {
        str_desc.bLength = 4;
        str_desc.String[0] = 0x09;
        str_desc.String[1] = 0x04;
    }
    else
    {
        len = rt_strlen(device->str[index]);
        str_desc.bLength = len*2 + 2;

        for (i=0; i<len; i++)
        {
            str_desc.String[i*2] = device->str[index][i];
            str_desc.String[i*2 + 1] = 0;
        }
    }

    if (setup->length > str_desc.bLength)
        len = str_desc.bLength;
    else
        len = setup->length;

    /* send string descriptor to endpoint 0 */
    dcd_ep_write(device->dcd, 0, (rt_uint8_t *)&str_desc, len);

    return RT_EOK;
}

/**
 * This function will handle get_descriptor request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_descriptor(struct udevice *device, ureq_t setup)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    if (setup->request_type == USB_REQ_TYPE_DIR_IN)
    {
        switch (setup->value >> 8)
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
            dcd_ep_stall(device->dcd, 0);
            break;
        default:
            rt_kprintf("unsupported descriptor request\n");
            dcd_ep_stall(device->dcd, 0);
            break;
        }
    }
    else
    {
        rt_kprintf("request direction error\n");
        dcd_ep_stall(device->dcd, 0);
    }

    return RT_EOK;
}

/**
 * This function will handle get_interface request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_interface(struct udevice *device, ureq_t setup)
{
    rt_uint8_t value;
    uintf_t intf;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_get_interface\n"));

    if (device->state != USB_STATE_CONFIGURED)
    {
        dcd_ep_stall(device->dcd, 0);

        return -RT_ERROR;
    }

    /* find the specified interface and its alternate setting */
    intf = rt_usbd_find_interface(device, setup->index & 0xFF, RT_NULL);
    value = intf->curr_setting->intf_desc->bAlternateSetting;

    /* send the interface alternate setting to endpoint 0*/
    dcd_ep_write(device->dcd, 0, &value, 1);

    return RT_EOK;
}

/**
 * This function will handle set_interface request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _set_interface(struct udevice *device, ureq_t setup)
{
    uintf_t intf;
    uep_t ep;
    struct rt_list_node *i;
    ualtsetting_t setting;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_set_interface\n"));

    if (device->state != USB_STATE_CONFIGURED)
    {
        dcd_ep_stall(device->dcd, 0);

        return -RT_ERROR;
    }

    /* find the specified interface */
    intf = rt_usbd_find_interface(device, setup->index & 0xFF, RT_NULL);

    /* set alternate setting to the interface */
    rt_usbd_set_altsetting(intf, setup->value & 0xFF);
    setting = intf->curr_setting;

    /* start all endpoints of the interface alternate setting */
    for (i=setting->ep_list.next; i != &setting->ep_list; i=i->next)
    {
        ep = (uep_t)rt_list_entry(i, struct uendpoint, list);
        dcd_ep_stop(device->dcd, ep);
        dcd_ep_run(device->dcd, ep);
    }
    dcd_send_status(device->dcd);
    
    return RT_EOK;
}

/**
 * This function will handle get_config request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _get_config(struct udevice *device, ureq_t setup)
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
    dcd_ep_write(device->dcd, 0, &value, 1);

    return RT_EOK;
}

/**
 * This function will handle set_config request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _set_config(struct udevice *device, ureq_t setup)
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

    if (setup->value > device->dev_desc.bNumConfigurations)
    {
        dcd_ep_stall(device->dcd, 0);

        return -RT_ERROR;
    }

    if (setup->value == 0)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("address state\n"));
        device->state = USB_STATE_ADDRESS;

        goto _exit;
    }

    /* set current configuration */
    rt_usbd_set_config(device, setup->value);
    cfg = device->curr_cfg;

    for (i=cfg->cls_list.next; i!=&cfg->cls_list; i=i->next)
    {
        /* run all classes and their endpoints in the configuration */
        uclass_t cls = (uclass_t)rt_list_entry(i, struct uclass, list);
        for (j=cls->intf_list.next; j!=&cls->intf_list; j=j->next)
        {
            intf = (uintf_t)rt_list_entry(j, struct uinterface, list);
            setting = intf->curr_setting;
            for (k=setting->ep_list.next; k != &setting->ep_list; k=k->next)
            {
                ep = (uep_t)rt_list_entry(k, struct uendpoint, list);

                /* first stop then start endpoint */
                dcd_ep_stop(device->dcd, ep);
                dcd_ep_run(device->dcd, ep);
            }
        }
        /* after running all endpoints, then run class */
        if (cls->ops->run != RT_NULL)
            cls->ops->run(device, cls);
    }

    device->state = USB_STATE_CONFIGURED;

_exit:
    /* issue status stage */
    dcd_send_status(device->dcd);

    return RT_EOK;
}

/**
 * This function will handle set_address request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _set_address(struct udevice *device, ureq_t setup)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_set_address\n"));

    /* set address in device control driver */
    dcd_set_address(device->dcd, setup->value);

    device->state = USB_STATE_ADDRESS;

    /* issue status stage */
    dcd_send_status(device->dcd);

    return RT_EOK;
}

/**
 * This function will handle standard request to 
 * interface that defined in class-specifics
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful. 
 */
static rt_err_t _request_interface(struct udevice *device, ureq_t setup)
{
    uintf_t intf;
    uclass_t cls;
    rt_err_t ret;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("_request_interface\n"));

    intf = rt_usbd_find_interface(device, setup->index & 0xFF, &cls);
    if (intf != RT_NULL)
    {
        ret = intf->handler(device, cls, setup);
    }
    else
    {
        ret = -RT_ERROR;
    }

    return ret;
}

/**
 * This function will handle standard request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful.
 */
static rt_err_t _standard_request(struct udevice *device, ureq_t setup)
{
    udcd_t dcd;
    rt_uint16_t value = 0;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    dcd = device->dcd;

    switch (setup->request_type & USB_REQ_TYPE_RECIPIENT_MASK)
    {
    case USB_REQ_TYPE_DEVICE:
        switch (setup->request)
        {
        case USB_REQ_GET_STATUS:
            dcd_ep_write(device->dcd, 0, &value, 2);
            break;
        case USB_REQ_CLEAR_FEATURE:
            dcd_clear_feature(dcd, setup->value, setup->index);
            dcd_send_status(dcd);
            break;
        case USB_REQ_SET_FEATURE:
            dcd_set_feature(dcd, setup->value, setup->index);
            break;
        case USB_REQ_SET_ADDRESS:
            _set_address(device, setup);
            break;
        case USB_REQ_GET_DESCRIPTOR:
            _get_descriptor(device, setup);
            break;
        case USB_REQ_SET_DESCRIPTOR:
            dcd_ep_stall(dcd, 0);
            break;
        case USB_REQ_GET_CONFIGURATION:
            _get_config(device, setup);
            break;
        case USB_REQ_SET_CONFIGURATION:
            _set_config(device, setup);
            break;
        default:
            rt_kprintf("unknown device request\n");
            dcd_ep_stall(device->dcd, 0);
            break;
        }
        break;
    case USB_REQ_TYPE_INTERFACE:
        switch (setup->request)
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
                dcd_ep_stall(device->dcd, 0);

                return - RT_ERROR;
            }
            else
                break;
        }
        break;
    case USB_REQ_TYPE_ENDPOINT:
        switch (setup->request)
        {
        case USB_REQ_GET_STATUS:
        {
            /* TODO */
            uep_t ep;
        
            ep = rt_usbd_find_endpoint(device, RT_NULL, setup->index);
            value = ep->is_stall;        
            dcd_ep_write(dcd, 0, &value, 2);
        }
        break;
        case USB_REQ_CLEAR_FEATURE:
        {
            uep_t ep;
        
            ep = rt_usbd_find_endpoint(device, RT_NULL, setup->index);
            ep->is_stall = 0;
            dcd_clear_feature(dcd, setup->value, setup->index);
            dcd_send_status(dcd);
        }
        break;
        case USB_REQ_SET_FEATURE:
        {
            uep_t ep;
        
            ep = rt_usbd_find_endpoint(device, RT_NULL, setup->index);
            ep->is_stall = 1;            
            dcd_set_feature(dcd, setup->value, setup->index);
            dcd_send_status(dcd);
        }
        break;
        case USB_REQ_SYNCH_FRAME:
            break;
        default:
            rt_kprintf("unknown endpoint request\n");
            dcd_ep_stall(device->dcd, 0);
            break;
        }
        break;
    case USB_REQ_TYPE_OTHER:
        rt_kprintf("unknown other type request\n");
        dcd_ep_stall(device->dcd, 0);
        break;
    default:
        rt_kprintf("unknown type request\n");
        dcd_ep_stall(device->dcd, 0);
        break;
    }

    return RT_EOK;
}

/**
 * This function will handle class request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful, -RT_ERROR on invalid request.
 */
static rt_err_t _class_request(udevice_t device, ureq_t setup)
{
    uintf_t intf;
    uclass_t cls;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    /* verify request value */
    if (setup->index > device->curr_cfg->cfg_desc.bNumInterfaces)
    {
        dcd_ep_stall(device->dcd, 0);

        return -RT_ERROR;
    }

    switch (setup->request_type & USB_REQ_TYPE_RECIPIENT_MASK)
    {
    case USB_REQ_TYPE_INTERFACE:
        intf = rt_usbd_find_interface(device, setup->index & 0xFF, &cls);
        intf->handler(device, cls, setup);
        break;
    case USB_REQ_TYPE_ENDPOINT:
        break;
    default:
        rt_kprintf("unknown class request type\n");
        dcd_ep_stall(device->dcd, 0);
        break;
    }

    return RT_EOK;
}

/**
 * This function will handle setup request.
 *
 * @param device the usb device object.
 * @param setup the setup request.
 *
 * @return RT_EOK on successful, -RT_ERROR on invalid request.
 */
static rt_err_t _setup_request(udevice_t device, ureq_t setup)
{
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(setup != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("[\n"));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("setup_request_handler 0x%x\n",
                                setup->request_type));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("value 0x%x\n", setup->value));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("length 0x%x\n", setup->length));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("index 0x%x\n", setup->index));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("request 0x%x\n", setup->request));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("]\n"));

    switch ((setup->request_type & USB_REQ_TYPE_MASK))
    {
    case USB_REQ_TYPE_STANDARD:
        _standard_request(device, setup);
        break;
    case USB_REQ_TYPE_CLASS:
        _class_request(device, setup);
        break;
    case USB_REQ_TYPE_VENDOR:
        rt_kprintf("vendor type request\n");
        break;
    default:
        rt_kprintf("unknown setup request type\n");
        dcd_ep_stall(device->dcd, 0);
        return -RT_ERROR;
    }

    return RT_EOK;
}

/**
 * This function will notity sof event to all of class.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK.
 */
rt_err_t _sof_notify(udevice_t device)
{
    struct rt_list_node *i;
    uclass_t cls;

    RT_ASSERT(device != RT_NULL);

    /* to notity every class that sof event comes */
    for (i  = device->curr_cfg->cls_list.next;
         i != &device->curr_cfg->cls_list;
         i  = i->next)
    {
        cls = (uclass_t)rt_list_entry(i, struct uclass, list);
        if (cls->ops->sof_handler != RT_NULL)
            cls->ops->sof_handler(device, cls);
    }

    return RT_EOK;
}

/**
 * This function will stop all class.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK.
 */
rt_err_t _stop_notify(udevice_t device)
{
    struct rt_list_node *i;
    uclass_t cls;

    RT_ASSERT(device != RT_NULL);

    /* to notity every class that sof event comes */
    for (i  = device->curr_cfg->cls_list.next;
         i != &device->curr_cfg->cls_list;
         i  = i->next)
    {
        cls = (uclass_t)rt_list_entry(i, struct uclass, list);
        if (cls->ops->stop != RT_NULL)
            cls->ops->stop(device, cls);
    }

    return RT_EOK;
}

/**
 * This function will run all class.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK.
 */
rt_err_t _run_notify(udevice_t device)
{
    struct rt_list_node *i;
    uclass_t cls;

    RT_ASSERT(device != RT_NULL);

    /* to notity every class that sof event comes */
    for (i  = device->curr_cfg->cls_list.next;
         i != &device->curr_cfg->cls_list;
         i  = i->next)
    {
        cls = (uclass_t)rt_list_entry(i, struct uclass, list);
        if (cls->ops->run != RT_NULL)
            cls->ops->run(device, cls);
    }

    return RT_EOK;
}

/**
 * This function will reset all class.
 *
 * @param device the usb device object.
 *
 * @return RT_EOK.
 */
rt_err_t _reset_notify(udevice_t device)
{
    struct rt_list_node *i;
    uclass_t cls;

    RT_ASSERT(device != RT_NULL);

    _stop_notify(device);
    _run_notify(device);

    return RT_EOK;
}

/**
 * This function will create an usb device object.
 *
 * @param ustring the usb string array to contain string descriptor.
 *
 * @return an usb device object on success, RT_NULL on fail.
 */
udevice_t rt_usbd_device_create(void)
{
    udevice_t udevice;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_device_create\n"));

    /* allocate memory for the object */
    udevice = rt_malloc(sizeof(struct udevice));
    if (udevice == RT_NULL)
    {
        rt_kprintf("alloc memery failed\n");

        return RT_NULL;
    }
    rt_memset(udevice, 0, sizeof(struct udevice));

    /* to initialize configuration list */
    rt_list_init(&udevice->cfg_list);

    /* insert the device object to device list */
    rt_list_insert_after(&device_list, &udevice->list);

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
uconfig_t rt_usbd_config_create(void)
{
    uconfig_t cfg;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_config_create\n"));

    /* allocate memory for the object */
    cfg = rt_malloc(sizeof(struct uconfig));
    if (cfg == RT_NULL)
    {
        rt_kprintf("alloc memery failed\n");

        return RT_NULL;
    }
    rt_memset(cfg, 0, sizeof(struct uconfig));

    /* set default value */
    cfg->cfg_desc.bLength      = USB_DESC_LENGTH_CONFIG;
    cfg->cfg_desc.type         = USB_DESC_TYPE_CONFIGURATION;
    cfg->cfg_desc.wTotalLength = USB_DESC_LENGTH_CONFIG;
    cfg->cfg_desc.bmAttributes = 0xC0;
    cfg->cfg_desc.MaxPower     = 0x32;

    /* to initialize class object list */
    rt_list_init(&cfg->cls_list);

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
uintf_t rt_usbd_interface_create(udevice_t device, uintf_handler_t handler)
{
    uintf_t intf;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_interface_create\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* allocate memory for the object */
    intf = (uintf_t)rt_malloc(sizeof(struct uinterface));
    if (intf == RT_NULL)
    {
        rt_kprintf("alloc memery failed\n");

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
ualtsetting_t rt_usbd_altsetting_create(rt_size_t desc_size)
{
    ualtsetting_t setting;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_altsetting_create\n"));

    /* parameter check */
    RT_ASSERT(desc_size > 0);

    /* allocate memory for the object */
    setting = (ualtsetting_t)rt_malloc(sizeof(struct ualtsetting));
    if (setting == RT_NULL)
    {
        rt_kprintf("alloc memery failed\n");

        return RT_NULL;
    }
    /* allocate memory for the desc */
    setting->desc = rt_malloc(desc_size);
    if (setting->desc == RT_NULL)
    {
        rt_kprintf("alloc desc memery failed\n");
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
rt_err_t rt_usbd_altsetting_config_descriptor(ualtsetting_t setting,
                                              const void   *desc,
                                              rt_off_t      intf_pos)
{
    RT_ASSERT(setting != RT_NULL);
    RT_ASSERT(setting->desc !=RT_NULL);

    rt_memcpy(setting->desc, desc, setting->desc_size);
    setting->intf_desc = (uintf_desc_t)((char *)setting->desc + intf_pos);

    return RT_EOK;
}

/**
 * This function will create an usb class object.
 *
 * @param device the usb device object.
 * @param dev_desc the device descriptor.
 * @param ops the operation set.
 *
 * @return an usb class object on success, RT_NULL on fail.
 */
uclass_t rt_usbd_class_create(udevice_t    device,
                              udev_desc_t  dev_desc,
                              uclass_ops_t ops)
{
    uclass_t cls;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_class_create\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(dev_desc != RT_NULL);

    /* allocate memory for the object */
    cls = (uclass_t)rt_malloc(sizeof(struct uclass));
    if (cls == RT_NULL)
    {
        rt_kprintf("alloc memery failed\n");

        return RT_NULL;
    }
    cls->dev_desc = dev_desc;
    cls->ops      = ops;
    cls->device   = device;

    /* to initialize interface list */
    rt_list_init(&cls->intf_list);

    return cls;
}

/**
 * This function will create an usb endpoint object.
 *
 * @param ep_desc the endpoint descriptor.
 * @handler the callback handler of object
 *
 * @return an usb endpoint object on success, RT_NULL on fail.
 */
uep_t rt_usbd_endpoint_create(uep_desc_t ep_desc, udep_handler_t handler)
{
    uep_t ep;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_endpoint_create\n"));

    /* parameter check */
    RT_ASSERT(ep_desc != RT_NULL);

    /* allocate memory for the object */
    ep = (uep_t)rt_malloc(sizeof(struct uendpoint));
    if (ep == RT_NULL)
    {
        rt_kprintf("alloc memery failed\n");

        return RT_NULL;
    }
    ep->ep_desc = ep_desc;
    ep->handler = handler;
    ep->buffer  = RT_NULL;

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
    struct rt_list_node *node;
    udevice_t device;

    /* parameter check */
    RT_ASSERT(dcd != RT_NULL);

    /* search a device in the the device list */
    for (node = device_list.next; node != &device_list; node = node->next)
    {
        device = (udevice_t)rt_list_entry(node, struct udevice, list);
        if (device->dcd == dcd)
            return device;
    }

    rt_kprintf("can't find device\n");

    return RT_NULL;
}

/**
 * This function will find an usb configuration object.
 *
 * @param device the usb device object.
 * @param value the configuration number.
 *
 * @return an usb configuration object on found or RT_NULL on not found.
 */
uconfig_t rt_usbd_find_config(udevice_t device, rt_uint8_t value)
{
    struct rt_list_node *node;
    uconfig_t cfg = RT_NULL;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_find_config\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value <= device->dev_desc.bNumConfigurations);

    /* search a configration in the the device */
    for (node  = device->cfg_list.next;
         node != &device->cfg_list;
         node  = node->next)
    {
        cfg = (uconfig_t)rt_list_entry(node, struct udevice, list);
        if (cfg->cfg_desc.bConfigurationValue == value)
            return cfg;
    }

    rt_kprintf("can't find configuration %d\n", value);

    return RT_NULL;
}

/**
 * This function will find an usb interface object.
 *
 * @param device the usb device object.
 * @param value the interface number.
 *
 * @return an usb configuration object on found or RT_NULL on not found.
 */
uintf_t rt_usbd_find_interface(udevice_t  device,
                               rt_uint8_t value,
                               uclass_t  *pcls)
{
    struct rt_list_node *i, *j;
    uclass_t cls;
    uintf_t intf;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_find_interface\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value < device->nr_intf);

    /* search an interface in the current configuration */
    for (i  = device->curr_cfg->cls_list.next;
         i != &device->curr_cfg->cls_list;
         i  = i->next)
    {
        cls = (uclass_t)rt_list_entry(i, struct uclass, list);
        for (j=cls->intf_list.next; j!=&cls->intf_list; j=j->next)
        {
            intf = (uintf_t)rt_list_entry(j, struct uinterface, list);
            if (intf->intf_num == value)
            {
                if (pcls != RT_NULL)
                    *pcls = cls;

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
 * @param value the alternate setting number.
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

    if (intf->curr_setting != RT_NULL)
    {
        /* if the value equal to the current alternate setting, then do not search */
        if (intf->curr_setting->intf_desc->bAlternateSetting == value)
            return intf->curr_setting;
    }

    /* search a setting in the alternate setting list */
    for (i=intf->setting_list.next; i!=&intf->setting_list; i=i->next)
    {
        setting =(ualtsetting_t)rt_list_entry(i, struct ualtsetting, list);
        if (setting->intf_desc->bAlternateSetting == value)
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
uep_t rt_usbd_find_endpoint(udevice_t  device,
                            uclass_t  *pcls,
                            rt_uint8_t ep_addr)
{
    uep_t ep;
    struct rt_list_node *i, *j, *k;
    uclass_t cls;
    uintf_t intf;

    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    /* search a endpoint in the current configuration */
    for (i  = device->curr_cfg->cls_list.next;
         i != &device->curr_cfg->cls_list;
         i  = i->next)
    {
        cls = (uclass_t)rt_list_entry(i, struct uclass, list);
        for (j=cls->intf_list.next; j!=&cls->intf_list; j=j->next)
        {
            intf = (uintf_t)rt_list_entry(j, struct uinterface, list);
            for (k  = intf->curr_setting->ep_list.next;
                 k != &intf->curr_setting->ep_list;
                 k  = k->next)
            {
                ep = (uep_t)rt_list_entry(k, struct uendpoint, list);
                if (ep->ep_desc->bEndpointAddress == ep_addr)
                {
                    if (pcls != RT_NULL)
                        *pcls = cls;

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
    struct rt_list_node *i, *j, *k;
    uclass_t cls;
    uintf_t intf;
    uep_t ep;

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_device_add_config\n"));

    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(cfg != RT_NULL);

    /* set configuration number to the configuration descriptor */
    cfg->cfg_desc.bConfigurationValue = device->dev_desc.bNumConfigurations + 1;
    device->dev_desc.bNumConfigurations++;

    for (i=cfg->cls_list.next; i!=&cfg->cls_list; i=i->next)
    {
        cls = (uclass_t)rt_list_entry(i, struct uclass, list);

        for (j=cls->intf_list.next; j!=&cls->intf_list; j=j->next)
        {
            intf = (uintf_t)rt_list_entry(j, struct uinterface, list);
            cfg->cfg_desc.bNumInterfaces++;

            /* allocate address for every endpoint in the interface alternate setting */
            for (k  = intf->curr_setting->ep_list.next;
                 k != &intf->curr_setting->ep_list;
                 k  = k->next)
            {
                ep = (uep_t)rt_list_entry(k, struct uendpoint, list);
                dcd_ep_alloc(device->dcd, ep);
            }

            /* construct complete configuration descriptor */
            rt_memcpy((void *)&cfg->cfg_desc.data[cfg->cfg_desc.wTotalLength - USB_DESC_LENGTH_CONFIG],
                      (void *)intf->curr_setting->desc,
                      intf->curr_setting->desc_size);
            cfg->cfg_desc.wTotalLength += intf->curr_setting->desc_size;
        }
    }

    /* insert the configuration to the list */
    rt_list_insert_after(&device->cfg_list, &cfg->list);

    return RT_EOK;
}

/**
 * This function will add a class to a configuration.
 *
 * @param cfg the configuration object.
 * @param cls the class object.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_config_add_class(uconfig_t cfg, uclass_t cls)
{
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_config_add_class\n"));

    /* parameter check */
    RT_ASSERT(cfg != RT_NULL);
    RT_ASSERT(cls != RT_NULL);

    /* insert the class to the list */
    rt_list_insert_after(&cfg->cls_list, &cls->list);

    return RT_EOK;
}

/**
 * This function will add an interface to a class.
 *
 * @param cls the class object.
 * @param intf the interface object.
 *
 * @return RT_EOK.
 */
rt_err_t rt_usbd_class_add_interface(uclass_t cls, uintf_t intf)
{

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbd_class_add_interface\n"));

    /* parameter check */
    RT_ASSERT(cls != RT_NULL);
    RT_ASSERT(intf != RT_NULL);

    /* insert the interface to the list */
    rt_list_insert_after(&cls->intf_list, &intf->list);

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
    rt_list_insert_after(&intf->setting_list, &setting->list);

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
    rt_list_insert_after(&setting->ep_list, &ep->list);

    return RT_EOK;
}

/**
 * This function will set an alternate setting for an interface.
 *
 * @param intf_desc the interface descriptor.
 * @param value the alternate setting number.
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
 * @param value the configuration number.
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

    return RT_TRUE;
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
static void rt_usbd_thread_entry(void *parameter)
{
    while (1)
    {
        struct udev_msg msg;
        udevice_t device;
        uclass_t cls;
        uep_t ep;

        /* receive message */
        if (rt_mq_recv(&usb_mq, &msg, sizeof(struct udev_msg), RT_WAITING_FOREVER) != RT_EOK)
            continue;

        device = rt_usbd_find_device(msg.dcd);
        if (device == RT_NULL)
        {
            rt_kprintf("invalid usb device\n");
            continue;
        }

        switch (msg.type)
        {
        case USB_MSG_SOF:
            _sof_notify(device);
            break;
        case USB_MSG_DATA_NOTIFY:
            /* some buggy drivers will have USB_MSG_DATA_NOTIFY before the core
             * got configured. */
            if (device->state != USB_STATE_CONFIGURED)
                break;
            ep = rt_usbd_find_endpoint(device, &cls, msg.content.ep_msg.ep_addr);
            if (ep != RT_NULL)
                ep->handler(device, cls, msg.content.ep_msg.size);
            else
                rt_kprintf("invalid endpoint\n");
            break;
        case USB_MSG_SETUP_NOTIFY:
            _setup_request(device, (ureq_t)msg.content.setup_msg.packet);
            break;
        case USB_MSG_RESET:
            if (device->state == USB_STATE_ADDRESS)
                _reset_notify(device);
            break;
        case USB_MSG_PLUG_OUT:
            _stop_notify(device);
            break;
        default:
            rt_kprintf("unknown msg type\n");
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
rt_err_t rt_usbd_post_event(struct udev_msg *msg, rt_size_t size)
{
    RT_ASSERT(msg != RT_NULL);

    /* send message to usb message queue */
    return rt_mq_send(&usb_mq, (void *)msg, size);
}


ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t usb_thread_stack[RT_USBD_THREAD_STACK_SZ];
static struct rt_thread usb_thread;
#define USBD_MQ_MSG_SZ  32
#define USBD_MQ_MAX_MSG 16
/* internal of the message queue: every message is associated with a pointer,
 * so in order to recveive USBD_MQ_MAX_MSG messages, we have to allocate more
 * than USBD_MQ_MSG_SZ*USBD_MQ_MAX_MSG memery. */
static rt_uint8_t usb_mq_pool[(USBD_MQ_MSG_SZ+sizeof(void*))*USBD_MQ_MAX_MSG];

/**
 * This function will initialize usb device thread.
 *
 * @return none.
 */
rt_err_t rt_usbd_core_init(void)
{
    rt_list_init(&device_list);

    /* create an usb message queue */
    rt_mq_init(&usb_mq,
               "usbd",
               usb_mq_pool,
               USBD_MQ_MSG_SZ,
               sizeof(usb_mq_pool),
               RT_IPC_FLAG_FIFO);

    /* init usb device thread */
    rt_thread_init(&usb_thread,
                   "usbd",
                   rt_usbd_thread_entry,
                   RT_NULL,
                   usb_thread_stack,
                   RT_USBD_THREAD_STACK_SZ,
                   RT_USBD_THREAD_PRIO,
                   20);
    /* rt_thread_init should always be OK, so start the thread without further
     * checking. */

    return rt_thread_startup(&usb_thread);
}
