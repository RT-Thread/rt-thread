/*
 * Copyright (c) 2025, sakumisu
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef USBH_HID_LVGL_H
#define USBH_HID_LVGL_H

#include "lvgl.h"

lv_indev_t *usbh_hid_lvgl_add_mouse(uint8_t sensitivity);
lv_indev_t *usbh_hid_lvgl_add_keyboard(void);

#endif