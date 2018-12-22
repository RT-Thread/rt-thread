/*!
    \file  usbd_core.h
    \brief USB device-mode core driver header file
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/


#ifndef USBD_CORE_H
#define USBD_CORE_H

#include "usbd_conf.h"
#include "usb_core.h"
#include "usbd_std.h"

/* device status */
#define USB_STATUS_DEFAULT                          1U     /* default status */
#define USB_STATUS_ADDRESSED                        2U     /* addressed status */
#define USB_STATUS_CONFIGURED                       3U     /* configured status */
#define USB_STATUS_SUSPENDED                        4U     /* suspended status */

/* function declarations */
/* initailizes the USB device-mode handler stack */
void usbd_init (usb_core_handle_struct *pudev, usb_core_id_enum core_id);
/* endpoint initialization */
void usbd_ep_init (usb_core_handle_struct *pudev, const usb_descriptor_endpoint_struct *pep_desc);
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
/* set an endpoint to STALL status */
void usbd_ep_stall (usb_core_handle_struct *pudev, uint8_t ep_addr);
/* clear endpoint stalled status */
void usbd_ep_clear_stall (usb_core_handle_struct *pudev, uint8_t ep_addr);
/* flushes the FIFOs */
void usbd_ep_fifo_flush (usb_core_handle_struct *pudev, uint8_t ep_addr);
/* get the received data length */
uint16_t usbd_rxcount_get (usb_core_handle_struct *pudev, uint8_t ep_id);

#endif /* USBD_CORE_H */
