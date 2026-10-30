/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#ifndef __DRV_USBH_PIPE_H
#define __DRV_USBH_PIPE_H

#include "drv_usb_host.h"

#define HC_MAX 8U

#define HC_OK        0x0000U
#define HC_USED      0x8000U
#define HC_ERROR     0xFFFFU
#define HC_USED_MASK 0x7FFFU

/* allocate a new pipe */
uint8_t usbh_pipe_allocate(usb_core_driver *pudev, uint8_t ep_addr);

/* delete all USB host pipe */
uint8_t usbh_pipe_delete(usb_core_driver *pudev);

/* free a pipe */
uint8_t usbh_pipe_free(usb_core_driver *pudev, uint8_t pp_num);

/* create a pipe */
uint8_t usbh_pipe_create(usb_core_driver *pudev,
                         uint8_t dev_addr,
                         uint8_t dev_speed,
                         uint8_t pp_num,
                         uint8_t ep_num,
                         uint8_t ep_type,
                         uint16_t ep_mpl);

/* modify a pipe */
uint8_t usbh_pipe_update(usb_core_driver *pudev,
                         uint8_t pp_num,
                         uint8_t dev_addr,
                         uint32_t dev_speed,
                         uint16_t ep_mpl);

#endif /* __DRV_USBH_PIPE_H */
