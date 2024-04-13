/*
 * Copyright (c) 2024, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _USB_OHCI_PRIV_H
#define _USB_OHCI_PRIV_H

#include "usbh_core.h"
#include "usbh_hub.h"
#include "usb_hc_ohci.h"

#define OHCI_HCOR ((struct ohci_hcor *)(uintptr_t)(bus->hcd.reg_base + CONFIG_USB_OHCI_HCOR_OFFSET))

int ohci_init(struct usbh_bus *bus);
int ohci_deinit(struct usbh_bus *bus);
uint16_t ohci_get_frame_number(struct usbh_bus *bus);
int ohci_roothub_control(struct usbh_bus *bus, struct usb_setup_packet *setup, uint8_t *buf);
int ohci_submit_urb(struct usbh_urb *urb);
int ohci_kill_urb(struct usbh_urb *urb);

void OHCI_IRQHandler(uint8_t busid);

#endif