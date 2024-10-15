/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_ADB_H
#define USBD_ADB_H

#include <stdint.h>

#define ADB_SHELL_LOALID     0x01
#define ADB_FILE_LOALID      0x02

// clang-format off
#define ADB_DESCRIPTOR_INIT(bFirstInterface, in_ep, out_ep, wMaxPacketSize)                   \
    USB_INTERFACE_DESCRIPTOR_INIT(bFirstInterface, 0x00, 0x02, 0xff, 0x42, 0x01, 0x02), \
    USB_ENDPOINT_DESCRIPTOR_INIT(in_ep, 0x02, wMaxPacketSize, 0x00),     \
    USB_ENDPOINT_DESCRIPTOR_INIT(out_ep, 0x02, wMaxPacketSize, 0x00)
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

struct usbd_interface *usbd_adb_init_intf(uint8_t busid, struct usbd_interface *intf, uint8_t in_ep, uint8_t out_ep);

void usbd_adb_notify_shell_read(uint8_t *data, uint32_t len);
void usbd_adb_notify_file_read(uint8_t *data, uint32_t len);
void usbd_adb_notify_write_done(void);
bool usbd_adb_can_write(void);
int usbd_abd_write(uint32_t localid, const uint8_t *data, uint32_t len);
void usbd_adb_close(uint32_t localid);

#ifdef __cplusplus
}
#endif

#endif /* USBD_ADB_H */