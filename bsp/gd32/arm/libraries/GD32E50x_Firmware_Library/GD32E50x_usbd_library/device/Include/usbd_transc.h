/*!
    \file    usbd_transc.h
    \brief   USBD transaction

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef __USB_TRANSC_H
#define __USB_TRANSC_H

#include "usbd_core.h"

/*!
    \brief      USB transaction configure
    \param[in]  transc: pointer to USB device transaction instance
    \param[in]  buf: transfer data buffer
    \param[in]  len: transfer data length
    \param[in]  count: transfer data counter
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_transc_config (usb_transc *transc, uint8_t *buf, uint16_t len, uint16_t count)
{
    transc->xfer_buf = buf;
    transc->xfer_len = len;
    transc->xfer_count = count;
}

/*!
    \brief      USB stalled transaction
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
__STATIC_INLINE void usb_stall_transc (usb_dev *udev)
{
    usbd_ep_stall(udev, 0x0U);
}


/*!
    \brief      USB control transaction status IN stage
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static inline void usb_ctl_status_in (usb_dev *udev)
{
    udev->control.ctl_state = USBD_CTL_STATUS_IN;

    udev->drv_handler->ep_write(udev->transc_in[0].xfer_buf, 0U, 0U);
}

/*!
    \brief      USB control transaction data IN stage
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static inline void usb_ctl_data_in (usb_dev *udev)
{
    udev->control.ctl_state = USBD_CTL_DATA_IN;

    usbd_ep_send(udev, 0U, udev->transc_in[0].xfer_buf, udev->transc_in[0].xfer_len);
}

/*!
    \brief      USB control transaction data OUT stage
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static inline void usb_ctl_data_out (usb_dev *udev)
{
    udev->control.ctl_state = USBD_CTL_DATA_OUT;

    udev->drv_handler->ep_rx_enable(udev, 0U);
}

/*!
    \brief      USB control transaction status OUT stage
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static inline void usb_ctl_status_out (usb_dev *udev)
{
    udev->control.ctl_state = USBD_CTL_STATUS_OUT;

    udev->drv_handler->ep_rx_enable(udev, 0U);
}


/*!
    \brief      USB send 0 length data packet
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static inline void usb_0len_packet_send (usb_dev *udev)
{
    udev->drv_handler->ep_write(udev->transc_in[0].xfer_buf, 0U, 0U);
}


/* function declarations */
/* process USB SETUP transaction */
void _usb_setup_transc (usb_dev *udev, uint8_t ep_num);
/* process USB OUT transaction */
void _usb_out0_transc (usb_dev *udev, uint8_t ep_num);
/* process USB IN transaction */
void _usb_in0_transc (usb_dev *udev, uint8_t ep_num);

#endif /* __USB_TRANSC_H */
