/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-03     Yi Qiu      first version
 */

#include <rtthread.h>
#include <drivers/usb_host.h>
#include "hid.h"

#if defined(RT_USBH_HID) && defined(RT_USBH_HID_KEYBOARD)

static struct uprotocal kbd_protocal;

static rt_err_t rt_usbh_hid_kbd_callback(void* arg)
{
    int int1, int2;
    struct uhid* hid;

    hid = (struct uhid*)arg;

    int1 = *(rt_uint32_t*)hid->buffer;
    int2 = *(rt_uint32_t*)(&hid->buffer[4]);

    if(int1 != 0 || int2 != 0)
    {
        RT_DEBUG_LOG(RT_DEBUG_USB, ("key down 0x%x, 0x%x\n", int1, int2));
    }

    return RT_EOK;
}

static rt_thread_t kbd_thread;
static void kbd_task(void* param)
{
    struct uhintf* intf = (struct uhintf*)param;
    while (1)
    {
        if (rt_usb_hcd_pipe_xfer(intf->device->hcd, ((struct uhid*)intf->user_data)->pipe_in,
            ((struct uhid*)intf->user_data)->buffer, ((struct uhid*)intf->user_data)->pipe_in->ep.wMaxPacketSize,
            USB_TIMEOUT_BASIC) == 0)
        {
            break;
        }

        rt_usbh_hid_kbd_callback(intf->user_data);
    }
}


static rt_err_t rt_usbh_hid_kbd_init(void* arg)
{
    struct uhintf* intf = (struct uhintf*)arg;

    RT_ASSERT(intf != RT_NULL);

    rt_usbh_hid_set_protocal(intf, 0);

    rt_usbh_hid_set_idle(intf, 10, 0);

    RT_DEBUG_LOG(RT_DEBUG_USB, ("start usb keyboard\n"));

    kbd_thread = rt_thread_create("kbd0", kbd_task, intf, 1024, 8, 100);
    rt_thread_startup(kbd_thread);

    return RT_EOK;
}

/**
 * This function will define the hid keyboard protocal, it will be register to the protocal list.
 *
 * @return the keyboard protocal structure.
 */
uprotocal_t rt_usbh_hid_protocal_kbd(void)
{
    kbd_protocal.pro_id = USB_HID_KEYBOARD;

    kbd_protocal.init = rt_usbh_hid_kbd_init;
    kbd_protocal.callback = rt_usbh_hid_kbd_callback;

    return &kbd_protocal;
}

#endif

