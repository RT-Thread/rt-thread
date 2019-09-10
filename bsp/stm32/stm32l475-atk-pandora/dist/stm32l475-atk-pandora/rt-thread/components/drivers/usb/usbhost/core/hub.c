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

#define USB_THREAD_STACK_SIZE    4096

static struct rt_messagequeue *usb_mq;
static struct uclass_driver hub_driver;
static struct uhub root_hub;

static rt_err_t root_hub_ctrl(struct uhcd *hcd, rt_uint16_t port, rt_uint8_t cmd, void *args)
{
    switch(cmd)
    {
    case RH_GET_PORT_STATUS:
        (*(rt_uint32_t *)args) = hcd->roothub->port_status[port-1];
        break;
    case RH_SET_PORT_STATUS:
        hcd->roothub->port_status[port-1] = (*(rt_uint32_t *)args);
        break;
    case RH_CLEAR_PORT_FEATURE:
        switch(((rt_uint32_t)args))
        {
        case PORT_FEAT_C_CONNECTION:
            hcd->roothub->port_status[port-1] &= ~PORT_CCSC;
            break;
        case PORT_FEAT_C_ENABLE:
            hcd->roothub->port_status[port-1] &= ~PORT_PESC;
            break;
        case PORT_FEAT_C_SUSPEND:
            hcd->roothub->port_status[port-1] &= ~PORT_PSSC;
            break;
        case PORT_FEAT_C_OVER_CURRENT:
            hcd->roothub->port_status[port-1] &= ~PORT_POCIC;
            break;
        case PORT_FEAT_C_RESET:
            hcd->roothub->port_status[port-1] &= ~PORT_PRSC;
            break;
        }
        break;
    case RH_SET_PORT_FEATURE:
        switch((rt_uint32_t)args)
        {
        case PORT_FEAT_CONNECTION:
            hcd->roothub->port_status[port-1] |= PORT_CCSC;
            break;
        case PORT_FEAT_ENABLE:
            hcd->roothub->port_status[port-1] |= PORT_PESC;
            break;
        case PORT_FEAT_SUSPEND:
            hcd->roothub->port_status[port-1] |= PORT_PSSC;
            break;
        case PORT_FEAT_OVER_CURRENT:
            hcd->roothub->port_status[port-1] |= PORT_POCIC;
            break;
        case PORT_FEAT_RESET:
            hcd->ops->reset_port(port);
            break;
        case PORT_FEAT_POWER:
            break;
        case PORT_FEAT_LOWSPEED:
            break;
        case PORT_FEAT_HIGHSPEED:
            break;
        }
        break;
    default:
        return RT_ERROR;
    }
    return RT_EOK;
} 
void rt_usbh_root_hub_connect_handler(struct uhcd *hcd, rt_uint8_t port, rt_bool_t isHS)
{
    struct uhost_msg msg;
    msg.type = USB_MSG_CONNECT_CHANGE;
    msg.content.hub = hcd->roothub;
    hcd->roothub->port_status[port - 1] |= PORT_CCS | PORT_CCSC;
    if(isHS)
    {
        hcd->roothub->port_status[port - 1] &= ~PORT_LSDA;
    }
    else
    {
        hcd->roothub->port_status[port - 1] |= PORT_LSDA;
    }
    rt_usbh_event_signal(&msg);
}

void rt_usbh_root_hub_disconnect_handler(struct uhcd *hcd, rt_uint8_t port)
{
    struct uhost_msg msg;
    msg.type = USB_MSG_CONNECT_CHANGE;
    msg.content.hub = hcd->roothub;
    hcd->roothub->port_status[port - 1] |= PORT_CCSC;
    hcd->roothub->port_status[port - 1] &= ~PORT_CCS;
    rt_usbh_event_signal(&msg);
}

/**
 * This function will do USB_REQ_GET_DESCRIPTOR bRequest for the device instance 
 * to get usb hub descriptor.
 *
 * @param intf the interface instance.
 * @buffer the data buffer to save usb hub descriptor.
 * @param nbytes the size of buffer
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hub_get_descriptor(struct uinstance* device, rt_uint8_t *buffer, rt_size_t nbytes)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;
        
    /* parameter check */
    RT_ASSERT(device != RT_NULL);
    
    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_DEVICE;
    setup.bRequest = USB_REQ_GET_DESCRIPTOR;
    setup.wIndex = 0;
    setup.wLength = nbytes;
    setup.wValue = USB_DESC_TYPE_HUB << 8;

    if(rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) == 8)
    {
        if(rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, buffer, nbytes, timeout) == nbytes)
        {
            return RT_EOK;
        }
    } 
    return -RT_FALSE;    
}

/**
 * This function will do USB_REQ_GET_STATUS bRequest for the device instance 
 * to get usb hub status.
 *
 * @param intf the interface instance.
 * @buffer the data buffer to save usb hub status.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hub_get_status(struct uinstance* device, rt_uint32_t* buffer)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;
    
    /* parameter check */
    RT_ASSERT(device != RT_NULL);

    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_DEVICE;
    setup.bRequest = USB_REQ_GET_STATUS;
    setup.wIndex = 0;
    setup.wLength = 4;
    setup.wValue = 0;
    if(rt_usb_hcd_setup_xfer(device->hcd, device->pipe_ep0_out, &setup, timeout) == 8)
    {
        if(rt_usb_hcd_pipe_xfer(device->hcd, device->pipe_ep0_in, buffer, 4, timeout) == 4)
        {
            return RT_EOK;
        }
    }
    return -RT_FALSE;    
}

/**
 * This function will do USB_REQ_GET_STATUS bRequest for the device instance 
 * to get hub port status.
 *
 * @param intf the interface instance.
 * @port the hub port to get status.
 * @buffer the data buffer to save usb hub status.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hub_get_port_status(uhub_t hub, rt_uint16_t port, rt_uint32_t* buffer)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;
    
    /* parameter check */
    RT_ASSERT(hub != RT_NULL);

    /* get roothub port status */
    if(hub->is_roothub)
    {
        root_hub_ctrl(hub->hcd, port, RH_GET_PORT_STATUS, 
            (void*)buffer);
        return RT_EOK;
    }

    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_OTHER;
    setup.bRequest = USB_REQ_GET_STATUS;
    setup.wIndex = port;
    setup.wLength = 4;
    setup.wValue = 0;

    if(rt_usb_hcd_setup_xfer(hub->hcd, hub->self->pipe_ep0_out, &setup, timeout) == 8)
    {
        if(rt_usb_hcd_pipe_xfer(hub->hcd, hub->self->pipe_ep0_in, buffer, 4, timeout) == 4)
        {
            return RT_EOK;
        }
    }
    return -RT_FALSE;        
}

/**
 * This function will do USB_REQ_CLEAR_FEATURE bRequest for the device instance 
 * to clear feature of the hub port.
 *
 * @param intf the interface instance.
 * @port the hub port.
 * @feature feature to be cleared.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hub_clear_port_feature(uhub_t hub, rt_uint16_t port, rt_uint16_t feature)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;
        
    /* parameter check */
    RT_ASSERT(hub != RT_NULL);

    /* clear roothub feature */
    if(hub->is_roothub)
    {
        root_hub_ctrl(hub->hcd, port, RH_CLEAR_PORT_FEATURE, 
            (void*)(rt_uint32_t)feature);
        return RT_EOK;
    }

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_CLASS | 
        USB_REQ_TYPE_OTHER;
    setup.bRequest = USB_REQ_CLEAR_FEATURE;
    setup.wIndex = port;
    setup.wLength = 0;
    setup.wValue = feature;

    if(rt_usb_hcd_setup_xfer(hub->hcd, hub->self->pipe_ep0_out, &setup, timeout) == 8)
    {
        return RT_EOK;
    }
    return -RT_FALSE;    
}

/**
 * This function will do USB_REQ_SET_FEATURE bRequest for the device instance 
 * to set feature of the hub port.
 *
 * @param intf the interface instance.
 * @port the hub port.
 * @feature feature to be set.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hub_set_port_feature(uhub_t hub, rt_uint16_t port, 
    rt_uint16_t feature)
{
    struct urequest setup;
    int timeout = USB_TIMEOUT_BASIC;
        
    /* parameter check */
    RT_ASSERT(hub != RT_NULL);

    /* clear roothub feature */
    if(hub->is_roothub)
    {
        root_hub_ctrl(hub->hcd, port, RH_SET_PORT_FEATURE, 
            (void*)(rt_uint32_t)feature);
        return RT_EOK;
    }

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_CLASS | 
        USB_REQ_TYPE_OTHER;
    setup.bRequest = USB_REQ_SET_FEATURE;
    setup.wIndex = port;
    setup.wLength = 0;
    setup.wValue = feature;

    if(rt_usb_hcd_setup_xfer(hub->hcd, hub->self->pipe_ep0_out, &setup, timeout) == 8)
    {
        return RT_EOK;
    }
    else return -RT_FALSE;        
}

/**
 * This function will rest hub port, it is invoked when sub device attached to the hub port.
 *
 * @param intf the interface instance.
 * @param port the hub port.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hub_reset_port(uhub_t hub, rt_uint16_t port)
{
    rt_err_t ret;
    rt_uint32_t pstatus;
    
    /* parameter check */
    RT_ASSERT(hub != RT_NULL);
    
    rt_thread_delay(50);

    /* reset hub port */
    ret = rt_usbh_hub_set_port_feature(hub, port, PORT_FEAT_RESET);
    if(ret != RT_EOK) return ret;

    while(1)
    {
        ret = rt_usbh_hub_get_port_status(hub, port, &pstatus);
        if(!(pstatus & PORT_PRS)) break;
    }
    
    /* clear port reset feature */
    ret = rt_usbh_hub_clear_port_feature(hub, port, PORT_FEAT_C_RESET);    
    if(ret != RT_EOK) return ret;

    rt_thread_delay(50);    

    return RT_EOK;
}

/**
 * This function will do debouce, it is invoked when sub device attached to the hub port.
 *
 * @param device the usb instance.
 * @param port the hub port.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usbh_hub_port_debounce(uhub_t hub, rt_uint16_t port)
{
    rt_err_t ret;
    int i = 0, times = 20;
    rt_uint32_t pstatus;
    rt_bool_t connect = RT_TRUE;
    int delayticks = USB_DEBOUNCE_TIME / times;
    if (delayticks < 1)
        delayticks = 1;

    /* parameter check */
    RT_ASSERT(hub != RT_NULL);

    for(i=0; i<times; i++)
    {
        ret = rt_usbh_hub_get_port_status(hub, port, &pstatus);
        if(ret != RT_EOK) return ret;
            
        if(!(pstatus & PORT_CCS)) 
        {
            connect = RT_FALSE;
            break;
        }
        
        rt_thread_delay(delayticks);
    }        

    if(connect) return RT_EOK;
    else return -RT_ERROR;
}

/**
 * This function will poll all the hub ports to detect port status, especially connect and
 * disconnect events.
 *
 * @param intf the interface instance.
 * 
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usbh_hub_port_change(uhub_t hub)
{
    int i;
    rt_bool_t reconnect;

    /* parameter check */
    RT_ASSERT(hub != RT_NULL);

    /* get usb device instance */    
    for (i = 0; i < hub->num_ports; i++)
    {
        rt_err_t ret;
        struct uinstance* device;
        rt_uint32_t pstatus = 0;

        reconnect = RT_FALSE;
        
        /* get hub port status */
        ret = rt_usbh_hub_get_port_status(hub, i + 1, &pstatus);
        if(ret != RT_EOK) continue;

        RT_DEBUG_LOG(RT_DEBUG_USB, ("port %d status 0x%x\n", i + 1, pstatus));

        /* check port status change */
        if (pstatus & PORT_CCSC) 
        {        
            /* clear port status change feature */
            rt_usbh_hub_clear_port_feature(hub, i + 1, PORT_FEAT_C_CONNECTION);
            reconnect = RT_TRUE;
        }

        if(pstatus & PORT_PESC)
        {
            rt_usbh_hub_clear_port_feature(hub, i + 1, PORT_FEAT_C_ENABLE);            
            reconnect = RT_TRUE;
        }
        
        if(reconnect)
        {            
            if(hub->child[i] != RT_NULL && hub->child[i]->status != DEV_STATUS_IDLE) 
                rt_usbh_detach_instance(hub->child[i]);
            
            ret = rt_usbh_hub_port_debounce(hub, i + 1);
            if(ret != RT_EOK) continue;
            
            /* allocate an usb instance for new connected device */
            device = rt_usbh_alloc_instance(hub->hcd);
            if(device == RT_NULL) break;
            
            /* set usb device speed */
            device->speed = (pstatus & PORT_LSDA) ? 1 : 0;
            device->parent_hub = hub;    
            device->hcd = hub->hcd;
            device->port = i + 1;
            hub->child[i] = device;

            /* reset usb roothub port */
            rt_usbh_hub_reset_port(hub, i + 1);
            
            /* attatch the usb instance to the hcd */
            rt_usbh_attatch_instance(device); 
        }
    }

    return RT_EOK;
}

/**
 * This function is the callback function of hub's int endpoint, it is invoked when data comes.
 *
 * @param context the context of the callback function.
 * 
 * @return none.
 */
static void rt_usbh_hub_irq(void* context)
{
    upipe_t pipe;
    uhub_t hub;
    int timeout = USB_TIMEOUT_BASIC;
    
    RT_ASSERT(context != RT_NULL);
    
    pipe = (upipe_t)context;
    hub = (uhub_t)pipe->user_data;

    if(pipe->status != UPIPE_STATUS_OK)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB,("hub irq error\n"));
        return;
    }
    
    rt_usbh_hub_port_change(hub);

    RT_DEBUG_LOG(RT_DEBUG_USB,("hub int xfer...\n"));

    /* parameter check */
     RT_ASSERT(pipe->inst->hcd != RT_NULL);
    
    rt_usb_hcd_pipe_xfer(hub->self->hcd, pipe, hub->buffer, pipe->ep.wMaxPacketSize, timeout);
}

/**
 * This function will run usb hub class driver when usb hub is detected and identified
 * as a hub class device, it will continue to do the enumulate process.
 *
 * @param arg the argument.
 * 
 * @return the error code, RT_EOK on successfully.
 */

static rt_err_t rt_usbh_hub_enable(void *arg)
{
    int i = 0;
    rt_err_t ret = RT_EOK;
    uep_desc_t ep_desc = RT_NULL;
    uhub_t hub;
    struct uinstance* device;
    struct uhintf* intf = (struct uhintf*)arg;
    upipe_t pipe_in = RT_NULL;
    int timeout = USB_TIMEOUT_LONG;
    /* paremeter check */
    RT_ASSERT(intf != RT_NULL);
    
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_hub_run\n"));

    /* get usb device instance */
    device = intf->device;

    /* create a hub instance */
    hub = rt_malloc(sizeof(struct uhub));
    rt_memset(hub, 0, sizeof(struct uhub));
    
    /* make interface instance's user data point to hub instance */
    intf->user_data = (void*)hub;

    /* get hub descriptor head */
    ret = rt_usbh_hub_get_descriptor(device, (rt_uint8_t*)&hub->hub_desc, 8);
    if(ret != RT_EOK)
    {
        rt_kprintf("get hub descriptor failed\n");
        return -RT_ERROR;        
    }

    /* get full hub descriptor */
    ret = rt_usbh_hub_get_descriptor(device, (rt_uint8_t*)&hub->hub_desc, 
        hub->hub_desc.length);
    if(ret != RT_EOK)
    {
        rt_kprintf("get hub descriptor again failed\n");
        return -RT_ERROR;        
    }    

    /* get hub ports number */
    hub->num_ports = hub->hub_desc.num_ports;
    hub->hcd = device->hcd;
    hub->self = device;

    /* reset all hub ports */
    for (i = 0; i < hub->num_ports; i++)
    {
        rt_usbh_hub_set_port_feature(hub, i + 1, PORT_FEAT_POWER);
        rt_thread_delay(hub->hub_desc.pwron_to_good
            * 2 * RT_TICK_PER_SECOND / 1000 );
    }

    if(intf->intf_desc->bNumEndpoints != 1) 
        return -RT_ERROR;

    /* get endpoint descriptor from interface descriptor */
    rt_usbh_get_endpoint_descriptor(intf->intf_desc, 0, &ep_desc);
    if(ep_desc == RT_NULL)
    {
        rt_kprintf("rt_usb_get_endpoint_descriptor error\n");
        return -RT_ERROR;
    }

    /* the endpoint type of hub class should be interrupt */        
    if( USB_EP_ATTR(ep_desc->bmAttributes) == USB_EP_ATTR_INT)
    {
        /* the endpoint direction of hub class should be in */
        if(ep_desc->bEndpointAddress & USB_DIR_IN)
        {    
            /* allocate a pipe according to the endpoint type */
            pipe_in = rt_usb_instance_find_pipe(device,ep_desc->bEndpointAddress);
            if(pipe_in == RT_NULL)
            {
                return RT_ERROR;
            }
            rt_usb_pipe_add_callback(pipe_in,rt_usbh_hub_irq);
        }
        else return -RT_ERROR;
    }

    /* parameter check */
    RT_ASSERT(device->hcd != RT_NULL);
    pipe_in->user_data = hub;
    rt_usb_hcd_pipe_xfer(hub->hcd, pipe_in, hub->buffer, 
        pipe_in->ep.wMaxPacketSize, timeout);
    return RT_EOK;
}

/**
 * This function will be invoked when usb hub plug out is detected and it would clean 
 * and release all hub class related resources.
 *
 * @param arg the argument.
 * 
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usbh_hub_disable(void* arg)
{
    int i;
    uhub_t hub;
    struct uhintf* intf = (struct uhintf*)arg;

    /* paremeter check */
    RT_ASSERT(intf != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usbh_hub_stop\n"));
    hub = (uhub_t)intf->user_data;

    for(i=0; i<hub->num_ports; i++)
    {
        if(hub->child[i] != RT_NULL)
            rt_usbh_detach_instance(hub->child[i]);
    }
    
    if(hub != RT_NULL) rt_free(hub);
    if(intf != RT_NULL) rt_free(intf);

    return RT_EOK;
}

/**
 * This function will register hub class driver to the usb class driver manager.
 * and it should be invoked in the usb system initialization.
 * 
 * @return the error code, RT_EOK on successfully.
 */
ucd_t rt_usbh_class_driver_hub(void)
{    
    hub_driver.class_code = USB_CLASS_HUB;
    
    hub_driver.enable = rt_usbh_hub_enable;
    hub_driver.disable = rt_usbh_hub_disable;

    return &hub_driver;
}

/**
 * This function is the main entry of usb hub thread, it is in charge of 
 * processing all messages received from the usb message buffer.  
 *
 * @param parameter the parameter of the usb host thread.
 * 
 * @return none.
 */
static void rt_usbh_hub_thread_entry(void* parameter)
{    
    while(1)
    {    
        struct uhost_msg msg;
        
        /* receive message */
        if(rt_mq_recv(usb_mq, &msg, sizeof(struct uhost_msg), RT_WAITING_FOREVER) 
            != RT_EOK ) continue;

        //RT_DEBUG_LOG(RT_DEBUG_USB, ("msg type %d\n", msg.type));
        
        switch (msg.type)
        {        
        case USB_MSG_CONNECT_CHANGE:
            rt_usbh_hub_port_change(msg.content.hub);
            break;
        case USB_MSG_CALLBACK:
            /* invoke callback */
            msg.content.cb.function(msg.content.cb.context);
            break;
        default:
            break;
        }            
    }
}

/**
 * This function will post an message to the usb message queue,
 *
 * @param msg the message to be posted
 * 
 * @return the error code, RT_EOK on successfully. 
 */
rt_err_t rt_usbh_event_signal(struct uhost_msg* msg)
{
    RT_ASSERT(msg != RT_NULL);

    /* send message to usb message queue */
    rt_mq_send(usb_mq, (void*)msg, sizeof(struct uhost_msg));

    return RT_EOK;
}

/**
 * This function will initialize usb hub thread.
 *
 * @return none.
 * 
 */
void rt_usbh_hub_init(uhcd_t hcd)
{
    rt_thread_t thread;
    /* link root hub to hcd */
    root_hub.is_roothub = RT_TRUE;
    hcd->roothub = &root_hub;
    root_hub.hcd = hcd;
    root_hub.num_ports = hcd->num_ports;
    /* create usb message queue */
    usb_mq = rt_mq_create("usbh", 32, 16, RT_IPC_FLAG_FIFO);
    
    /* create usb hub thread */
    thread = rt_thread_create("usbh", rt_usbh_hub_thread_entry, RT_NULL, 
        USB_THREAD_STACK_SIZE, 8, 20);
    if(thread != RT_NULL)
    {
        /* startup usb host thread */
        rt_thread_startup(thread);
    }
}

