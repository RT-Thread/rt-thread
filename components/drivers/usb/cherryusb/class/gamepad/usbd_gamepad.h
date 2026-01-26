/*
 * Copyright (c) 2026, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBD_GAMEPAD_H
#define USBD_GAMEPAD_H

#include "usb_gamepad.h"

#define USBD_GAMEPAD_MODE_XINPUT  0
#define USBD_GAMEPAD_MODE_SWITCH  1
#define USBD_GAMEPAD_MODE_XBOXONE 2
#define USBD_GAMEPAD_MODE_PS4     3

struct usbd_interface *usbd_gamepad_xinput_init_intf(struct usbd_interface *intf);
struct usbd_interface *usbd_gamepad_switch_init_intf(struct usbd_interface *intf);

int usbd_gamepad_xinput_send_report(uint8_t ep, struct usb_gamepad_report *report);
int usbd_gamepad_switch_send_report(uint8_t ep, struct usb_gamepad_report *report);

#endif /* USBD_GAMEPAD_H */