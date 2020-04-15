/*!
    \file  usbd_int.h
    \brief USB device mode interrupt handler header file
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-02-10, V1.0.0, firmware for GD32F30x
*/

#ifndef USBD_INT_H
#define USBD_INT_H

#include "usbd_core.h"

typedef struct
{
    uint8_t (*SOF) (usb_core_handle_struct *pudev);
}usbd_int_cb_struct;

extern usbd_int_cb_struct *usbd_int_fops;

/* function declarations */
/* USB device-mode interrupts global service routine handler */
uint32_t usbd_isr (usb_core_handle_struct *pudev);

#endif /* USBD_INT_H */

