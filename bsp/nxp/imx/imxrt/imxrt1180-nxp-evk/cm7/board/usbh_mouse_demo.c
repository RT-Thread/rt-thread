/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026/06/10     Tim          first version
 */
#include <rtthread.h>

#if defined(BSP_CHERRYUSB_HOST_MOUSE_DEMO) && defined(RT_CHERRYUSB_HOST) && defined(RT_CHERRYUSB_HOST_HID)

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "usb_config.h"
#include "usb_errno.h"
#include "usb_osal.h"
#include "usbh_core.h"
#include "usbh_hid.h"
#include "usb_hid.h"

#define RT1180_USBH_MOUSE_REPORT_LEN 64U
#define RT1180_USBH_MOUSE_THREAD_STACK 2048U

struct rt1180_usbh_mouse_state
{
    bool active;
    uint8_t buttons;
};

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t rt1180_mouse_report[CONFIG_USBHOST_MAX_HID_CLASS][RT1180_USBH_MOUSE_REPORT_LEN];
static struct rt1180_usbh_mouse_state rt1180_mouse_state[CONFIG_USBHOST_MAX_HID_CLASS];

static uint8_t rt1180_hid_minor(struct usbh_hid *hid_class)
{
    if (hid_class == RT_NULL)
    {
        return CONFIG_USBHOST_MAX_HID_CLASS;
    }

    return hid_class->minor;
}

static uint32_t rt1180_mouse_xfer_len(struct usbh_hid *hid_class)
{
    uint32_t len;

    if ((hid_class == RT_NULL) || (hid_class->intin == RT_NULL))
    {
        return 0;
    }

    len = hid_class->intin->wMaxPacketSize;
    if (len > RT1180_USBH_MOUSE_REPORT_LEN)
    {
        len = RT1180_USBH_MOUSE_REPORT_LEN;
    }

    return len;
}

static void rt1180_mouse_button_event(const char *name, bool pressed)
{
    rt_kprintf("USB mouse: %s button %s\r\n", name, pressed ? "down" : "up");
}

static void rt1180_mouse_report_button(uint8_t changed, uint8_t buttons, uint8_t mask, const char *name)
{
    if (changed & mask)
    {
        rt1180_mouse_button_event(name, (buttons & mask) != 0U);
    }
}

static void rt1180_mouse_parse_report(struct usbh_hid *hid_class, const uint8_t *report, int nbytes)
{
    struct rt1180_usbh_mouse_state *state;
    uint8_t minor;
    uint8_t buttons;
    uint8_t changed;
    int8_t x;
    int8_t y;
    int8_t wheel = 0;

    if ((report == RT_NULL) || (nbytes < 3))
    {
        return;
    }

    minor = rt1180_hid_minor(hid_class);
    if (minor >= CONFIG_USBHOST_MAX_HID_CLASS)
    {
        return;
    }

    state = &rt1180_mouse_state[minor];

    buttons = report[0];
    x = (int8_t)report[1];
    y = (int8_t)report[2];
    if (nbytes >= 4)
    {
        wheel = (int8_t)report[3];
    }

    changed = buttons ^ state->buttons;
    rt1180_mouse_report_button(changed, buttons, HID_MOUSE_INPUT_BUTTON_LEFT, "left");
    rt1180_mouse_report_button(changed, buttons, HID_MOUSE_INPUT_BUTTON_RIGHT, "right");
    rt1180_mouse_report_button(changed, buttons, HID_MOUSE_INPUT_BUTTON_MIDDLE, "middle");

    if (x < 0)
    {
        rt_kprintf("USB mouse: move left dx=%d\r\n", x);
    }
    else if (x > 0)
    {
        rt_kprintf("USB mouse: move right dx=%d\r\n", x);
    }

    if (y < 0)
    {
        rt_kprintf("USB mouse: move up dy=%d\r\n", y);
    }
    else if (y > 0)
    {
        rt_kprintf("USB mouse: move down dy=%d\r\n", y);
    }

    if (wheel < 0)
    {
        rt_kprintf("USB mouse: wheel down delta=%d\r\n", wheel);
    }
    else if (wheel > 0)
    {
        rt_kprintf("USB mouse: wheel up delta=%d\r\n", wheel);
    }

    state->buttons = buttons;
}

static void rt1180_mouse_submit(struct usbh_hid *hid_class);

static void rt1180_mouse_callback(void *arg, int nbytes)
{
    struct usbh_hid *hid_class = (struct usbh_hid *)arg;
    uint8_t minor = rt1180_hid_minor(hid_class);

    if (minor >= CONFIG_USBHOST_MAX_HID_CLASS)
    {
        return;
    }

    if (!rt1180_mouse_state[minor].active)
    {
        return;
    }

    if (nbytes > 0)
    {
        rt1180_mouse_parse_report(hid_class, rt1180_mouse_report[minor], nbytes);
        rt1180_mouse_submit(hid_class);
    }
    else if (nbytes == -USB_ERR_NAK)
    {
        rt1180_mouse_submit(hid_class);
    }
    else
    {
        rt_kprintf("USB mouse: interrupt transfer stopped, ret=%d\r\n", nbytes);
        rt1180_mouse_state[minor].active = false;
    }
}

static void rt1180_mouse_submit(struct usbh_hid *hid_class)
{
    uint8_t minor = rt1180_hid_minor(hid_class);
    uint32_t len;
    int ret;

    if (minor >= CONFIG_USBHOST_MAX_HID_CLASS)
    {
        return;
    }

    if (!rt1180_mouse_state[minor].active)
    {
        return;
    }

    len = rt1180_mouse_xfer_len(hid_class);
    if (len == 0U)
    {
        rt_kprintf("USB mouse: invalid interrupt IN endpoint\r\n");
        rt1180_mouse_state[minor].active = false;
        return;
    }

    usbh_int_urb_fill(&hid_class->intin_urb,
                      hid_class->hport,
                      hid_class->intin,
                      rt1180_mouse_report[minor],
                      len,
                      0,
                      rt1180_mouse_callback,
                      hid_class);

    ret = usbh_submit_urb(&hid_class->intin_urb);
    if (ret < 0)
    {
        rt_kprintf("USB mouse: submit interrupt IN failed, ret=%d\r\n", ret);
        rt1180_mouse_state[minor].active = false;
    }
}

static void rt1180_usbh_mouse_thread(CONFIG_USB_OSAL_THREAD_SET_ARGV)
{
    struct usbh_hid *hid_class = (struct usbh_hid *)CONFIG_USB_OSAL_THREAD_GET_ARGV;
    uint8_t minor = rt1180_hid_minor(hid_class);

    if (minor >= CONFIG_USBHOST_MAX_HID_CLASS)
    {
        goto exit;
    }

    if ((hid_class->intin == RT_NULL) || (hid_class->protocol != HID_PROTOCOL_MOUSE))
    {
        rt_kprintf("USB HID: ignore non-mouse device, minor=%u, protocol=%u\r\n",
                   (unsigned int)minor,
                   (unsigned int)((hid_class != RT_NULL) ? hid_class->protocol : 0U));
        goto exit;
    }

    memset(&rt1180_mouse_state[minor], 0, sizeof(rt1180_mouse_state[minor]));
    memset(rt1180_mouse_report[minor], 0, sizeof(rt1180_mouse_report[minor]));
    rt1180_mouse_state[minor].active = true;

    (void)usbh_hid_set_idle(hid_class, 0, 0);
    (void)usbh_hid_set_protocol(hid_class, HID_PROTOCOL_BOOT);

    rt_kprintf("USB mouse: connected, dev=/dev/input%u\r\n", (unsigned int)minor);
    rt1180_mouse_submit(hid_class);

exit:
    usb_osal_thread_delete(RT_NULL);
}

void usbh_hid_run(struct usbh_hid *hid_class)
{
    usb_osal_thread_create("usbh_mouse",
                           RT1180_USBH_MOUSE_THREAD_STACK,
                           CONFIG_USBHOST_PSC_PRIO + 1,
                           rt1180_usbh_mouse_thread,
                           hid_class);
}

void usbh_hid_stop(struct usbh_hid *hid_class)
{
    uint8_t minor = rt1180_hid_minor(hid_class);

    if (minor >= CONFIG_USBHOST_MAX_HID_CLASS)
    {
        return;
    }

    if (rt1180_mouse_state[minor].active)
    {
        rt_kprintf("USB mouse: disconnected, dev=/dev/input%u\r\n", (unsigned int)minor);
    }

    rt1180_mouse_state[minor].active = false;
    rt1180_mouse_state[minor].buttons = 0;
}

#endif
