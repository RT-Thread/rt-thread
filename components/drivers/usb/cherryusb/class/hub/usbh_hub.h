/*
 * Copyright (c) 2022, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_HUB_H
#define USBH_HUB_H

#include "usb_hub.h"

struct usbh_hub;

#define USBH_HUB_MAX_PORTS 4
/* Maximum size of an interrupt IN transfer */
#define USBH_HUB_INTIN_BUFSIZE ((USBH_HUB_MAX_PORTS + 8) >> 3)

#ifdef __cplusplus
extern "C" {
#endif

int usbh_hub_set_feature(struct usbh_hub *hub, uint8_t port, uint8_t feature);
int usbh_hub_clear_feature(struct usbh_hub *hub, uint8_t port, uint8_t feature);

void usbh_hub_thread_wakeup(struct usbh_hub *hub);

int usbh_hub_initialize(struct usbh_bus *bus);
int usbh_hub_deinitialize(struct usbh_bus *bus);

#ifdef __cplusplus
}
#endif

#endif /* USBH_HUB_H */
