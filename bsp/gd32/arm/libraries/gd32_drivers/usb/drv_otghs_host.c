/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 * 2026-09-01     CYFS         start host after filesystem initialization
 */

#include "drv_otghs_host.h"
#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#include "drv_usb_hw.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
#endif

#if defined(BSP_USING_USB) && defined(RT_USING_USB_HOST)

#define OTG_FS_PORT 1

usb_core_driver gd_usb_host_core;
#define gd_usb_core gd_usb_host_core

static struct rt_completion urb_completion;
static volatile rt_bool_t connect_status = RT_FALSE;
volatile rt_uint32_t gd_usbh_irq_count;

void usbh_connect_callback(usb_core_driver *hhcd)
{
    uhcd_t hcd = (uhcd_t)hhcd->host.data;
    if (!connect_status)
    {
        connect_status = RT_TRUE;
        rt_usbh_root_hub_connect_handler(hcd, OTG_FS_PORT, RT_FALSE);
    }
}

void usbh_disconnect_callback(usb_core_driver *hhcd)
{
    uhcd_t hcd = (uhcd_t)hhcd->host.data;
    if (connect_status)
    {
        connect_status = RT_FALSE;
        rt_usbh_root_hub_disconnect_handler(hcd, OTG_FS_PORT);
    }
}

void usbh_hc_notifyurbchange_callback(usb_core_driver *hhcd, uint8_t chnum, usb_urb_state urb_state)
{
    rt_completion_done(&urb_completion);
}

static rt_err_t drv_reset_port(rt_uint8_t port)
{
    usb_port_reset(&gd_usb_core);

    return RT_EOK;
}

static int drv_pipe_xfer(upipe_t pipe, rt_uint8_t token, void *buffer, int nbytes, int timeout)
{
    while (1)
    {
        uint8_t dir = (pipe->ep.bEndpointAddress & 0x80) >> 7;

        if (!connect_status)
        {
            return -1;
        }

        rt_completion_init(&urb_completion);

        if (dir == 0)
        {
            if (token == 0)
            {
                usbh_ctlsetup_send(&gd_usb_core, buffer, pipe->pipe_index);
            }
            else
            {
                usbh_data_send(&gd_usb_core, buffer, pipe->pipe_index, nbytes);
            }
        }
        else
        {
            usbh_data_recev(&gd_usb_core, buffer, pipe->pipe_index, nbytes);
        }


        rt_completion_wait(&urb_completion, timeout);

        rt_thread_mdelay(1);

        if (usbh_urbstate_get(&gd_usb_core, pipe->pipe_index) == URB_NOTREADY)
        {
            if (pipe->ep.bmAttributes == USB_EP_ATTR_INT)
            {
                rt_thread_delay((pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) > 0 ? (pipe->ep.bInterval * RT_TICK_PER_SECOND / 1000) : 1);
            }

            usb_pipe_halt(&gd_usb_core, pipe->pipe_index);

            usbh_pipe_create(&gd_usb_core,
                             pipe->inst->address,
                             (uint8_t)PORT_SPEED_FULL,
                             pipe->pipe_index,
                             pipe->ep.bEndpointAddress,
                             pipe->ep.bmAttributes,
                             pipe->ep.wMaxPacketSize);
            continue;
        }
        else if (usbh_urbstate_get(&gd_usb_core, pipe->pipe_index) == URB_STALL)
        {
            pipe->status = UPIPE_STATUS_STALL;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            return -1;
        }
        else if (usbh_urbstate_get(&gd_usb_core, pipe->pipe_index) == URB_ERROR)
        {
            pipe->status = UPIPE_STATUS_ERROR;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            return -1;
        }
        else if (usbh_urbstate_get(&gd_usb_core, pipe->pipe_index) == URB_DONE)
        {
            pipe->status = UPIPE_STATUS_OK;
            if (pipe->callback != RT_NULL)
            {
                pipe->callback(pipe);
            }
            if (pipe->ep.bEndpointAddress & 0x80)
            {
                return usbh_xfercount_get(&gd_usb_core, pipe->pipe_index);
            }
            return nbytes;
        }
        return -1;
    }
}

static rt_uint16_t pipe_index = 0;
static rt_uint8_t drv_get_free_pipe_index()
{
    rt_uint8_t idx;
    for (idx = 0; idx < USBHS_MAX_CHANNEL_COUNT; idx++)
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
    if (index < USBHS_MAX_CHANNEL_COUNT)
    {
        pipe_index &= ~(0x01 << index);
    }
}

static rt_err_t drv_open_pipe(upipe_t pipe)
{
    pipe->pipe_index = drv_get_free_pipe_index();
    if (pipe->pipe_index == 0xff)
    {
        return -RT_ERROR;
    }

    usbh_pipe_create(&gd_usb_core,
                     pipe->inst->address,
                     (uint8_t)PORT_SPEED_FULL,
                     pipe->pipe_index,
                     pipe->ep.bEndpointAddress,
                     pipe->ep.bmAttributes,
                     pipe->ep.wMaxPacketSize);

    /* Set DATA0 PID token*/
    if (gd_usb_core.host.pipe[pipe->pipe_index].ep.dir)
    {
        gd_usb_core.host.pipe[pipe->pipe_index].data_toggle_in = 0;
    }
    else
    {
        gd_usb_core.host.pipe[pipe->pipe_index].data_toggle_out = 0;
    }

    return RT_EOK;
}

static rt_err_t drv_close_pipe(upipe_t pipe)
{
    usb_pipe_halt(&gd_usb_core, pipe->pipe_index);

    drv_free_pipe_index(pipe->pipe_index);

    return RT_EOK;
}

struct uhcd_ops _uhcd_ops = {
    drv_reset_port,
    drv_pipe_xfer,
    drv_open_pipe,
    drv_close_pipe,
};

static rt_err_t gd32_hcd_init(rt_device_t device)
{
    usb_rcu_config(USBHS1);

    /* configure GPIO pin used for switching VBUS power and charge pump I/O */
    usb_vbus_config();

    uint8_t i = 0U;
    pipe_index = 0U;

    usb_para_init(&gd_usb_core, USBHS1, USB_SPEED_FULL, HOST_MODE);

    gd_usb_core.host.connect_status = 0U;

    for (i = 0U; i < USBHS_MAX_TX_FIFOS; i++)
    {
        gd_usb_core.host.pipe[i].err_count = 0U;
        gd_usb_core.host.pipe[i].pp_status = PIPE_IDLE;
        gd_usb_core.host.backup_xfercount[i] = 0U;
    }

    gd_usb_core.host.pipe[0].ep.mps = 8U;

    usb_basic_init(&gd_usb_core.bp, &gd_usb_core.regs);

    usb_globalint_disable(&gd_usb_core.regs);

    usb_core_init(gd_usb_core.bp, &gd_usb_core.regs);

    usb_curmode_set(&gd_usb_core.regs, HOST_MODE);

    usb_host_init(&gd_usb_core);

    usb_globalint_enable(&gd_usb_core.regs);

    /* enable interrupts */
    usb_intr_config(USBHS1);

    return RT_EOK;
}

int gd_usbh_register(void)
{
    rt_err_t res = -RT_ERROR;

    uhcd_t uhcd = (uhcd_t)rt_malloc(sizeof(struct uhcd));
    if (uhcd == RT_NULL)
    {
        rt_kprintf("uhcd malloc failed\r\n");
        return -RT_ERROR;
    }

    rt_memset((void *)uhcd, 0, sizeof(struct uhcd));
    uhcd->parent.type = RT_Device_Class_USBHost;
    uhcd->parent.init = gd32_hcd_init;
    uhcd->parent.user_data = &gd_usb_core;

    uhcd->ops = &_uhcd_ops;
    uhcd->num_ports = OTG_FS_PORT;
    gd_usb_core.host.data = uhcd;

    res = rt_device_register(&uhcd->parent, "usbh", RT_DEVICE_FLAG_DEACTIVATE);
    if (res != RT_EOK)
    {
        rt_kprintf("register usb host failed res = %d\r\n", res);
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(gd_usbh_register);

static int gd_usbh_start(void)
{
    return rt_usb_host_init("usbh");
}
INIT_APP_EXPORT(gd_usbh_start);

#ifdef RT_USING_FINSH
static void usbhstat(void)
{
    rt_kprintf("usbh irq=%u connected=%u core_connected=%u\n",
               gd_usbh_irq_count, connect_status,
               gd_usb_core.host.connect_status);
    rt_kprintf("core GAHBCS=%08x GUSBCS=%08x GINTF=%08x GINTEN=%08x\n",
               gd_usb_core.regs.gr->GAHBCS, gd_usb_core.regs.gr->GUSBCS,
               gd_usb_core.regs.gr->GINTF, gd_usb_core.regs.gr->GINTEN);
    rt_kprintf("host HCTL=%08x HFINFR=%08x HACHINT=%08x HPCS=%08x\n",
               gd_usb_core.regs.hr->HCTL, gd_usb_core.regs.hr->HFINFR,
               gd_usb_core.regs.hr->HACHINT, *gd_usb_core.regs.HPCS);
    rt_kprintf("nvic enable=%u pending=%u active=%u\n",
               NVIC_GetEnableIRQ(USBHS1_IRQn), NVIC_GetPendingIRQ(USBHS1_IRQn),
               NVIC_GetActive(USBHS1_IRQn));
}
MSH_CMD_EXPORT(usbhstat, show USB host status);
#endif

#endif /* BSP_USING_USB && RT_USING_USB_HOST */
