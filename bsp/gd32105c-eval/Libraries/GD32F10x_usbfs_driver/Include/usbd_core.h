/*!
    \file  usbd_core.h
    \brief USB device mode core driver header file

    \version 2014-12-26, V1.0.0, firmware for GD32F10x
    \version 2017-06-20, V2.0.0, firmware for GD32F10x
    \version 2018-07-31, V2.1.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2018, GigaDevice Semiconductor Inc.

    All rights reserved.

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

#ifndef USBD_CORE_H
#define USBD_CORE_H

#include "usbd_conf.h"
#include "usb_core.h"
#include "usbd_std.h"

/* constants definitions */
/* device status */
#define USB_STATUS_DEFAULT                          1U     /* default status */
#define USB_STATUS_ADDRESSED                        2U     /* addressed status */
#define USB_STATUS_CONFIGURED                       3U     /* configured status */
#define USB_STATUS_SUSPENDED                        4U     /* suspended status */

/* function declarations */
/* initailizes the USB device-mode handler stack */
void usbd_init (usb_core_handle_struct *pudev, usb_core_id_enum core_id);
/* endpoint initialization */
void usbd_ep_init (usb_core_handle_struct *pudev, const usb_descriptor_endpoint_struct *ep_desc);
/* endpoint deinitialize */
void usbd_ep_deinit (usb_core_handle_struct *pudev, uint8_t ep_addr);
/* endpoint prepare to receive data */
void usbd_ep_rx (usb_core_handle_struct *pudev, uint8_t ep_addr, uint8_t *pbuf, uint16_t buf_len);
/* endpoint prepare to transmit data */
void usbd_ep_tx (usb_core_handle_struct *pudev, uint8_t ep_addr, uint8_t *pbuf, uint32_t buf_len);
/* transmit data on the control channel */
usbd_status_enum usbd_ctltx (usb_core_handle_struct *pudev, uint8_t *pbuf, uint16_t len);
/* receive data on the control channel */
usbd_status_enum usbd_ctlrx (usb_core_handle_struct *pudev, uint8_t *pbuf, uint16_t len);
/* transmit status on the control channel */
usbd_status_enum usbd_ctlstatus_tx (usb_core_handle_struct *pudev);
/* receive status on the control channel */
usbd_status_enum usbd_ctlstatus_rx (usb_core_handle_struct *pudev);
/* set an endpoint to stall status */
void usbd_ep_stall (usb_core_handle_struct *pudev, uint8_t ep_addr);
/* clear endpoint stalled status */
void usbd_ep_clear_stall (usb_core_handle_struct *pudev, uint8_t ep_addr);
/* flushes the fifos */
void usbd_ep_fifo_flush (usb_core_handle_struct *pudev, uint8_t ep_addr);
/* get the received data length */
uint16_t usbd_rxcount_get (usb_core_handle_struct *pudev, uint8_t ep_num);

#endif /* USBD_CORE_H */
