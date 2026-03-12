/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usb_midi.h"

#define MIDI_OUT_EP 0x02
#define MIDI_IN_EP  0x81

#define USBD_VID           0x0d28
#define USBD_PID           0x0404
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#define AUDIO_AC_SIZ AUDIO_SIZEOF_AC_HEADER_DESC(1)
#define AUDIO_MS_SIZ (7 + MIDI_SIZEOF_JACK_DESC + 9 + 5 + 9 + 5)

#define USB_CONFIG_SIZE (unsigned long)(9 +                            \
                                        AUDIO_AC_DESCRIPTOR_LEN(1) +   \
                                        MIDI_STANDARD_DESCRIPTOR_LEN + \
                                        AUDIO_MS_SIZ)

#ifdef CONFIG_USB_HS
#define MIDI_EP_MPS 512
#else
#define MIDI_EP_MPS 64
#endif

static const uint8_t device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0100, 0x01)
};

static const uint8_t config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    AUDIO_AC_DESCRIPTOR_INIT(0x00, 0x02, AUDIO_AC_SIZ, 0x00, 0x01),
    MIDI_STANDARD_DESCRIPTOR_INIT(0x01, 0x02),
    MIDI_CS_HEADER_DESCRIPTOR_INIT(AUDIO_MS_SIZ),
    MIDI_JACK_DESCRIPTOR_INIT(0x01),
    // OUT endpoint descriptor
    0x09, 0x05, MIDI_OUT_EP, 0x02, WBVAL(MIDI_EP_MPS), 0x00, 0x00, 0x00,
    0x05, 0x25, 0x01, 0x01, 0x01,

    // IN endpoint descriptor
    0x09, 0x05, MIDI_IN_EP, 0x02, WBVAL(MIDI_EP_MPS), 0x00, 0x00, 0x00,
    0x05, 0x25, 0x01, 0x01, 0x03
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
    (const char[]){ 0x09, 0x04 }, /* Langid */
    "CherryUSB",                  /* Manufacturer */
    "CherryUSB MIDI DEMO",        /* Product */
    "2022123456",                 /* Serial Number */
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
    if (index > 3) {
        return NULL;
    }
    return string_descriptors[index];
}

const struct usb_descriptor midi_descriptor = {
    .device_descriptor_callback = device_descriptor_callback,
    .config_descriptor_callback = config_descriptor_callback,
    .device_quality_descriptor_callback = device_quality_descriptor_callback,
    .string_descriptor_callback = string_descriptor_callback
};

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_buffer[MIDI_EP_MPS];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t write_buffer[MIDI_EP_MPS];

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
            usbd_ep_start_read(busid, MIDI_OUT_EP, read_buffer, MIDI_EP_MPS);
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

void usbd_midi_bulk_out(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    usbd_ep_start_read(busid, MIDI_OUT_EP, read_buffer, MIDI_EP_MPS);
}

void usbd_midi_bulk_in(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
}

struct usbd_interface intf0;
struct usbd_interface intf1;

struct usbd_endpoint midi_out_ep = {
    .ep_addr = MIDI_OUT_EP,
    .ep_cb = usbd_midi_bulk_out
};

struct usbd_endpoint midi_in_ep = {
    .ep_addr = MIDI_IN_EP,
    .ep_cb = usbd_midi_bulk_in
};

void midi_init(uint8_t busid, uintptr_t reg_base)
{
    usbd_desc_register(busid, &midi_descriptor);

    usbd_add_interface(busid, &intf0);
    usbd_add_interface(busid, &intf1);
    usbd_add_endpoint(busid, &midi_out_ep);
    usbd_add_endpoint(busid, &midi_in_ep);

    usbd_initialize(busid, reg_base, usbd_event_handler);
}