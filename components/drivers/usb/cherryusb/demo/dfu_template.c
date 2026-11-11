/*
 * Copyright (c) 2022 ~ 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_dfu.h"

#define USBD_VID           0x0483
#define USBD_PID           0xdf11
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#define USB_CONFIG_SIZE (9 + DFU_DESCRIPTOR_LEN)

#define FLASH_DESC_STR      "@Internal Flash   /0x08000000/16*128Kg"

static const uint8_t device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0200, 0x01)
};

static const uint8_t config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    DFU_DESCRIPTOR_INIT(4)
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
    "CherryUSB DFU DEMO",         /* Product */
    "2022123456",                 /* Serial Number */
    FLASH_DESC_STR
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

const struct usb_descriptor dfu_descriptor = {
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

void dfu_init(uint8_t busid, uintptr_t reg_base)
{
    usbd_desc_register(busid, &dfu_descriptor);

    usbd_add_interface(busid, usbd_dfu_init_intf(&intf0));
    usbd_initialize(busid, reg_base, usbd_event_handler);
}

volatile uint32_t flash_start_address;

void usbd_dfu_begin_load(void)
{
    flash_start_address = 0x08000000;
}

void usbd_dfu_end_load(void)
{
}

void usbd_dfu_reset(void)
{
    //NVIC_SystemReset();
}

int usbd_dfu_write(uint16_t value, const uint8_t *data, uint16_t length)
{
    //usb_hexdump(data, length);

    // patch for stm32 special command
#if 1
    if (value == 0) {
        if (data[0] == DFU_SPECIAL_CMD_SET_ADDRESS_POINTER) {
            memcpy((uint8_t *)&flash_start_address, data, 4);
        } else if (data[0] == DFU_SPECIAL_CMD_ERASE) {
            memcpy((uint8_t *)&flash_start_address, data, 4);
        }
    } else if (value > 1) {
        uint32_t addr = (value - 2) * CONFIG_USBDEV_REQUEST_BUFFER_LEN + flash_start_address;
    }
#else
    flash_start_address += length;
#endif
    return 0;
}

int usbd_dfu_read(uint16_t value, const uint8_t *data, uint16_t length, uint16_t *actual_length)
{
    return 0;
}