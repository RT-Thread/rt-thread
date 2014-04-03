/*
 * File      : hub.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Development Team
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
 * 2011-12-12     Yi Qiu      first version
 */

#include <rtthread.h>
#include <drivers/usb_host.h>

#define USB_THREAD_STACK_SIZE    2048

static struct rt_messagequeue *usb_mq;
static struct uclass_driver hub_driver;

/**
 * This function will do USB_REQ_GET_DESCRIPTOR request for the device instance 
 * to get usb hub descriptor.
 *
 * @param ifinst the interface instance.
 * @buffer the data buffer to save usb hub descriptor.
 * @param nbytes the size of buffer
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usb_hub_get_descriptor(uinst_t uinst, rt_uint8_t *buffer, 
    rt_size_t nbytes)
{
    struct ureqest setup;
    int timeout = 100;
        
    /* parameter check */
    RT_ASSERT(uinst != RT_NULL);
    
    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_CLASS | 
        USB_REQ_TYPE_DEVICE;
    setup.request = USB_REQ_GET_DESCRIPTOR;
    setup.index = 0;
    setup.length = nbytes;
    setup.value = USB_DESC_TYPE_HUB << 8;

    if(rt_usb_hcd_control_xfer(uinst->hcd, uinst, &setup, buffer, nbytes, 
        timeout) == nbytes) return RT_EOK;
    else return -RT_FALSE;    
}

/**
 * This function will do USB_REQ_GET_STATUS request for the device instance 
 * to get usb hub status.
 *
 * @param ifinst the interface instance.
 * @buffer the data buffer to save usb hub status.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usb_hub_get_status(uinst_t uinst, rt_uint8_t* buffer)
{
    struct ureqest setup;
    int timeout = 100;
    int length = 4;
    
    /* parameter check */
    RT_ASSERT(uinst != RT_NULL);

    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_CLASS | 
        USB_REQ_TYPE_DEVICE;
    setup.request = USB_REQ_GET_STATUS;
    setup.index = 0;
    setup.length = length;
    setup.value = 0;

    if(rt_usb_hcd_control_xfer(uinst->hcd, uinst, &setup, buffer, length, 
        timeout) == length) return RT_EOK;
    else return -RT_FALSE;    
}

/**
 * This function will do USB_REQ_GET_STATUS request for the device instance 
 * to get hub port status.
 *
 * @param ifinst the interface instance.
 * @port the hub port to get status.
 * @buffer the data buffer to save usb hub status.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usb_hub_get_port_status(uhubinst_t uhub, rt_uint16_t port, 
    rt_uint8_t* buffer)
{
    struct ureqest setup;
    int timeout = 100;
    int length = 4;
    
    /* parameter check */
    RT_ASSERT(uhub != RT_NULL);

    /* get roothub port status */
    if(uhub->is_roothub)
    {
        rt_usb_hcd_hub_control(uhub->hcd, port, RH_GET_PORT_STATUS, 
            (void*)buffer);
        return RT_EOK;
    }

    setup.request_type = USB_REQ_TYPE_DIR_IN | USB_REQ_TYPE_CLASS | 
        USB_REQ_TYPE_OTHER;
    setup.request = USB_REQ_GET_STATUS;
    setup.index = port;
    setup.length = 4;
    setup.value = 0;

    if(rt_usb_hcd_control_xfer(uhub->hcd, uhub->self, &setup, buffer, 
        length, timeout) == timeout) return RT_EOK;
    else return -RT_FALSE;        
}

/**
 * This function will do USB_REQ_CLEAR_FEATURE request for the device instance 
 * to clear feature of the hub port.
 *
 * @param ifinst the interface instance.
 * @port the hub port.
 * @feature feature to be cleared.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usb_hub_clear_port_feature(uhubinst_t uhub, rt_uint16_t port, 
    rt_uint16_t feature)
{
    struct ureqest setup;
    int timeout = 100;
        
    /* parameter check */
    RT_ASSERT(uhub != RT_NULL);

    /* clear roothub feature */
    if(uhub->is_roothub)
    {
        rt_usb_hcd_hub_control(uhub->hcd, port, RH_CLEAR_PORT_FEATURE, 
            (void*)feature);
        return RT_EOK;
    }

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_CLASS | 
        USB_REQ_TYPE_OTHER;
    setup.request = USB_REQ_CLEAR_FEATURE;
    setup.index = port;
    setup.length = 0;
    setup.value = feature;

    if(rt_usb_hcd_control_xfer(uhub->hcd, uhub->self, &setup, RT_NULL, 0, 
        timeout) == 0) return RT_EOK;
    else return -RT_FALSE;    
}

/**
 * This function will do USB_REQ_SET_FEATURE request for the device instance 
 * to set feature of the hub port.
 *
 * @param ifinst the interface instance.
 * @port the hub port.
 * @feature feature to be set.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usb_hub_set_port_feature(uhubinst_t uhub, rt_uint16_t port, 
    rt_uint16_t feature)
{
    struct ureqest setup;
    int timeout = 100;
        
    /* parameter check */
    RT_ASSERT(uhub != RT_NULL);

    /* clear roothub feature */
    if(uhub->is_roothub)
    {
        rt_usb_hcd_hub_control(uhub->hcd, port, RH_SET_PORT_FEATURE, 
            (void*)feature);
        return RT_EOK;
    }

    setup.request_type = USB_REQ_TYPE_DIR_OUT | USB_REQ_TYPE_CLASS | 
        USB_REQ_TYPE_OTHER;
    setup.request = USB_REQ_SET_FEATURE;
    setup.index = port;
    setup.length = 0;
    setup.value = feature;

    if(rt_usb_hcd_control_xfer(uhub->hcd, uhub->self, &setup, RT_NULL, 0, 
        timeout) == 0) return RT_EOK;
    else return -RT_FALSE;        
}

/**
 * This function will rest hub port, it is invoked when sub device attached to the hub port.
 *
 * @param ifinst the interface instance.
 * @param port the hub port.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usb_hub_reset_port(uhubinst_t uhub, rt_uint16_t port)
{
    rt_err_t ret;
    rt_uint32_t pstatus;
    
    /* parameter check */
    RT_ASSERT(uhub != RT_NULL);
    
    rt_thread_delay(50);

    /* reset hub port */
    ret = rt_usb_hub_set_port_feature(uhub, port, PORT_FEAT_RESET);
    if(ret != RT_EOK) return ret;

    while(1)
    {
        ret = rt_usb_hub_get_port_status(uhub, port, (rt_uint8_t*)&pstatus);
        if(!(pstatus & PORT_PRS)) break;
    }
    
    /* clear port reset feature */
    ret = rt_usb_hub_clear_port_feature(uhub, port, PORT_FEAT_C_RESET);    
    if(ret != RT_EOK) return ret;

    rt_thread_delay(50);    

    return RT_EOK;
}

/**
 * This function will do debouce, it is invoked when sub device attached to the hub port.
 *
 * @param uinst the usb instance.
 * @param port the hub port.
 * 
 * @return the error code, RT_EOK on successfully.
 */
rt_err_t rt_usb_hub_port_debounce(uhubinst_t uhub, rt_uint16_t port)
{
    rt_err_t ret;
    int i = 0, times = 20;
    rt_uint32_t pstatus;
    rt_bool_t connect = RT_TRUE;

    /* parameter check */
    RT_ASSERT(uhub != RT_NULL);

    for(i=0; i<times; i++)
    {
        ret = rt_usb_hub_get_port_status(uhub, port, (rt_uint8_t*)&pstatus);
        if(ret != RT_EOK) return ret;
            
        if(!(pstatus & PORT_CCS)) 
        {
            connect = RT_FALSE;
            break;
        }
        
        rt_thread_delay(1);
    }        

    if(connect) return RT_EOK;
    else return -RT_ERROR;
}

/**
 * This function will poll all the hub ports to detect port status, especially connect and
 * disconnect events.
 *
 * @param ifinst the interface instance.
 * 
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usb_hub_port_change(uhubinst_t uhub)
{
    int i;
    rt_bool_t reconnect;

    /* parameter check */
    RT_ASSERT(uhub != RT_NULL);

    /* get usb device instance */    
    for (i = 0; i < uhub->num_ports; i++)
    {
        rt_err_t ret;
        uinst_t uinst;
        rt_uint32_t pstatus = 0;

        reconnect = RT_FALSE;
        
        /* get hub port status */
        ret = rt_usb_hub_get_port_status(uhub, i + 1, (rt_uint8_t*)&pstatus);
        if(ret != RT_EOK) continue;

        RT_DEBUG_LOG(RT_DEBUG_USB, ("port_status 0x%x\n", pstatus));

        /* check port status change */
        if ((pstatus & PORT_CCSC)) 
        {        
            /* clear port status change feature */
            rt_usb_hub_clear_port_feature(uhub, i + 1, PORT_FEAT_C_CONNECTION);
            reconnect = RT_TRUE;
        }

        if(pstatus & PORT_PESC)
        {
            rt_usb_hub_clear_port_feature(uhub, i + 1, PORT_FEAT_C_ENABLE);            
            reconnect = RT_TRUE;
        }
        
        if(reconnect)
        {            
            if(uhub->child[i]->status != UINST_STATUS_IDLE) 
                rt_usb_detach_instance(uhub->child[i]);
            
            ret = rt_usb_hub_port_debounce(uhub, i + 1);
            if(ret != RT_EOK) continue;
            
            /* allocate an usb instance for new connected device */
            uinst = rt_usb_alloc_instance();
            if(uinst == RT_NULL) break;
            
            /* set usb device speed */
            uinst->speed = (pstatus & PORT_LSDA) ? 1 : 0;
            uinst->parent = uhub;    
            uinst->hcd = uhub->hcd;
            uhub->child[i] = uinst;

            /* reset usb roothub port */
            rt_usb_hub_reset_port(uhub, i + 1);
            
            /* attatch the usb instance to the hcd */
            rt_usb_attatch_instance(uinst); 
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
static void rt_usb_hub_irq(void* context)
{
    upipe_t pipe; 
    uifinst_t ifinst;
    uhubinst_t uhub;
    int timeout = 100;
    
    RT_ASSERT(context != RT_NULL);
    
    pipe = (upipe_t)context;
    ifinst = pipe->ifinst;
    uhub = (uhubinst_t)ifinst->user_data;

    if(pipe->status != UPIPE_STATUS_OK)
    {
        rt_kprintf("hub irq error\n");
        return;
    }
    
    rt_usb_hub_port_change(uhub);

    rt_kprintf("hub int xfer...\n");

    /* parameter check */
     RT_ASSERT(pipe->ifinst->uinst->hcd != RT_NULL);
    
    rt_usb_hcd_int_xfer(ifinst->uinst->hcd, pipe, uhub->buffer, 
        pipe->ep.wMaxPacketSize, timeout);
}

/**
 * This function will run usb hub class driver when usb hub is detected and identified
 * as a hub class device, it will continue to do the enumulate process.
 *
 * @param arg the argument.
 * 
 * @return the error code, RT_EOK on successfully.
 */
static rt_err_t rt_usb_hub_run(void *arg)
{
    int i = 0;
    rt_err_t ret = RT_EOK;
    uep_desc_t ep_desc;
    uhubinst_t uhub;
    uinst_t uinst;
    uifinst_t ifinst = (uifinst_t)arg;
    int timeout = 300;

    /* paremeter check */
    RT_ASSERT(ifinst != RT_NULL);
    
    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usb_hub_run\n"));

    /* get usb device instance */
    uinst = ifinst->uinst;

    /* create a hub instance */
    uhub = rt_malloc(sizeof(struct uhubinst));
    rt_memset(uhub, 0, sizeof(struct uhubinst));
    
    /* make interface instance's user data point to hub instance */
    ifinst->user_data = (void*)uhub;

    /* get hub descriptor head */
    ret = rt_usb_hub_get_descriptor(uinst, (rt_uint8_t*)&uhub->hub_desc, 8);
    if(ret != RT_EOK)
    {
        rt_kprintf("get hub descriptor failed\n");
        return -RT_ERROR;        
    }

    /* get full hub descriptor */
    ret = rt_usb_hub_get_descriptor(uinst, (rt_uint8_t*)&uhub->hub_desc, 
        uhub->hub_desc.length);
    if(ret != RT_EOK)
    {
        rt_kprintf("get hub descriptor again failed\n");
        return -RT_ERROR;        
    }    

    /* get hub ports number */
    uhub->num_ports = uhub->hub_desc.num_ports;
    uhub->hcd = uinst->hcd;
    uhub->self = uinst;

    /* reset all hub ports */
    for (i = 0; i < uhub->num_ports; i++)
    {
        rt_usb_hub_set_port_feature(uhub, i + 1, PORT_FEAT_POWER);
        rt_thread_delay(uhub->hub_desc.pwron_to_good
            * 2 * RT_TICK_PER_SECOND / 1000 );
    }

    if(ifinst->intf_desc->bNumEndpoints != 1) 
        return -RT_ERROR;

    /* get endpoint descriptor from interface descriptor */
    rt_usb_get_endpoint_descriptor(ifinst->intf_desc, 0, &ep_desc);
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
            rt_usb_hcd_alloc_pipe(uinst->hcd, &uhub->pipe_in, ifinst, 
                ep_desc, rt_usb_hub_irq);
        }
        else return -RT_ERROR;
    }

    /* parameter check */
     RT_ASSERT(uinst->hcd != RT_NULL);
    
    rt_usb_hcd_int_xfer(uinst->hcd, uhub->pipe_in, uhub->buffer, 
        uhub->pipe_in->ep.wMaxPacketSize, timeout);
    
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
static rt_err_t rt_usb_hub_stop(void* arg)
{
    int i;
    uhubinst_t uhub;
    uinst_t uinst;
    uifinst_t ifinst = (uifinst_t)arg;

    /* paremeter check */
    RT_ASSERT(ifinst != RT_NULL);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("rt_usb_hub_stop\n"));

    uinst = ifinst->uinst;
    uhub = (uhubinst_t)ifinst->user_data;

    if(uhub->pipe_in != RT_NULL)
        rt_usb_hcd_free_pipe(uinst->hcd, uhub->pipe_in);

    for(i=0; i<uhub->num_ports; i++)
    {
        if(uhub->child[i] != RT_NULL)
            rt_usb_detach_instance(uhub->child[i]);
    }
    
    if(uhub != RT_NULL) rt_free(uhub);
    if(ifinst != RT_NULL) rt_free(ifinst);

    return RT_EOK;
}

/**
 * This function will register hub class driver to the usb class driver manager.
 * and it should be invoked in the usb system initialization.
 * 
 * @return the error code, RT_EOK on successfully.
 */
ucd_t rt_usb_class_driver_hub(void)
{    
    hub_driver.class_code = USB_CLASS_HUB;
    
    hub_driver.run = rt_usb_hub_run;
    hub_driver.stop = rt_usb_hub_stop;

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
static void rt_usb_hub_thread_entry(void* parameter)
{    
    while(1)
    {    
        struct uhost_msg msg;
        
        /* receive message */
        if(rt_mq_recv(usb_mq, &msg, sizeof(struct uhost_msg), RT_WAITING_FOREVER) 
            != RT_EOK ) continue;

        RT_DEBUG_LOG(RT_DEBUG_USB, ("msg type %d\n", msg.type));
        
        switch (msg.type)
        {        
        case USB_MSG_CONNECT_CHANGE:
            rt_usb_hub_port_change(msg.content.uhub);
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
 * @param size the size of the message .
 * 
 * @return the error code, RT_EOK on successfully. 
 */
rt_err_t rt_usb_post_event(struct uhost_msg* msg, rt_size_t size)
{
    RT_ASSERT(msg != RT_NULL);

    /* send message to usb message queue */
    rt_mq_send(usb_mq, (void*)msg, size);

    return RT_EOK;
}

/**
 * This function will initialize usb hub thread.
 *
 * @return none.
 * 
 */
void rt_usb_hub_thread(void)
{
    rt_thread_t thread;
    
    /* create usb message queue */
    usb_mq = rt_mq_create("usbh", 32, 16, RT_IPC_FLAG_FIFO);
    
    /* create usb hub thread */
    thread = rt_thread_create("usbh", rt_usb_hub_thread_entry, RT_NULL, 
        USB_THREAD_STACK_SIZE, 8, 20);
    if(thread != RT_NULL)
    {
        /* startup usb host thread */
        rt_thread_startup(thread);
    }
}

