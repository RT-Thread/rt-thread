/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#ifndef __DRV_USBH_TRANSC_H
#define __DRV_USBH_TRANSC_H

#include "drv_usb_host.h"

#if defined(BSP_USING_USB) && defined(RT_USING_USB_HOST)

/* send the setup packet to the USB device */
usbh_status usbh_ctlsetup_send(usb_core_driver *pudev, uint8_t *buf, uint8_t pp_num);

/* send a data packet to the USB device */
usbh_status usbh_data_send(usb_core_driver *pudev, uint8_t *buf, uint8_t pp_num, uint16_t len);

/* receive a data packet from the USB device */
usbh_status usbh_data_recev(usb_core_driver *pudev, uint8_t *buf, uint8_t pp_num, uint16_t len);

/* get USB URB state */
static inline usb_urb_state usbh_urbstate_get(usb_core_driver *pudev, uint8_t pp_num)
{
    return pudev->host.pipe[pp_num].urb_state;
}

/* get USB transfer data count */
static inline uint32_t usbh_xfercount_get(usb_core_driver *pudev, uint8_t pp_num)
{
    return pudev->host.backup_xfercount[pp_num];
}

#endif /* BSP_USING_USB && RT_USING_USB_HOST */
#endif /* __DRV_USBH_TRANSC_H */
