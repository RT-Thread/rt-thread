/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-11-07     RealThread   the first version
 */

#ifndef DRV_USB_DEV_H
#define DRV_USB_DEV_H

#include "drv_usb_core.h"

#if defined(BSP_USING_USB) && defined(RT_USING_USB_DEVICE)

#define EP_IN(x)                ((uint8_t)(0x80U | (x)))    /*!< device IN endpoint */
#define EP_OUT(x)               ((uint8_t)(x))              /*!< device OUT endpoint */
#define EP_MAX_PACKET_SIZE_MASK 0x07FFU                     /*!< endpoint maximum packet size mask */

#define USB_MIN(a, b) (((a) < (b)) ? (a) : (b))

/* static inline function definitions */

/*!
    \brief      configure the USB device to be disconnected
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_dev_disconnect(usb_core_driver *udev)
{
    udev->regs.dr->DCTL |= DCTL_SD;
}

/*!
    \brief      configure the USB device to be connected
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_dev_connect(usb_core_driver *udev)
{
    udev->regs.dr->DCTL &= ~DCTL_SD;
}

/*!
    \brief      set the USB device address
    \param[in]  udev: pointer to USB device
    \param[in]  dev_addr: device address for setting
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_devaddr_set(usb_core_driver *udev, uint8_t dev_addr)
{
    udev->regs.dr->DCFG &= ~DCFG_DAR;
    udev->regs.dr->DCFG |= (uint32_t)dev_addr << 4;
}

/*!
    \brief      read device all OUT endpoint interrupt register
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     interrupt status
*/
__STATIC_INLINE uint32_t usb_oepintnum_read(usb_core_driver *udev)
{
    uint32_t value = udev->regs.dr->DAEPINT;

    value &= udev->regs.dr->DAEPINTEN;

    return (value & DAEPINT_OEPITB) >> 16;
}

/*!
    \brief      read device OUT endpoint interrupt flag register
    \param[in]  udev: pointer to USB device
    \param[in]  ep_num: endpoint number
    \param[out] none
    \retval     interrupt status
*/
__STATIC_INLINE uint32_t usb_oepintr_read(usb_core_driver *udev, uint8_t ep_num)
{
    uint32_t value = udev->regs.er_out[ep_num]->DOEPINTF;

    value &= udev->regs.dr->DOEPINTEN;

    return value;
}

/*!
    \brief      read device all IN endpoint interrupt register
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     interrupt status
*/
__STATIC_INLINE uint32_t usb_iepintnum_read(usb_core_driver *udev)
{
    uint32_t value = udev->regs.dr->DAEPINT;

    value &= udev->regs.dr->DAEPINTEN;

    return value & DAEPINT_IEPITB;
}

/*!
    \brief      set remote wakeup signaling
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_rwkup_set(usb_core_driver *udev)
{
    if (udev->dev.pm.dev_remote_wakeup)
    {
        /* enable remote wakeup signaling */
        udev->regs.dr->DCTL |= DCTL_RWKUP;
    }
}

/*!
    \brief      reset remote wakeup signaling
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_rwkup_reset(usb_core_driver *udev)
{
    if (udev->dev.pm.dev_remote_wakeup)
    {
        /* disable remote wakeup signaling */
        udev->regs.dr->DCTL &= ~DCTL_RWKUP;
    }
}

/*!
    \brief      enable USB BCD function
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_bcd_enable(usb_core_driver *udev)
{
    udev->regs.gr->GCCFG |= GCCFG_BCDEN;
}

/*!
    \brief      disable USB BCD function
    \param[in]  udev: pointer to USB device
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_bcd_disable(usb_core_driver *udev)
{
    udev->regs.gr->GCCFG &= ~GCCFG_BCDEN;
}

/* function declarations */
/* initialize USB core registers for device mode */
usb_status usb_devcore_init(usb_core_driver *udev);
/* enable the USB device mode interrupts */
usb_status usb_devint_enable(usb_core_driver *udev);
/* active the USB endpoint 0 transaction */
usb_status usb_transc0_active(usb_core_driver *udev, usb_transc *transc);
/* active the USB transaction */
usb_status usb_ep_active(usb_core_driver *udev, uint8_t ep_addr, uint16_t ep_mps, uint8_t ep_attr);
/* deactivate the USB transaction */
usb_status usb_ep_deactivate(usb_core_driver *udev, uint8_t ep_addr);
/* configure USB transaction to start IN transfer */
usb_status usb_ep_inxfer(usb_core_driver *udev, uint8_t ep_addr, uint8_t *buf, uint16_t count);
/* configure USB transaction to start OUT transfer */
usb_status usb_ep_outxfer(usb_core_driver *udev, uint8_t ep_addr, uint8_t *buf, uint16_t count);
/* set the USB transaction STALL status */
usb_status usb_ep_stall(usb_core_driver *udev, uint8_t ep_addr);
/* clear the USB transaction STALL status */
usb_status usb_ep_clrstall(usb_core_driver *udev, uint8_t ep_addr);
/* read device IN endpoint interrupt flag register */
uint32_t usb_iepintr_read(usb_core_driver *udev, uint8_t ep_num);
/* configures OUT endpoint 0 to receive SETUP packets */
void usb_ctlep_startout(usb_core_driver *udev);
/* active remote wakeup signaling */
void usb_rwkup_active(usb_core_driver *udev);
/* active USB core clock */
void usb_clock_active(usb_core_driver *udev);
/* USB device suspend */
void usb_dev_suspend(usb_core_driver *udev);
/* stop the device and clean up FIFOs */
void usb_dev_stop(usb_core_driver *udev);
/* USB battery charging detect operation */
bcd_type usbd_bcd_detect(usb_core_driver *udev);

#endif /* BSP_USING_USB && RT_USING_USB_DEVICE */

#endif /* DRV_USB_DEV_H */
