/*
 * Copyright (c) 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "usbd_core.h"
#include "usbd_display.h"

struct usbd_display_priv {
    struct usb_mempool pool;
    struct usbd_endpoint out_ep;
    struct usbd_endpoint in_ep;
    struct usbd_display_frame *current_frame;
} g_usbd_display;

int usbd_display_frame_create(struct usbd_display_frame *frame, uint32_t count)
{
    return usb_mempool_create(&g_usbd_display.pool, frame, sizeof(struct usbd_display_frame), count);
}

struct usbd_display_frame *usbd_display_frame_alloc(void)
{
    return (struct usbd_display_frame *)usb_mempool_alloc(&g_usbd_display.pool);
}

int usbd_display_frame_free(struct usbd_display_frame *frame)
{
    return usb_mempool_free(&g_usbd_display.pool, (uintptr_t *)frame);
}

int usbd_display_frame_send(struct usbd_display_frame *frame)
{
    return usb_mempool_send(&g_usbd_display.pool, (uintptr_t *)frame);
}

int usbd_display_frame_recv(struct usbd_display_frame **frame, uint32_t timeout)
{
    return usb_mempool_recv(&g_usbd_display.pool, (uintptr_t **)frame, timeout);
}

uint8_t usb_dispay_dummy[512];
volatile uint32_t usb_display_buf_offset;
volatile bool usb_display_ignore_frame;

static void display_notify_handler(uint8_t busid, uint8_t event, void *arg)
{
    switch (event) {
        case USBD_EVENT_RESET:
            break;
        case USBD_EVENT_CONFIGURED:
            usb_display_buf_offset = 0;
            usb_display_ignore_frame = true;
            g_usbd_display.current_frame = NULL;
            usb_mempool_reset(&g_usbd_display.pool);
            usbd_ep_start_read(busid, g_usbd_display.out_ep.ep_addr, usb_dispay_dummy, usbd_get_ep_mps(0, g_usbd_display.out_ep.ep_addr));
            break;
        default:
            break;
    }
}

void usbd_display_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    if (usb_display_ignore_frame) {
        // alloc frame for next at the end of current frame
        if ((nbytes % usbd_get_ep_mps(0, g_usbd_display.out_ep.ep_addr)) || (nbytes == 0)) {
            if (g_usbd_display.current_frame == NULL) {
                g_usbd_display.current_frame = usbd_display_frame_alloc();
                if (g_usbd_display.current_frame) {
                    usb_display_ignore_frame = false;
                    usb_display_buf_offset = 0;

                    goto get_frame;
                } else {
                    goto drop_frame;
                }
            } else {
                usb_display_ignore_frame = false;
                usb_display_buf_offset = 0;

                goto get_frame;
            }
        } else {
            goto drop_frame;
        }
    } else {
        struct usbd_disp_frame_header *header = (struct usbd_disp_frame_header *)&g_usbd_display.current_frame->frame_buf[0];
        struct usbd_display_frame *frame;

        if (header->payload_total > g_usbd_display.current_frame->frame_bufsize) {
            USB_LOG_ERR("frame overflow, drop it\r\n");
            usb_display_ignore_frame = true;

            goto drop_frame;
        }

        usb_display_buf_offset += nbytes;

        if ((nbytes % usbd_get_ep_mps(0, g_usbd_display.out_ep.ep_addr)) || (nbytes == 0)) {
            frame = g_usbd_display.current_frame;
            g_usbd_display.current_frame = NULL;

            frame->frame_format = header->type;
            frame->frame_size = header->payload_total;
            usbd_display_frame_send(frame);

            g_usbd_display.current_frame = usbd_display_frame_alloc();
            if (g_usbd_display.current_frame) {
                usb_display_ignore_frame = false;
                usb_display_buf_offset = 0;

                goto get_frame;
            } else {
                usb_display_ignore_frame = true;

                goto drop_frame;
            }
        } else {
            goto get_frame;
        }
    }
    return;

drop_frame:
    // drop current frame
    usbd_ep_start_read(busid, g_usbd_display.out_ep.ep_addr, usb_dispay_dummy, usbd_get_ep_mps(0, g_usbd_display.out_ep.ep_addr));
    return;
get_frame:
    usbd_ep_start_read(busid, g_usbd_display.out_ep.ep_addr, &g_usbd_display.current_frame->frame_buf[usb_display_buf_offset], 16384);
    return;
}

void usbd_display_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
}

struct usbd_interface *usbd_display_init_intf(struct usbd_interface *intf,
                                              const uint8_t out_ep,
                                              const uint8_t in_ep,
                                              struct usbd_display_frame *frame,
                                              uint32_t count)
{
    intf->class_interface_handler = NULL;
    intf->class_endpoint_handler = NULL;
    intf->vendor_handler = NULL;
    intf->notify_handler = display_notify_handler;

    g_usbd_display.out_ep.ep_addr = out_ep;
    g_usbd_display.out_ep.ep_cb = usbd_display_bulk_out;
    g_usbd_display.in_ep.ep_addr = in_ep;
    g_usbd_display.in_ep.ep_cb = usbd_display_bulk_in;
    usbd_add_endpoint(0, &g_usbd_display.out_ep);
    usbd_add_endpoint(0, &g_usbd_display.in_ep);

    for (uint32_t i = 0; i < count; i++) {
        USB_ASSERT_MSG(frame[i].frame_bufsize % 16384, "frame_bufsize must be the multiple of 16384");
    }

    usbd_display_frame_create(frame, count);
    return intf;
}

int usbd_display_dequeue(struct usbd_display_frame **frame, uint32_t timeout)
{
    return usbd_display_frame_recv(frame, timeout);
}

int usbd_display_enqueue(struct usbd_display_frame *frame)
{
    return usbd_display_frame_free(frame);
}