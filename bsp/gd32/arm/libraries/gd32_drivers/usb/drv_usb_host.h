/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#ifndef DRV_USB_HOST_H
#define DRV_USB_HOST_H

#include "drv_usb_core.h"

#if defined(BSP_USING_USB) && defined(RT_USING_USB_HOST)

typedef enum
{
    USBH_OK = 0U,
    USBH_BUSY,
    USBH_FAIL,
    USBH_NOT_SUPPORTED,
    USBH_UNRECOVERED_ERROR,
    USBH_SPEED_UNKNOWN_ERROR,
    USBH_APPLY_DEINIT
} usbh_status;

/*!
    \brief      get USB even frame
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     USB even frame state
*/
__STATIC_INLINE uint8_t usb_frame_even(usb_core_driver *udev)
{
    return (uint8_t) !(udev->regs.hr->HFINFR & 0x01U);
}

/*!
    \brief      read USB port
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     port status
*/
__STATIC_INLINE uint32_t usb_port_read(usb_core_driver *udev)
{
    return *udev->regs.HPCS & ~(HPCS_PE | HPCS_PCD | HPCS_PEDC);
}

/*!
    \brief      get USB current speed
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     USB current speed
*/
__STATIC_INLINE uint32_t usb_curspeed_get(usb_core_driver *udev)
{
    return *udev->regs.HPCS & HPCS_PS;
}

/*!
    \brief      get USB current frame
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     USB current frame
*/
__STATIC_INLINE uint32_t usb_curframe_get(usb_core_driver *udev)
{
    return (udev->regs.hr->HFINFR & 0xFFFFU);
}

/* function declarations */
/* initializes USB core for host mode */
usb_status usb_host_init(usb_core_driver *udev);
/* control the VBUS to power */
void usb_portvbus_switch(usb_core_driver *udev, uint8_t state);
/* reset host port */
uint32_t usb_port_reset(usb_core_driver *udev);
/* initialize host pipe */
usb_status usb_pipe_init(usb_core_driver *udev, uint8_t pipe_num);
/* prepare host pipe for transferring packets */
usb_status usb_pipe_xfer(usb_core_driver *udev, uint8_t pipe_num);
/* halt host pipe */
usb_status usb_pipe_halt(usb_core_driver *udev, uint8_t pipe_num);
/* configure host pipe to do ping operation */
usb_status usb_pipe_ping(usb_core_driver *udev, uint8_t pipe_num);
/* stop the USB host and clean up FIFO */
void usb_host_stop(usb_core_driver *udev);

#endif /* BSP_USING_USB && RT_USING_USB_HOST */

#endif /* DRV_USB_HOST_H */
