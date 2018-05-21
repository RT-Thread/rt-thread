/*!
    \file  usbh_int.h
    \brief USB host mode interrupt handler header file
*/

/*
    Copyright (C) 2017 GigaDevice

    2017-02-10, V1.0.0, firmware for GD32F30x
*/

#ifndef USBH_INT_H
#define USBH_INT_H

#include "usb_core.h"

typedef struct
{
    uint8_t (*sof)                  (usb_core_handle_struct *pudev);
    uint8_t (*device_connected)     (usb_core_handle_struct *pudev);
    uint8_t (*device_disconnected)  (usb_core_handle_struct *pudev);
}usbh_hcd_int_cb_struct;

extern usbh_hcd_int_cb_struct *usbh_hcd_int_fops;

/* function declarations */
/* handle global host interrupt */
uint32_t usbh_isr (usb_core_handle_struct *pudev);

#endif /* USBH_INT_H */
