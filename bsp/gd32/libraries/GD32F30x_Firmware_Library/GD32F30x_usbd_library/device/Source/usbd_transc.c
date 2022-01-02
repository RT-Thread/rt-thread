/*!
    \file    usbd_transc.c
    \brief   USBD transaction function

    \version 2020-08-01, V3.0.0, firmware for GD32F30x
*/

/*
    Copyright (c) 2020, GigaDevice Semiconductor Inc.

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

#include "usbd_enum.h"
#include "usbd_transc.h"

/* local function prototypes ('static') */
static inline void usb_stall_transc (usb_dev *udev);
static inline void usb_ctl_status_in (usb_dev *udev);
static inline void usb_ctl_data_in (usb_dev *udev);
static inline void usb_ctl_out (usb_dev *udev);
static inline void usb_0len_packet_send (usb_dev *udev);

/*!
    \brief      USB setup stage processing
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
void _usb_setup_transc (usb_dev *udev, uint8_t ep_num)
{
    (void)ep_num;

    usb_reqsta reqstat = REQ_NOTSUPP;

    uint16_t count = udev->drv_handler->ep_read((uint8_t *)(&udev->control.req), 0U, (uint8_t)EP_BUF_SNG);

    if (count != USB_SETUP_PACKET_LEN) {
        usb_stall_transc(udev);

        return;
    }

    switch (udev->control.req.bmRequestType & USB_REQTYPE_MASK) {
    /* standard device request */
    case USB_REQTYPE_STRD:
        reqstat = usbd_standard_request(udev, &udev->control.req);
        break;

    /* device class request */
    case USB_REQTYPE_CLASS:
        reqstat = usbd_class_request(udev, &udev->control.req);
        break;

    /* vendor defined request */
    case USB_REQTYPE_VENDOR:
        reqstat = usbd_vendor_request(udev, &udev->control.req);
        break;

    default:
        break;
    }

    if (REQ_SUPP == reqstat) {
        if (0U == udev->control.req.wLength) {
            /* USB control transfer status in stage */
            usb_ctl_status_in(udev);
        } else {
            if (udev->control.req.bmRequestType & 0x80U) {
                usb_ctl_data_in(udev);
            } else {
                /* USB control transfer data out stage */
                usb_ctl_out(udev);
            }
        }
    } else {
        usb_stall_transc(udev);
    }
}

/*!
    \brief      data out stage processing
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint identifier(0..7)
    \param[out] none
    \retval     none
*/
void _usb_out0_transc (usb_dev *udev, uint8_t ep_num)
{
    if (((uint8_t)USBD_CONFIGURED == udev->cur_status) && (udev->class_core->ctlx_out != NULL)) {
        /* device class handle */
        (void)udev->class_core->ctlx_out(udev);
    }

    usb_transc_config(&udev->transc_out[ep_num], NULL, 0U, 0U);

    /* enter the control transaction status in stage */
    usb_ctl_status_in(udev);
}

/*!
    \brief      data in stage processing
    \param[in]  udev: pointer to USB device instance
    \param[in]  ep_num: endpoint identifier(0..7)
    \param[out] none
    \retval     none
*/
void _usb_in0_transc (usb_dev *udev, uint8_t ep_num)
{
    (void)ep_num;

    if (udev->control.ctl_zlp) {
        /* send 0 length packet */
        usb_0len_packet_send(udev);

        udev->control.ctl_zlp = 0U;
    }

    if (((uint8_t)USBD_CONFIGURED == udev->cur_status) && (udev->class_core->ctlx_in != NULL)) {
        (void)udev->class_core->ctlx_in(udev);
    }

    /* USB control transfer status out stage */
    usb_ctl_out(udev);

    if (0U != udev->dev_addr) {
        udev->drv_handler->set_addr(udev);

        udev->dev_addr = 0U;
    }
}

/*!
    \brief      USB stalled transaction
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static inline void usb_stall_transc (usb_dev *udev)
{
    usbd_ep_stall(udev, 0x0U);
}

/*!
    \brief      USB control transaction status in stage
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static inline void usb_ctl_status_in (usb_dev *udev)
{
    udev->drv_handler->ep_write(udev->transc_in[0].xfer_buf, 0U, 0U);
}

/*!
    \brief      USB control transaction data in stage
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static inline void usb_ctl_data_in (usb_dev *udev)
{
    usbd_ep_send(udev, 0U, udev->transc_in[0].xfer_buf, udev->transc_in[0].xfer_len);
}

/*!
    \brief      USB control transaction data out & status out stage
    \param[in]  udev: pointer to USB device instance
    \param[out] none
    \retval     none
*/
static inline void usb_ctl_out (usb_dev *udev)
{
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
