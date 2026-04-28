/*
 * Copyright (c) 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_display.h"

#define DISPLAY_IN_EP  0x81
#define DISPLAY_OUT_EP 0x02

#define USBD_VID           0x303A
#define USBD_PID           0x2987
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#define USB_CONFIG_SIZE (9 + 9 + 7 + 7)

#ifdef CONFIG_USB_HS
#define DISPLAY_EP_MPS 512
#else
#define DISPLAY_EP_MPS 64
#endif

static const uint8_t device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0101, 0x01)
};

static const uint8_t config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    USB_INTERFACE_DESCRIPTOR_INIT(0x00, 0x00, 0x02, 0xff, 0x00, 0x00, 0x00),
    USB_ENDPOINT_DESCRIPTOR_INIT(DISPLAY_IN_EP, 0x02, DISPLAY_EP_MPS, 0x00),
    USB_ENDPOINT_DESCRIPTOR_INIT(DISPLAY_OUT_EP, 0x02, DISPLAY_EP_MPS, 0x00),
};

static const uint8_t device_quality_descriptor[] = {
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x00,
    0x00,
};

static const char *string_descriptors[] = {
    (const char[]){ 0x09, 0x04 },            /* Langid */
    "CherryUSB",                             /* Manufacturer */
    "cherryusb_R640x480_Ergb16_Fps30_Bl128", /* Product */
    // "cherryusb_R640x480_Ejpg9_Fps30_Bl128", /* Product */
    "2022123456",                            /* Serial Number */
};

static const uint8_t *device_descriptor_callback(uint8_t speed)
{
    return device_descriptor;
}

static const uint8_t *config_descriptor_callback(uint8_t speed)
{
    return config_descriptor;
}

static const uint8_t *device_quality_descriptor_callback(uint8_t speed)
{
    return device_quality_descriptor;
}

static const char *string_descriptor_callback(uint8_t speed, uint8_t index)
{
    if (index >= (sizeof(string_descriptors) / sizeof(char *))) {
        return NULL;
    }
    return string_descriptors[index];
}

const struct usb_descriptor usbdisplay_descriptor = {
    .device_descriptor_callback = device_descriptor_callback,
    .config_descriptor_callback = config_descriptor_callback,
    .device_quality_descriptor_callback = device_quality_descriptor_callback,
    .string_descriptor_callback = string_descriptor_callback
};

static void usbd_event_handler(uint8_t busid, uint8_t event)
{
    switch (event) {
        case USBD_EVENT_RESET:
            break;
        case USBD_EVENT_CONNECTED:
            break;
        case USBD_EVENT_DISCONNECTED:
            break;
        case USBD_EVENT_RESUME:
            break;
        case USBD_EVENT_SUSPEND:
            break;
        case USBD_EVENT_CONFIGURED:
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

struct usbd_interface intf0;

struct usbd_display_frame frame_pool[2];

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t usb_display_buffer[2][640 * 480 * 2];

void usbdisplay_init(uint8_t busid, uintptr_t reg_base)
{
    frame_pool[0].frame_buf = usb_display_buffer[0];
    frame_pool[0].frame_bufsize = 640 * 480 * 2;
    frame_pool[1].frame_buf = usb_display_buffer[1];
    frame_pool[1].frame_bufsize = 640 * 480 * 2;

    usbd_desc_register(busid, &usbdisplay_descriptor);

    usbd_add_interface(busid, usbd_display_init_intf(&intf0, DISPLAY_OUT_EP, DISPLAY_IN_EP, frame_pool, 2));
    usbd_initialize(busid, reg_base, usbd_event_handler);
}

void usbdisplay_poll(void)
{
    struct usbd_display_frame *frame;
    int ret;

    ret = usbd_display_dequeue(&frame, 0xffffffff); // timeout is not useful for baremental
    if (ret < 0) {
        return;
    }
    USB_LOG_INFO("frame type: %u, frame size %u\r\n", frame->frame_format, frame->frame_size);
    usbd_display_enqueue(frame);
}