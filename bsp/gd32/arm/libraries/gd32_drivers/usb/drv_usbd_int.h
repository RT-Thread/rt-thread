/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#ifndef DRV_USBD_INT_H
#define DRV_USBD_INT_H

#include "drv_usb_core.h"
#include "drv_usb_dev.h"

/* function declarations */
#ifdef USB_DEDICATED_EP1_ENABLED
/* USB dedicated OUT endpoint 1 interrupt service routine handler */
uint32_t usbd_int_dedicated_ep1out(usb_core_driver *udev);
/* USB dedicated IN endpoint 1 interrupt service routine handler */
uint32_t usbd_int_dedicated_ep1in(usb_core_driver *udev);
#endif /* USB_DEDICATED_EP1_ENABLED */

/* USB device-mode interrupts global service routine handler */
void usbd_isr(usb_core_driver *udev);

#endif /* DRV_USBD_INT_H */
