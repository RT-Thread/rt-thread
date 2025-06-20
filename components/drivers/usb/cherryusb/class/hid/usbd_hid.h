/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_HID_H
#define USBD_HID_H

#include "usb_hid.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Init hid interface driver */
struct usbd_interface *usbd_hid_init_intf(uint8_t busid, struct usbd_interface *intf, const uint8_t *desc, uint32_t desc_len);

/* Setup request command callback api */
void usbd_hid_get_report(uint8_t busid, uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t **data, uint32_t *len);
uint8_t usbd_hid_get_idle(uint8_t busid, uint8_t intf, uint8_t report_id);
uint8_t usbd_hid_get_protocol(uint8_t busid, uint8_t intf);
void usbd_hid_set_report(uint8_t busid, uint8_t intf, uint8_t report_id, uint8_t report_type, uint8_t *report, uint32_t report_len);
void usbd_hid_set_idle(uint8_t busid, uint8_t intf, uint8_t report_id, uint8_t duration);
void usbd_hid_set_protocol(uint8_t busid, uint8_t intf, uint8_t protocol);

#ifdef __cplusplus
}
#endif

#endif /* USBD_HID_H */
