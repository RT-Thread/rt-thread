/*
 * Copyright (c) 2022, sakumisu
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

/* Interface functions that need to be implemented by the user */
uint8_t *dfu_read_flash(uint8_t *src, uint8_t *dest, uint32_t len);
uint16_t dfu_write_flash(uint8_t *src, uint8_t *dest, uint32_t len);
uint16_t dfu_erase_flash(uint32_t add);
void dfu_leave(void);
#ifdef __cplusplus
}
#endif

#endif /* USBD_DFU_H */
