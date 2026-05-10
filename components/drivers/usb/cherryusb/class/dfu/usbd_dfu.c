/*
 * Copyright (c) 2022 ~ 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "usbd_core.h"
#include "usbd_dfu.h"

struct usbd_dfu_priv {
    uint8_t dfu_state;
} g_usbd_dfu;

const char *usbd_dfu_state_string[] = {
    "APP_IDLE",
    "APP_DETACH",
    "DFU_IDLE",
    "DFU_DNLOAD_SYNC",
    "DFU_DNLOAD_BUSY",
    "DFU_DNLOAD_IDLE",
    "DFU_MANIFEST_SYNC",
    "DFU_MANIFEST",
    "DFU_MANIFEST_WAIT_RESET",
    "DFU_UPLOAD_IDLE",
    "DFU_ERROR"
};

static int dfu_class_interface_request_handler(uint8_t busid, struct usb_setup_packet *setup, uint8_t **data, uint32_t *len)
{
    USB_LOG_DBG("DFU Class request: "
                "bRequest 0x%02x\r\n",
                setup->bRequest);

    USB_LOG_DBG("dfu state:%s\r\n", usbd_dfu_state_string[g_usbd_dfu.dfu_state]);

    switch (g_usbd_dfu.dfu_state) {
        case DFU_STATE_APP_IDLE:
            switch (setup->bRequest) {
                case DFU_REQUEST_DETACH:
                    break;
                case DFU_REQUEST_GETSTATUS:
                    (*data)[0] = DFU_STATUS_OK; /* bStatus */
                    (*data)[1] = 0;
                    (*data)[2] = 0;
                    (*data)[3] = 0;
                    (*data)[4] = g_usbd_dfu.dfu_state;
                    (*data)[5] = 0; /* iString */
                    *len = 6;
                    break;
                case DFU_REQUEST_GETSTATE:
                    (*data)[0] = g_usbd_dfu.dfu_state;
                    *len = 1;
                    break;

                default:
                    return -1;
            }
            break;
        case DFU_STATE_APP_DETACH:
            switch (setup->bRequest) {
                case DFU_REQUEST_GETSTATUS:
                    (*data)[0] = DFU_STATUS_OK; /* bStatus */
                    (*data)[1] = 0;
                    (*data)[2] = 0;
                    (*data)[3] = 0;
                    (*data)[4] = g_usbd_dfu.dfu_state;
                    (*data)[5] = 0; /* iString */
                    *len = 6;
                    break;
                case DFU_REQUEST_GETSTATE:
                    (*data)[0] = g_usbd_dfu.dfu_state;
                    *len = 1;
                    break;

                default:
                    return -1;
            }
            break;
        case DFU_STATE_DFU_IDLE:
            switch (setup->bRequest) {
                case DFU_REQUEST_DNLOAD:
                    /* We received a DOWNLOAD command. Check the length field of the request. If it is 0,
                    we are done with the transfer.  */
                    if (setup->wLength == 0) {
                        usbd_dfu_end_load();
                        g_usbd_dfu.dfu_state = DFU_STATE_DFU_MANIFEST_SYNC;
                    } else {
                        usbd_dfu_begin_load();
                        if (usbd_dfu_write(setup->wValue, *data, setup->wLength) < 0) {
                            g_usbd_dfu.dfu_state = DFU_STATE_DFU_ERROR;
                            return -1;
                        } else {
                            g_usbd_dfu.dfu_state = DFU_STATE_DFU_DNLOAD_SYNC;
                        }
                    }
                    break;
                case DFU_REQUEST_UPLOAD:
                    usbd_dfu_begin_load();

                    uint16_t actual_length;
                    if (usbd_dfu_read(setup->wValue, *data, setup->wLength, &actual_length) < 0) {
                        g_usbd_dfu.dfu_state = DFU_STATE_DFU_ERROR;
                        return -1;
                    } else {
                        g_usbd_dfu.dfu_state = DFU_STATE_DFU_UPLOAD_IDLE;
                    }
                    *len = actual_length;
                    break;
                case DFU_REQUEST_ABORT:
                    g_usbd_dfu.dfu_state = DFU_STATE_DFU_IDLE;
                    break;
                case DFU_REQUEST_GETSTATUS:
                    (*data)[0] = DFU_STATUS_OK; /* bStatus */
                    (*data)[1] = 0;
                    (*data)[2] = 0;
                    (*data)[3] = 0;
                    (*data)[4] = g_usbd_dfu.dfu_state;
                    (*data)[5] = 0; /* iString */
                    *len = 6;
                    break;
                case DFU_REQUEST_GETSTATE:
                    (*data)[0] = g_usbd_dfu.dfu_state;
                    *len = 1;
                    break;

                default:
                    return -1;
            }
            break;
        case DFU_STATE_DFU_DNLOAD_SYNC:
            switch (setup->bRequest) {
                case DFU_REQUEST_GETSTATUS:
                    g_usbd_dfu.dfu_state = DFU_STATE_DFU_DNLOAD_BUSY;

                    (*data)[0] = DFU_STATUS_OK; /* bStatus */
                    (*data)[1] = 0;
                    (*data)[2] = 0;
                    (*data)[3] = 0;
                    (*data)[4] = g_usbd_dfu.dfu_state;
                    (*data)[5] = 0; /* iString */
                    *len = 6;
                    break;
                case DFU_REQUEST_GETSTATE:
                    (*data)[0] = g_usbd_dfu.dfu_state;
                    *len = 1;
                    break;

                default:
                    return -1;
            }
            break;
        case DFU_STATE_DFU_DNLOAD_BUSY:
            switch (setup->bRequest) {
                case DFU_REQUEST_GETSTATUS:
                    g_usbd_dfu.dfu_state = DFU_STATE_DFU_DNLOAD_IDLE;

                    (*data)[0] = DFU_STATUS_OK; /* bStatus */
                    (*data)[1] = 0;
                    (*data)[2] = 0;
                    (*data)[3] = 0;
                    (*data)[4] = g_usbd_dfu.dfu_state;
                    (*data)[5] = 0; /* iString */
                    *len = 6;
                    break;
                case DFU_REQUEST_GETSTATE:
                    (*data)[0] = g_usbd_dfu.dfu_state;
                    *len = 1;
                    break;

                default:
                    return -1;
            }
            break;
        case DFU_STATE_DFU_DNLOAD_IDLE:
            switch (setup->bRequest) {
                case DFU_REQUEST_DNLOAD:
                    /* We received a DOWNLOAD command. Check the length field of the request. If it is 0,
                    we are done with the transfer.  */
                    if (setup->wLength == 0) {
                        usbd_dfu_end_load();
                        g_usbd_dfu.dfu_state = DFU_STATE_DFU_MANIFEST_SYNC;
                    } else {
                        if (usbd_dfu_write(setup->wValue, *data, setup->wLength) < 0) {
                            g_usbd_dfu.dfu_state = DFU_STATE_DFU_ERROR;
                            return -1;
                        } else {
                            g_usbd_dfu.dfu_state = DFU_STATE_DFU_DNLOAD_SYNC;
                        }
                    }

                    break;
                case DFU_REQUEST_ABORT:
                    g_usbd_dfu.dfu_state = DFU_STATE_DFU_IDLE;
                    break;
                case DFU_REQUEST_GETSTATUS:
                    (*data)[0] = DFU_STATUS_OK; /* bStatus */
                    (*data)[1] = 0;
                    (*data)[2] = 0;
                    (*data)[3] = 0;
                    (*data)[4] = g_usbd_dfu.dfu_state;
                    (*data)[5] = 0; /* iString */
                    *len = 6;
                    break;
                case DFU_REQUEST_GETSTATE:
                    (*data)[0] = g_usbd_dfu.dfu_state;
                    *len = 1;
                    break;

                default:
                    return -1;
            }
            break;
        case DFU_STATE_DFU_UPLOAD_IDLE:
            switch (setup->bRequest) {
                case DFU_REQUEST_UPLOAD: {
                    uint16_t actual_length;
                    if (usbd_dfu_read(setup->wValue, *data, setup->wLength, &actual_length) < 0) {
                        g_usbd_dfu.dfu_state = DFU_STATE_DFU_ERROR;
                        return -1;
                    } else {
                        if (actual_length < setup->wLength) {
                            usbd_dfu_end_load();
                            g_usbd_dfu.dfu_state = DFU_STATE_DFU_IDLE;
                        } else {
                            g_usbd_dfu.dfu_state = DFU_STATE_DFU_UPLOAD_IDLE;
                        }
                    }
                } break;
                case DFU_REQUEST_ABORT:
                    g_usbd_dfu.dfu_state = DFU_STATE_DFU_IDLE;
                    break;
                case DFU_REQUEST_GETSTATUS:
                    (*data)[0] = DFU_STATUS_OK; /* bStatus */
                    (*data)[1] = 0;
                    (*data)[2] = 0;
                    (*data)[3] = 0;
                    (*data)[4] = g_usbd_dfu.dfu_state;
                    (*data)[5] = 0; /* iString */
                    *len = 6;
                    break;
                case DFU_REQUEST_GETSTATE:
                    (*data)[0] = g_usbd_dfu.dfu_state;
                    *len = 1;
                    break;

                default:
                    return -1;
            }
            break;
        case DFU_STATE_DFU_MANIFEST_SYNC:
            switch (setup->bRequest) {
                case DFU_REQUEST_GETSTATUS:
                    g_usbd_dfu.dfu_state = DFU_STATE_DFU_MANIFEST_WAIT_RESET;

                    (*data)[0] = DFU_STATUS_OK; /* bStatus */
                    (*data)[1] = 0;
                    (*data)[2] = 0;
                    (*data)[3] = 0;
                    (*data)[4] = g_usbd_dfu.dfu_state;
                    (*data)[5] = 0; /* iString */
                    *len = 6;

                    break;
                case DFU_REQUEST_GETSTATE:
                    (*data)[0] = g_usbd_dfu.dfu_state;
                    *len = 1;
                    break;

                default:
                    return -1;
            }
            break;
        case DFU_STATE_DFU_MANIFEST_WAIT_RESET:
            switch (setup->bRequest) {
                case DFU_REQUEST_GETSTATUS:

                    (*data)[0] = DFU_STATUS_OK; /* bStatus */
                    (*data)[1] = 0;
                    (*data)[2] = 0;
                    (*data)[3] = 0;
                    (*data)[4] = g_usbd_dfu.dfu_state;
                    (*data)[5] = 0; /* iString */
                    *len = 6;

                    usbd_dfu_reset();

                    break;
                case DFU_REQUEST_GETSTATE:
                    (*data)[0] = g_usbd_dfu.dfu_state;
                    *len = 1;
                    break;

                default:
                    return -1;
            }
            break;
        case DFU_STATE_DFU_ERROR:
            switch (setup->bRequest) {
                case DFU_REQUEST_CLRSTATUS:
                    g_usbd_dfu.dfu_state = DFU_STATE_DFU_IDLE;
                    break;

                default:
                    return -1;
            }
            break;

        default:
            USB_LOG_WRN("Invalid dfu state %s\r\n", usbd_dfu_state_string[g_usbd_dfu.dfu_state]);
            return -1;
    }
    return 0;
}

static void dfu_notify_handler(uint8_t busid, uint8_t event, void *arg)
{
    switch (event) {
        case USBD_EVENT_RESET:
            g_usbd_dfu.dfu_state = DFU_STATE_DFU_IDLE;
            break;
        default:
            break;
    }
}

struct usbd_interface *usbd_dfu_init_intf(struct usbd_interface *intf)
{
    intf->class_interface_handler = dfu_class_interface_request_handler;
    intf->class_endpoint_handler = NULL;
    intf->vendor_handler = NULL;
    intf->notify_handler = dfu_notify_handler;

    return intf;
}

uint8_t usbd_dfu_get_state(void)
{
    return g_usbd_dfu.dfu_state;
}

__WEAK void usbd_dfu_begin_load(void)
{
}

__WEAK void usbd_dfu_end_load(void)
{
}

__WEAK void usbd_dfu_reset(void)
{
}

__WEAK int usbd_dfu_write(uint16_t value, const uint8_t *data, uint16_t length)
{
    return 0;
}

__WEAK int usbd_dfu_read(uint16_t value, const uint8_t *data, uint16_t length, uint16_t *actual_length)
{
    return 0;
}