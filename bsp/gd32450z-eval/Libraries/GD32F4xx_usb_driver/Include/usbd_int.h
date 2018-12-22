/*!
    \file  usbd_int.h
    \brief USB device-mode interrupt handler header file
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef USBD_INT_H
#define USBD_INT_H

#include "usbd_core.h"

/* function declarations */
/* USB device-mode interrupts global service routine handler */
uint32_t usbd_isr (usb_core_handle_struct *pudev);

#ifdef USBHS_DEDICATED_EP1_ENABLED

/* USB dedicated OUT endpoint 1 interrupt service routine handler */
uint32_t USBD_EP1OUT_ISR_Handler (usb_core_handle_struct *pudev);
/* USB dedicated IN endpoint 1 interrupt service routine handler */
uint32_t USBD_EP1IN_ISR_Handler (usb_core_handle_struct *pudev);

#endif /* USBHS_DEDICATED_EP1_ENABLED */

#endif /* USBD_INT_H */

