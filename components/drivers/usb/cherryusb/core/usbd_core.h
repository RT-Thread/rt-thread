/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_CORE_H
#define USBD_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "usb_config.h"
#include "usb_util.h"
#include "usb_errno.h"
#include "usb_def.h"
#include "usb_list.h"
#include "usb_log.h"
#include "usb_dc.h"

enum usbd_event_type {
    /* USB DCD IRQ */
    USBD_EVENT_ERROR,        /** USB error reported by the controller */
    USBD_EVENT_RESET,        /** USB reset */
    USBD_EVENT_SOF,          /** Start of Frame received */
    USBD_EVENT_CONNECTED,    /** USB connected*/
    USBD_EVENT_DISCONNECTED, /** USB disconnected */
    USBD_EVENT_SUSPEND,      /** USB connection suspended by the HOST */
    USBD_EVENT_RESUME,       /** USB connection resumed by the HOST */

    /* USB DEVICE STATUS */
    USBD_EVENT_CONFIGURED,        /** USB configuration done */
    USBD_EVENT_SET_INTERFACE,     /** USB interface selected */
    USBD_EVENT_SET_REMOTE_WAKEUP, /** USB set remote wakeup */
    USBD_EVENT_CLR_REMOTE_WAKEUP, /** USB clear remote wakeup */
    USBD_EVENT_INIT,              /** USB init done when call usbd_initialize */
    USBD_EVENT_DEINIT,            /** USB deinit done when call usbd_deinitialize */
    USBD_EVENT_UNKNOWN
};

typedef int (*usbd_request_handler)(uint8_t busid, struct usb_setup_packet *setup, uint8_t **data, uint32_t *len);
typedef void (*usbd_endpoint_callback)(uint8_t busid, uint8_t ep, uint32_t nbytes);
typedef void (*usbd_notify_handler)(uint8_t busid, uint8_t event, void *arg);

struct usbd_endpoint {
    uint8_t ep_addr;
    usbd_endpoint_callback ep_cb;
};

struct usbd_interface {
    usbd_request_handler class_interface_handler;
    usbd_request_handler class_endpoint_handler;
    usbd_request_handler vendor_handler;
    usbd_notify_handler notify_handler;
    const uint8_t *hid_report_descriptor;
    uint32_t hid_report_descriptor_len;
    uint8_t intf_num;
};

struct usb_descriptor {
    const uint8_t *(*device_descriptor_callback)(uint8_t speed);
    const uint8_t *(*config_descriptor_callback)(uint8_t speed);
    const uint8_t *(*device_quality_descriptor_callback)(uint8_t speed);
    const uint8_t *(*other_speed_descriptor_callback)(uint8_t speed);
    const char *(*string_descriptor_callback)(uint8_t speed, uint8_t index);
    const struct usb_msosv1_descriptor *msosv1_descriptor;
    const struct usb_msosv2_descriptor *msosv2_descriptor;
    const struct usb_webusb_url_ex_descriptor *webusb_url_descriptor;
    const struct usb_bos_descriptor *bos_descriptor;
};

struct usbd_bus {
    uint8_t busid;
    uint32_t reg_base;
};

extern struct usbd_bus g_usbdev_bus[];

#ifdef USBD_IRQHandler
#error USBD_IRQHandler is obsolete, please call USBD_IRQHandler(xxx) in your irq
#endif

#ifdef CONFIG_USBDEV_ADVANCE_DESC
void usbd_desc_register(uint8_t busid, const struct usb_descriptor *desc);
#else
void usbd_desc_register(uint8_t busid, const uint8_t *desc);
void usbd_msosv1_desc_register(uint8_t busid, struct usb_msosv1_descriptor *desc);
void usbd_msosv2_desc_register(uint8_t busid, struct usb_msosv2_descriptor *desc);
void usbd_bos_desc_register(uint8_t busid, struct usb_bos_descriptor *desc);
#endif

void usbd_add_interface(uint8_t busid, struct usbd_interface *intf);
void usbd_add_endpoint(uint8_t busid, struct usbd_endpoint *ep);

uint16_t usbd_get_ep_mps(uint8_t busid, uint8_t ep);
uint8_t usbd_get_ep_mult(uint8_t busid, uint8_t ep);
bool usb_device_is_configured(uint8_t busid);

int usbd_initialize(uint8_t busid, uint32_t reg_base, void (*event_handler)(uint8_t busid, uint8_t event));
int usbd_deinitialize(uint8_t busid);

#ifdef __cplusplus
}
#endif

#endif /* USBD_CORE_H */
