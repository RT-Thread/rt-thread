/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#ifndef DRV_USB_HW_H
#define DRV_USB_HW_H

#include "drv_usb_core.h"

/* function declarations */
/* configure USB clock */
void usb_rcu_config(uint32_t usb_periph);
/* configure USB data line GPIO */
void usb_gpio_config(void);
/* configure USB interrupt */
void usb_intr_config(uint32_t usb_periph);
/* delay in microseconds */
void usb_udelay(const uint32_t usec);
/* delay in milliseconds */
void usb_mdelay(const uint32_t msec);

/* configure USB clock */
void pllusb_rcu_config(uint32_t usb_periph);

#if defined(RT_USING_USB_HOST)
/* configure systick */
void systick_config(void);
/* configure USB VBus */
void usb_vbus_config(void);
/* drive USB VBus */
void usb_vbus_drive(uint8_t State);
#endif /* RT_USING_USB_HOST */

#endif /* DRV_USB_HW_H */
