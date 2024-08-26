/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_CDC_ACM_H
#define USBD_CDC_ACM_H

#include "usb_cdc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Init cdc acm interface driver */
struct usbd_interface *usbd_cdc_acm_init_intf(uint8_t busid, struct usbd_interface *intf);

/* Setup request command callback api */
void usbd_cdc_acm_set_line_coding(uint8_t busid, uint8_t intf, struct cdc_line_coding *line_coding);
void usbd_cdc_acm_get_line_coding(uint8_t busid, uint8_t intf, struct cdc_line_coding *line_coding);
void usbd_cdc_acm_set_dtr(uint8_t busid, uint8_t intf, bool dtr);
void usbd_cdc_acm_set_rts(uint8_t busid, uint8_t intf, bool rts);
void usbd_cdc_acm_send_break(uint8_t busid, uint8_t intf);

#ifdef __cplusplus
}
#endif

#endif /* USBD_CDC_ACM_H */
