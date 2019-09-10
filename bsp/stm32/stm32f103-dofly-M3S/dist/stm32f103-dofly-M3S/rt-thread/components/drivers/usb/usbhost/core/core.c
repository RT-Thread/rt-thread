/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-12     Yi Qiu      first version
 */

#include <rtthread.h>
#include <drivers/usb_host.h>

static struct uinstance dev[USB_MAX_DEVICE];

/**
 * This function will allocate an usb device instance from system.
 *
 * @param parent the hub instance to which the new allocated device attached.
 * @param port the hub port.
 *
 * @return the allocate instance on successful, or RT_NULL on failure.
 */
uinst_t rt_usbh_alloc_instance(uhcd_t uhcd)
{
    int i;

    /* lock scheduler */
    rt_enter_critical();
    
    for(i=0; i<USB_MAX_DEVICE; i++)
    {
        /* to find an idle instance handle */
        if(dev[i].status != DEV_STATUS_IDLE) continue;
        
        /* initialize the usb device instance */
        rt_memset(&dev[i], 0, sizeof(struct uinstance));
        
        dev[i].status = DEV_STATUS_BUSY;
        dev[i].index = i + 1;
        dev[i].address = 0;
        dev[i].max_packet_size = 0x8;
        rt_list_init(&dev[i].pipe);
        dev[i].hcd = uhcd;
        /* unlock scheduler */        
        rt_exit_critical();
        return &dev[i];
    }

    /* unlock scheduler */            
    rt_exit_critical();     

    return RT_NULL;
}

/**
 * This function will attatch an usb device instance to a host controller,
 * and do device enumunation process.
 *
 * @param hcd the host controller driver.
 * @param device the usb device instance.
 * 
 * @return the error code, RT_EOK on successfully.
 */
static struct uendpoint_descriptor ep0_out_desc = 
{
    /*endpoint descriptor*/
    USB_DESC_LENGTH_ENDPOINT,
    USB_DESC_TYPE_ENDPOINT,
    0x00 | USB_DIR_OUT,
    USB_EP_ATTR_CONTROL,
    0x00,
    0x00,
};
static struct uendpoint_descriptor ep0_in_desc = 
{
    /*endpoint descriptor*/
    USB_DESC_LENGTH_ENDPOINT,
    USB_DESC_TYPE_ENDPOINT,
    0x00 | USB_DIR_IN,
    USB_EP_ATTR_CONTROL,
    0x00,
    0x00,
};
rt_err_t rt_usbh_attatch_instance(uinst_t device)
{
    int i = 0;
    rt_err_t ret = RT_EOK;
    struct uconfig_descriptor cfg_desc;
    udev_desc_t dev_desc;
    uintf_desc_t intf_desc;
    uep_desc_t ep_desc;
    rt_uint8_t ep_index;
    upipe_t pipe;
    ucd_t drv;

    RT_ASSERT(device != RT_NULL);
    
    rt_memset(&cfg_desc, 0, sizeof(struct uconfig_descriptor));
    dev_desc = &device->dev_desc;
    
    /* alloc address 0 ep0 pipe*/
    ep0_out_desc.wMaxPacketSize = 8;
    ep0_in_desc.wMaxPacketSize = 8;
    rt_usb_hcd_alloc_pipe(device->hcd, &device->pipe_ep0_out, device, &ep0_out_desc);
    rt_usb_hcd_alloc_pipe(device->hcd, &device->pipe_ep0_in, device, &ep0_in_desc);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("start enumnation\n"));
    
    /* get device descriptor head */
    ret = rt_usbh_get_descriptor(device, USB_DESC_TYPE_DEVICE, (void*)dev_desc, 8);
    if(ret != RT_EOK)
    {
        rt_kprintf("get device descriptor head failed\n");
        return ret;
    }
    
    /* reset bus */
    rt_usbh_hub_reset_port(device->parent_hub, device->port);
    rt_thread_delay(2);
    rt_usbh_hub_clear_port_feature(device->parent_hub, i + 1, PORT_FEAT_C_CONNECTION);
    /* set device address */
    ret = rt_usbh_set_address(device);
    if(ret != RT_EOK)
    {
        rt_kprintf("set device address failed\n");
        return ret;
    }
    /* free address 0 ep0 pipe*/
    
    rt_usb_hcd_free_pipe(device->hcd,device->pipe_ep0_out);
    rt_usb_hcd_free_pipe(device->hcd,device->pipe_ep0_in);
    
    /* set device max packet size */
    ep0_out_desc.wMaxPacketSize = device->dev_desc.bMaxPacketSize0;
    ep0_in_desc.wMaxPacketSize = device->dev_desc.bMaxPacketSize0;
    
    /* alloc true address ep0 pipe*/
    rt_usb_hcd_alloc_pipe(device->hcd, &device->pipe_ep0_out, device, &ep0_out_desc);
    rt_usb_hcd_alloc_pipe(device->hcd, &device->pipe_ep0_in, device, &ep0_in_desc);
    RT_DEBUG_LOG(RT_DEBUG_USB, ("get device descriptor length %d\n",
                                dev_desc->bLength));
    
    /* get full device descriptor again */
    ret = rt_usbh_get_descriptor(device, USB_DESC_TYPE_DEVICE, (void*)dev_desc, dev_desc->bLength);
    if(ret != RT_EOK)
    {
        rt_kprintf("get full device descriptor failed\n");
        return ret;
    }

    RT_DEBUG_LOG(RT_DEBUG_USB, ("Vendor ID 0x%x\n", dev_desc->idVendor));
    RT_DEBUG_LOG(RT_DEBUG_USB, ("Product ID 0x%x\n", dev_desc->idProduct));

    /* get configuration descriptor head */
    ret = rt_usbh_get_descriptor(device, USB_DESC_TYPE_CONFIGURATION, &cfg_desc, 18);
    if(ret != RT_EOK)
    {
        rt_kprintf("get configuration descriptor head failed\n");
        return ret;
    }

    /* alloc memory for configuration descriptor */
    device->cfg_desc = (ucfg_desc_t)rt_malloc(cfg_desc.wTotalLength);
    rt_memset(device->cfg_desc, 0, cfg_desc.wTotalLength);

    /* get full configuration descriptor */
    ret = rt_usbh_get_descriptor(device, USB_DESC_TYPE_CONFIGURATION, 
        device->cfg_desc, cfg_desc.wTotalLength);
    if(ret != RT_EOK)
    {
        rt_kprintf("get full configuration descriptor failed\n");
        return ret;
    }

    /* set configuration */
    ret = rt_usbh_set_configure(device, 1);
    if(ret != RT_EOK) 
    {
        return ret;
    }
    for(i=0; i<device->cfg_desc->bNumInterfaces; i++)
    {        
        /* get interface descriptor through configuration descriptor */
        ret = rt_usbh_get_interface_descriptor(device->cfg_desc, i, &intf_desc);
        if(ret != RT_EOK)
        {
            rt_kprintf("rt_usb_get_interface_descriptor error\n");
            return -RT_ERROR;
        }

        RT_DEBUG_LOG(RT_DEBUG_USB, ("interface class 0x%x, subclass 0x%x\n", 
                                    intf_desc->bInterfaceClass,
                                    intf_desc->bInterfaceSubClass));
        /* alloc pipe*/
        for(ep_index = 0; ep_index < intf_desc->bNumEndpoints; ep_index++)
        {
            rt_usbh_get_endpoint_descriptor(intf_desc, ep_index, &ep_desc);
            if(ep_desc != RT_NULL)
            {
                if(rt_usb_hcd_alloc_pipe(device->hcd, &pipe, device, ep_desc) != RT_EOK)
                {
                    rt_kprintf("alloc pipe failed\n");
                    return RT_ERROR;
                }
                rt_usb_instance_add_pipe(device,pipe);
            }
            else
            {
                rt_kprintf("get endpoint desc failed\n");
                return RT_ERROR;
            }
        }
        /* find driver by class code found in interface descriptor */
        drv = rt_usbh_class_driver_find(intf_desc->bInterfaceClass, 
            intf_desc->bInterfaceSubClass);
        
        if(drv != RT_NULL)
        {
            /* allocate memory for interface device */
            device->intf[i] = (struct uhintf*)rt_malloc(sizeof(struct uhintf));
            device->intf[i]->drv = drv;
            device->intf[i]->device = device;
            device->intf[i]->intf_desc = intf_desc;
            device->intf[i]->user_data = RT_NULL;

            /* open usb class driver */
            ret = rt_usbh_class_driver_enable(drv, (void*)device->intf[i]);
            if(ret != RT_EOK)
            {
                rt_kprintf("interface %d run class driver error\n", i);
            }
        }
        else
        {
            rt_kprintf("find usb device driver failed\n");
            continue;
        }
    }
    
    return RT_EOK;
}

/**
 * This function will detach an usb device instance from its host controller,
 * and release all resource.
 *
 * @param device the usb device instance.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_detach_instance(uinst_t device)
{
    int i = 0;
    rt_list_t * l;
    if(device == RT_NULL) 
    {
        rt_kprintf("no usb instance to detach\n");
        return -RT_ERROR;
    }
    
    /* free configration descriptor */
    if (device->cfg_desc) {
        for (i = 0; i < device->cfg_desc->bNumInterfaces; i++)
        {
            if (device->intf[i] == RT_NULL) continue;
            if (device->intf[i]->drv == RT_NULL) continue;

            RT_ASSERT(device->intf[i]->device == device);

            RT_DEBUG_LOG(RT_DEBUG_USB, ("free interface instance %d\n", i));
            rt_usbh_class_driver_disable(device->intf[i]->drv, (void*)device->intf[i]);
            rt_free(device->intf[i]);
        }
        rt_free(device->cfg_desc);
    }
    
    rt_usb_hcd_free_pipe(device->hcd,device->pipe_ep0_out);
    rt_usb_hcd_free_pipe(device->hcd,device->pipe_ep0_in);
    
    while(device->pipe.next!= &device->pipe)
    {
        l = device->pipe.next;
        rt_list_remove(l);
        rt_usb_hcd_free_pipe(device->hcd,rt_list_entry(l,struct upipe,list));
    }
    rt_memset(device, 0, sizeof(struct uinstance));
    
    return RT_EOK;
}

/**
 * This function will do USB_REQ_GET_DESCRIPTO' bRequest for the usb device instance,
 *
 * @param device the usb device instance. 
 * @param type the type of descriptor bRequest.
 * @param buffer the data buffer to save requested data
 * @param nbytes the size of buffer
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_get_descriptor(uinst_t device, rt_uint8_t type, void* buffer, 
    int nbytes)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;
    
    RT_ASSERT(device != RT_NULL);

    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_STANDARD | 
        USB_REQ_TYPE_DEVICE;
    setup.bRequest = USB_REQ_GET_DESCRIPTOR;
    setup.wIndex = 0;
    setup.wLength = nbytes;
    setup.wValue = type << 8;

    if(rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) == 8)
    {
        if(rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, buffer, nbytes, timeout) == nbytes)
        {
            if(rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_out, RT_NULL, 0, timeout) == 0)
            {
                return RT_EOK;
            }
        }
    }
    return RT_ERROR;
}

/**
 * This function will set an address to the usb device.
 *
 * @param device the usb device instance.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_set_address(uinst_t device)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;
    
    RT_ASSERT(device != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usb_set_address\n"));

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_STANDARD | 
        USB_REQ_TYPE_DEVICE;
    setup.bRequest = USB_REQ_SET_ADDRESS;
    setup.wIndex = 0;
    setup.wLength = 0;
    setup.wValue = device->index;

    if(rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) != 8)
    {
        return RT_ERROR;
    }
    if(rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, RT_NULL, 0, timeout) == 0)
    {
        device->address = device->index;
    }

    return RT_EOK;
}

/**
 * This function will set a configuration to the usb device.
 *
 * @param device the usb device instance.
 * @param config the configuration number.
  * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_set_configure(uinst_t device, int config)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;

    /* check parameter */
    RT_ASSERT(device != RT_NULL);

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_STANDARD | 
        USB_REQ_TYPE_DEVICE;
    setup.bRequest = USB_REQ_SET_CONFIGURATION;
    setup.wIndex = 0;
    setup.wLength = 0;
    setup.wValue = config;

    if(rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) != 8)
    {
        return RT_ERROR;
    }
    if(rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, RT_NULL, 0, timeout) != 0)
    {
        return RT_ERROR;
    }
    return RT_EOK;    
}

/**
 * This function will set an interface to the usb device.
 *
 * @param device the usb device instance.
 * @param intf the interface number.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_set_interface(uinst_t device, int intf)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;

    /* check parameter */
    RT_ASSERT(device != RT_NULL);

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_STANDARD | 
        USB_REQ_TYPE_INTERFACE;
    setup.bRequest = USB_REQ_SET_INTERFACE;
    setup.wIndex = 0;
    setup.wLength = 0;
    setup.wValue = intf;

    if(rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) != 8)
    {
        return RT_ERROR;
    }
    
    return RT_EOK;    
}

/**
 * This function will clear feature for the endpoint of the usb device.
 *
 * @param device the usb device instance.
 * @param endpoint the endpoint number of the usb device.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_clear_feature(uinst_t device, int endpoint, int feature)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;

    /* check parameter */
    RT_ASSERT(device != RT_NULL);

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_STANDARD | 
        USB_REQ_TYPE_ENDPOINT;
    setup.bRequest = USB_REQ_CLEAR_FEATURE;
    setup.wIndex = endpoint;
    setup.wLength = 0;
    setup.wValue = feature;

    if(rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) != 8)
    {
        return RT_ERROR;
    }
    
    return RT_EOK;    
}

/**
 * This function will get an interface descriptor from the configuration descriptor.
 *
 * @param cfg_desc the point of configuration descriptor structure.
 * @param num the number of interface descriptor.
 * @intf_desc the point of interface descriptor point.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_get_interface_descriptor(ucfg_desc_t cfg_desc, int num, 
    uintf_desc_t* intf_desc)
{
    rt_uint32_t ptr, depth = 0;
    udesc_t desc;

    /* check parameter */
    RT_ASSERT(cfg_desc != RT_NULL);

    ptr = (rt_uint32_t)cfg_desc + cfg_desc->bLength;
    while(ptr < (rt_uint32_t)cfg_desc + cfg_desc->wTotalLength)
    {
        if(depth++ > 0x20) 
        {
            *intf_desc = RT_NULL;        
            return -RT_EIO;
        }
        desc = (udesc_t)ptr;
        if(desc->type == USB_DESC_TYPE_INTERFACE)
        {
            if(((uintf_desc_t)desc)->bInterfaceNumber == num)
            {
                *intf_desc = (uintf_desc_t)desc;

                RT_DEBUG_LOG(RT_DEBUG_USB,
                             ("rt_usb_get_interface_descriptor: %d\n", num));                
                return RT_EOK;
            }
        }    
        ptr = (rt_uint32_t)desc + desc->bLength;
    }

    rt_kprintf("rt_usb_get_interface_descriptor %d failed\n", num);
    return -RT_EIO;
}

/**
 * This function will get an endpoint descriptor from the interface descriptor.
 *
 * @param intf_desc the point of interface descriptor structure.
 * @param num the number of endpoint descriptor.
 * @param ep_desc the point of endpoint descriptor point.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_get_endpoint_descriptor(uintf_desc_t intf_desc, int num, 
    uep_desc_t* ep_desc)
{
    int count = 0, depth = 0;
    rt_uint32_t ptr;    
    udesc_t desc;

    /* check parameter */
    RT_ASSERT(intf_desc != RT_NULL);
    RT_ASSERT(num < intf_desc->bNumEndpoints);
    *ep_desc = RT_NULL;

    ptr = (rt_uint32_t)intf_desc + intf_desc->bLength;
    while(count < intf_desc->bNumEndpoints)
    {
        if(depth++ > 0x20) 
        {
            *ep_desc = RT_NULL;            
            return -RT_EIO;
        }
        desc = (udesc_t)ptr;        
        if(desc->type == USB_DESC_TYPE_ENDPOINT)
        {
            if(num == count) 
            {
                *ep_desc = (uep_desc_t)desc;

                RT_DEBUG_LOG(RT_DEBUG_USB,
                             ("rt_usb_get_endpoint_descriptor: %d\n", num));
                return RT_EOK;
            }
            else count++;
        }
        ptr = (rt_uint32_t)desc + desc->bLength;
    }

    rt_kprintf("rt_usb_get_endpoint_descriptor %d failed\n", num);
    return -RT_EIO;
}

int rt_usb_hcd_pipe_xfer(uhcd_t hcd, upipe_t pipe, void* buffer, int nbytes, int timeout)
{
    rt_size_t remain_size;
    rt_size_t send_size;
    remain_size = nbytes;
    rt_uint8_t * pbuffer = (rt_uint8_t *)buffer;
    do
    {
        RT_DEBUG_LOG(RT_DEBUG_USB,("pipe transform remain size,: %d\n", remain_size));
        send_size = (remain_size > pipe->ep.wMaxPacketSize) ? pipe->ep.wMaxPacketSize : remain_size;
        if(hcd->ops->pipe_xfer(pipe, USBH_PID_DATA, pbuffer, send_size, timeout) == send_size)
        {
            remain_size -= send_size;
            pbuffer += send_size;
        }
        else
        {
            return 0;
        }
    }while(remain_size > 0);
    return nbytes;
}
