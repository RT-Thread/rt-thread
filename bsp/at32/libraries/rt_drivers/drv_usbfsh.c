/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-28     leo          first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"

#if defined(BSP_USING_HOST_USBFS1) || defined(BSP_USING_HOST_USBFS2)
#include "usbh_int.h"
#include "drv_usbfs.h"
#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG             "drv.usb"
#include <drv_log.h>

static struct rt_completion urb_completion;
static volatile rt_bool_t connect_status = RT_FALSE;
static struct at32_usbfs *p_usbfs_instance = RT_NULL;

enum
{
#ifdef BSP_USING_HOST_USBFS1
    USBFS1_INDEX,
#endif
#ifdef BSP_USING_HOST_USBFS2
    USBFS2_INDEX,
#endif
};

static struct at32_usbfs usbfsh_config[] = {
#ifdef BSP_USING_HOST_USBFS1
    USBFS1_CONFIG,
#endif
#ifdef BSP_USING_HOST_USBFS2
    USBFS2_CONFIG,
#endif
};

#ifdef BSP_USING_HOST_USBFS1
void OTGFS1_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usbh_irq_handler(p_usbfs_instance->p_otg_core);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

#ifdef BSP_USING_HOST_USBFS2
void OTGFS2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    usbh_irq_handler(p_usbfs_instance->p_otg_core);

    /* leave interrupt */
    rt_interrupt_leave();
}
#endif

void usbh_connect_callback(usbh_core_type *uhost)
{
    uhcd_t hcd = (uhcd_t)uhost->pdata;
    if (!connect_status)
    {
        connect_status = RT_TRUE;
        RT_DEBUG_LOG(RT_DEBUG_USB, ("usb connected\n"));
        rt_usbh_root_hub_connect_handler(hcd, 1, RT_FALSE);
    }
}

void usbh_disconnect_callback(usbh_core_type *uhost)
{
    uhcd_t hcd = (uhcd_t)uhost->pdata;
    if (connect_status)
    {
        connect_status = RT_FALSE;
        RT_DEBUG_LOG(RT_DEBUG_USB, ("usb disconnnect\n"));
        rt_usbh_root_hub_disconnect_handler(hcd, 1);
    }
}

void usbd_notify_urbchange_callback(usbh_core_type *uhost, uint8_t chnum, urb_sts_type sts)
{
    rt_completion_done(&urb_completion);
}

static rt_err_t drv_reset_port(rt_uint8_t port)
{
    RT_DEBUG_LOG(RT_DEBUG_USB, ("reset port\n"));
    usbh_reset_port(&p_usbfs_instance->p_otg_core->host);
    return RT_EOK;
}

static int drv_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeouts)
{
    int timeout = timeouts;

    while(1)
    {
        if(!connect_status)
        {
            return -1;
        }
        rt_completion_init(&urb_completion);

        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].dir = (pipe->ep.bEndpointAddress & 0x80) >> 7;

        if(token == 0U)
        {
            p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_SETUP;
        }
        else
        {
            p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA1;
        }

        /* endpoint type */
        switch(pipe->ep.bmAttributes)
        {
            /* endpoint is control type */
            case EPT_CONTROL_TYPE:
                if((token == 1U) && (((pipe->ep.bEndpointAddress & 0x80) >> 7) == 0U))
                {
                    if(nbytes == 0U)
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].toggle_out = 1U;
                    }
                    if((&p_usbfs_instance->p_otg_core->host)->hch[pipe->pipe_index].toggle_out == 0U)
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA0;
                    }
                    else
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA1;
                    }
                }
                break;
            /* endpoint is bulk type */
            case EPT_BULK_TYPE:
                if(((pipe->ep.bEndpointAddress & 0x80) >> 7) == 0U)
                {
                    if( p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].toggle_out == 0U)
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA0;
                    }
                    else
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA1;
                    }
                }
                else
                {
                    if( p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].toggle_in == 0U)
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA0;
                    }
                    else
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA1;
                    }
                }
                break;
            /* endpoint is int type */
            case  EPT_INT_TYPE:
                if(((pipe->ep.bEndpointAddress & 0x80) >> 7) == 0U)
                {
                    if( p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].toggle_out == 0U)
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA0;
                    }
                    else
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA1;
                    }
                }
                else
                {
                    if( p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].toggle_in == 0U)
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA0;
                    }
                    else
                    {
                        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA1;
                    }
                }
                break;
            /* endpoint is isoc type */
            case EPT_ISO_TYPE:
                p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].data_pid = HCH_PID_DATA0;
                break;

            default:
                break;
        }

        /* set transfer buffer */
        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].trans_buf = buffer;
        /* set transfer len*/
        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].trans_len = nbytes;
        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].urb_sts = URB_IDLE;
        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].ch_num = pipe->pipe_index;
        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].trans_count = 0;
        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].state = HCH_IDLE;

        /* data in/out for host */
        usbh_in_out_request((&p_usbfs_instance->p_otg_core->host), pipe->pipe_index);

        rt_completion_wait(&urb_completion, timeout);
        rt_thread_mdelay(1);

        if(usbh_get_status((&p_usbfs_instance->p_otg_core->host), pipe->pipe_index) == HCH_NAK)
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("nak\n"));
            if (pipe->ep.bmAttributes == USB_EP_ATTR_INT)
            {
                rt_thread_delay((pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) > 0 ? (pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) : 1);
            }
            usb_hch_halt((&p_usbfs_instance->p_otg_core->host)->usb_reg, pipe->pipe_index);

            usbh_hc_open(&p_usbfs_instance->p_otg_core->host,
                         pipe->pipe_index,
                         pipe->ep.bEndpointAddress,
                         pipe->inst->address,
                         pipe->ep.bmAttributes,
                         pipe->ep.wMaxPacketSize,
                         USB_PRTSPD_FULL_SPEED);
            continue;
        }
        else if (usbh_get_status(&p_usbfs_instance->p_otg_core->host, pipe->pipe_index) == HCH_STALL)
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("stall\n"));
            pipe->status = UPIPE_STATUS_STALL;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            return -1;
        }
        else if (usbh_get_status(&p_usbfs_instance->p_otg_core->host, pipe->pipe_index) == URB_ERROR)
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("error\n"));
            pipe->status = UPIPE_STATUS_ERROR;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            return -1;
        }
        else if(URB_DONE == usbh_get_urb_status(&p_usbfs_instance->p_otg_core->host, pipe->pipe_index))
        {
            RT_DEBUG_LOG(RT_DEBUG_USB, ("ok\n"));
            pipe->status = UPIPE_STATUS_OK;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            size_t size = (&p_usbfs_instance->p_otg_core->host)->hch[pipe->pipe_index].trans_count;
            if (pipe->ep.bEndpointAddress & 0x80)
            {
                return size;
            }
            else if (pipe->ep.bEndpointAddress & 0x00)
            {
                return size;
            }
            return nbytes;
        }
        continue;
    }
}

static rt_uint16_t pipe_index = 0;
static rt_uint8_t  drv_get_free_pipe_index(void)
{
    rt_uint8_t idx;
    for (idx = 1; idx < 16; idx++)
    {
        if (!(pipe_index & (0x01 << idx)))
        {
            pipe_index |= (0x01 << idx);
            return idx;
        }
    }
    return 0xff;
}

static void drv_free_pipe_index(rt_uint8_t index)
{
    pipe_index &= ~(0x01 << index);
}

static rt_err_t drv_open_pipe(upipe_t pipe)
{
    pipe->pipe_index = drv_get_free_pipe_index();
    usbh_hc_open(&p_usbfs_instance->p_otg_core->host,
                 pipe->pipe_index,
                 pipe->ep.bEndpointAddress,
                 pipe->inst->address,
                 pipe->ep.bmAttributes,
                 pipe->ep.wMaxPacketSize,
                 USB_PRTSPD_FULL_SPEED);
    /* set data0 pid token*/
    if (p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].dir)
    {
        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].toggle_in = 0;
    }
    else
    {
        p_usbfs_instance->p_otg_core->host.hch[pipe->pipe_index].toggle_out = 0;
    }
    return RT_EOK;
}

static rt_err_t drv_close_pipe(upipe_t pipe)
{
    usb_hch_halt((&p_usbfs_instance->p_otg_core->host)->usb_reg, pipe->pipe_index);
    drv_free_pipe_index(pipe->pipe_index);
    return RT_EOK;
}

static struct uhcd_ops _uhcd_ops =
{
    drv_reset_port,
    drv_pipe_xfer,
    drv_open_pipe,
    drv_close_pipe,
};

static rt_err_t at32_hcd_init(rt_device_t device)
{
    /* usb gpio config */
    at32_msp_usb_init(device);

    /* enable otgfs irq */
    nvic_irq_enable(p_usbfs_instance->irqn, 2, 0);

    /* init usb */
    usbh_init(p_usbfs_instance->p_otg_core,
              USB_FULL_SPEED_CORE_ID,
              p_usbfs_instance->id);
    return RT_EOK;
}

int at32_usbh_register(void)
{
    rt_size_t obj_num;
    rt_err_t result = 0;
    int index;

    obj_num = sizeof(usbfsh_config) / sizeof(struct at32_usbfs);

    for (index = 0; index < obj_num; index++) {
        uhcd_t uhcd = (uhcd_t)rt_malloc(sizeof(struct uhcd));
        if (uhcd == RT_NULL)
        {
            rt_kprintf("uhcd malloc failed\r\n");
            return -RT_ERROR;
        }
        rt_memset((void *)uhcd, 0, sizeof(struct uhcd));

        otg_core_type *p_otg_core = (otg_core_type *)rt_malloc(sizeof(otg_core_type));
        if (p_otg_core == RT_NULL)
        {
            rt_kprintf("otg_core malloc failed\r\n");
            return -RT_ERROR;
        }
        rt_memset((void *)p_otg_core, 0, sizeof(otg_core_type));

        uhcd->parent.type = RT_Device_Class_USBHost;
        uhcd->parent.init = at32_hcd_init;
        uhcd->parent.user_data = &(p_otg_core->host);

        uhcd->ops = &_uhcd_ops;
        uhcd->num_ports = 1;
        p_otg_core->host.pdata = uhcd;
        usbfsh_config[index].p_otg_core = p_otg_core;

        result = rt_device_register(&uhcd->parent, usbfsh_config[index].name, RT_DEVICE_FLAG_DEACTIVATE);
        RT_ASSERT(result == RT_EOK);

        p_usbfs_instance = &usbfsh_config[index];

        result = rt_usb_host_init(usbfsh_config[index].name);
        RT_ASSERT(result == RT_EOK);
    }

    return result;
}

INIT_DEVICE_EXPORT(at32_usbh_register);

#endif
