/*
 * Copyright (c) 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_gamepad.h"

#define GAMEPAD_IN_EP  0x81
#define GAMEPAD_OUT_EP 0x02

#define USBD_MAX_POWER 500

static const uint8_t xinput_device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, XINPUT_VID, XINPUT_PID, XINPUT_BCD_DEVICE, 0x01)
};

static const uint8_t switch_device_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, SWITCH_VID, SWITCH_PID, SWITCH_BCD_DEVICE, 0x01)
};

static const uint8_t xinput_config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT((9 + XINPUT_DESCRIPTOR_LEN), 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    XINPUT_DESCRIPTOR_INIT(0x00, GAMEPAD_OUT_EP, GAMEPAD_IN_EP)
};

static const uint8_t switch_config_descriptor[] = {
    USB_CONFIG_DESCRIPTOR_INIT((9 + SWITCH_DESCRIPTOR_LEN), 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    SWITCH_DESCRIPTOR_INIT(0x00, GAMEPAD_OUT_EP, GAMEPAD_IN_EP)
};

static const char *xinput_string_descriptors[] = {
    (const char[]){ 0x09, 0x04 }, /* Langid */
    "Microsoft",                  /* Manufacturer */
    "XInput STANDARD GAMEPAD",    /* Product */
    "1.0",                        /* Serial Number */
};

static const char *switch_string_descriptors[] = {
    (const char[]){ 0x09, 0x04 }, /* Langid */
    "HORI",                       /* Manufacturer */
    "Switch Pro Controller",      /* Product */
    "1.0",                        /* Serial Number */
};

uint8_t gamepad_mode = USBD_GAMEPAD_MODE_XINPUT;
bool gamepad_init_flag = false;

static const uint8_t *device_descriptor_callback(uint8_t speed)
{
    switch (gamepad_mode) {
        case USBD_GAMEPAD_MODE_XINPUT:
            return xinput_device_descriptor;
        case USBD_GAMEPAD_MODE_SWITCH:
            return switch_device_descriptor;
        case USBD_GAMEPAD_MODE_XBOXONE:
            break;
        case USBD_GAMEPAD_MODE_PS4:
            break;

        default:
            break;
    }
    return NULL;
}

static const uint8_t *config_descriptor_callback(uint8_t speed)
{
    switch (gamepad_mode) {
        case USBD_GAMEPAD_MODE_XINPUT:
            return xinput_config_descriptor;
        case USBD_GAMEPAD_MODE_SWITCH:
            return switch_config_descriptor;
        case USBD_GAMEPAD_MODE_XBOXONE:
            break;
        case USBD_GAMEPAD_MODE_PS4:
            break;

        default:
            break;
    }
    return NULL;
}

static const uint8_t *device_quality_descriptor_callback(uint8_t speed)
{
    return NULL;
}

static const char *string_descriptor_callback(uint8_t speed, uint8_t index)
{
    if (index > 3) {
        return NULL;
    }

    switch (gamepad_mode) {
        case USBD_GAMEPAD_MODE_XINPUT:
            return xinput_string_descriptors[index];
        case USBD_GAMEPAD_MODE_SWITCH:
            return switch_string_descriptors[index];
        case USBD_GAMEPAD_MODE_XBOXONE:
            break;
        case USBD_GAMEPAD_MODE_PS4:
            break;

        default:
            break;
    }
    return NULL;
}

const struct usb_descriptor gamepad_descriptor = {
    .device_descriptor_callback = device_descriptor_callback,
    .config_descriptor_callback = config_descriptor_callback,
    .device_quality_descriptor_callback = device_quality_descriptor_callback,
    .string_descriptor_callback = string_descriptor_callback
};

USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t gamepad_read_buffer[64];
struct usb_gamepad_report gamepad_report;

#define GAMEPAD_STATE_IDLE 0
#define GAMEPAD_STATE_BUSY 1

volatile uint8_t gamepad_state = GAMEPAD_STATE_IDLE;

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
            usbd_ep_start_read(busid, GAMEPAD_OUT_EP, gamepad_read_buffer, usbd_get_ep_mps(busid, GAMEPAD_OUT_EP));
            break;
        case USBD_EVENT_SET_REMOTE_WAKEUP:
            break;
        case USBD_EVENT_CLR_REMOTE_WAKEUP:
            break;

        default:
            break;
    }
}

static void usbd_gamepad_int_in_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    gamepad_state = GAMEPAD_STATE_IDLE;
}

void usbd_gamepad_int_out_callback(uint8_t busid, uint8_t ep, uint32_t nbytes)
{
    usbd_ep_start_read(busid, GAMEPAD_OUT_EP, gamepad_read_buffer, usbd_get_ep_mps(busid, GAMEPAD_OUT_EP));
}

/*!< endpoint call back */
static struct usbd_endpoint gamepad_in_ep = {
    .ep_cb = usbd_gamepad_int_in_callback,
    .ep_addr = GAMEPAD_IN_EP
};

static struct usbd_endpoint gamepad_out_ep = {
    .ep_cb = usbd_gamepad_int_out_callback,
    .ep_addr = GAMEPAD_OUT_EP
};

static struct usbd_interface intf0;

void gamepad_init(uint8_t busid, uintptr_t reg_base)
{
    if (gamepad_init_flag) {
        return;
    }

    gamepad_init_flag = true;

    usbd_desc_register(busid, &gamepad_descriptor);

    switch (gamepad_mode) {
        case USBD_GAMEPAD_MODE_XINPUT:
            usbd_add_interface(busid, usbd_gamepad_xinput_init_intf(&intf0));
            break;
        case USBD_GAMEPAD_MODE_SWITCH:
            usbd_add_interface(busid, usbd_gamepad_switch_init_intf(&intf0));
            break;
        case USBD_GAMEPAD_MODE_XBOXONE:
            break;
        case USBD_GAMEPAD_MODE_PS4:
            break;

        default:
            break;
    }

    usbd_add_endpoint(busid, &gamepad_in_ep);
    usbd_add_endpoint(busid, &gamepad_out_ep);
    usbd_initialize(busid, reg_base, usbd_event_handler);
}

void gamepad_change_mode(uint8_t mode, uintptr_t reg_base)
{
    gamepad_mode = mode;

    if (gamepad_init_flag) {
        usbd_deinitialize(0);
    }
    gamepad_init_flag = false;
    gamepad_init(0, reg_base);
}

void gamepad_test(uint8_t busid)
{
    static uint32_t test_counter = 0;

    if (usb_device_is_configured(busid) == false) {
        return;
    }

    gamepad_state = GAMEPAD_STATE_BUSY;
    memset(&gamepad_report, 0, sizeof(gamepad_report));

    gamepad_report.buttons = (1 << (test_counter % 18));

    switch (gamepad_mode) {
        case USBD_GAMEPAD_MODE_XINPUT:
            usbd_gamepad_xinput_send_report(GAMEPAD_IN_EP, &gamepad_report);
            break;
        case USBD_GAMEPAD_MODE_SWITCH:
            usbd_gamepad_switch_send_report(GAMEPAD_IN_EP, &gamepad_report);
            break;
        case USBD_GAMEPAD_MODE_XBOXONE:
            break;
        case USBD_GAMEPAD_MODE_PS4:
            break;

        default:
            break;
    }

    test_counter++;
    while (gamepad_state == GAMEPAD_STATE_BUSY) {
    }
}