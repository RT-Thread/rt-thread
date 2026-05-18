/*
 * Copyright (c) 2022 ~ 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_DFU_H
#define USBD_DFU_H

#include "usb_dfu.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Init dfu interface driver */
struct usbd_interface *usbd_dfu_init_intf(struct usbd_interface *intf);
uint8_t usbd_dfu_get_state(void);

void usbd_dfu_begin_load(void);
void usbd_dfu_end_load(void);
void usbd_dfu_reset(void);
int usbd_dfu_write(uint16_t value, const uint8_t *data, uint16_t length);
int usbd_dfu_read(uint16_t value, const uint8_t *data, uint16_t length, uint16_t *actual_length);

#ifdef __cplusplus
}
#endif

#endif /* USBD_DFU_H */
