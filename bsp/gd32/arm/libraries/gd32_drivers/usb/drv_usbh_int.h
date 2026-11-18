/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#ifndef DRV_USBH_INT_H
#define DRV_USBH_INT_H

#include "drv_usb_host.h"

/* handle global host interrupt */
uint32_t usbh_isr(usb_core_driver *udev);

#endif /* DRV_USBH_INT_H */
