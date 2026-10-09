/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#ifndef __DRV_OTGFS_HOST_H__
#define __DRV_OTGFS_HOST_H__


#include <rtthread.h>

#include "drv_usb_host.h"
#include "drv_usbh_transc.h"
#include "drv_usbh_pipe.h"

#define OTG_FS_PORT 1

#if defined(BSP_USING_USB) && defined(RT_USING_USB_HOST)

extern usb_core_driver gd_usb_host_core;
extern volatile rt_uint32_t gd_usbh_irq_count;

void usbh_connect_callback(usb_core_driver *hhcd);

void usbh_disconnect_callback(usb_core_driver *hhcd);

void usbh_hc_notifyurbchange_callback(usb_core_driver *hhcd, uint8_t chnum, usb_urb_state urb_state);

int gd_usbh_register(void);

#endif /* BSP_USING_USB && RT_USING_USB_HOST */
#endif
