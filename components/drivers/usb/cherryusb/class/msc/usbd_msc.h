/*
 * Copyright (c) 2022, sakumisu
 * Copyright (c) 2024, zhihong chen
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_MSC_H
#define USBD_MSC_H

#include "usb_msc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Init msc interface driver */
struct usbd_interface *usbd_msc_init_intf(uint8_t busid, struct usbd_interface *intf,
                                          const uint8_t out_ep,
                                          const uint8_t in_ep);

void usbd_msc_get_cap(uint8_t busid, uint8_t lun, uint32_t *block_num, uint32_t *block_size);
int usbd_msc_sector_read(uint8_t busid, uint8_t lun, uint32_t sector, uint8_t *buffer, uint32_t length);
int usbd_msc_sector_write(uint8_t busid, uint8_t lun, uint32_t sector, uint8_t *buffer, uint32_t length);

void usbd_msc_set_readonly(uint8_t busid, bool readonly);
bool usbd_msc_set_popup(uint8_t busid);

#ifdef __cplusplus
}
#endif

#endif /* USBD_MSC_H */
