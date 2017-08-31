/*!
    \file  usbh_hcs.h
    \brief header file for usbh_hcs.c
*/

/*
    Copyright (C) 2016 GigaDevice

    2016-08-15, V1.0.0, firmware for GD32F4xx
*/

#ifndef USBH_HCS_H
#define USBH_HCS_H

#include "usbh_core.h"

#define HC_MAX                  8U

#define HC_OK                   0x0000U
#define HC_USED                 0x8000U
#define HC_ERROR                0xFFFFU
#define HC_USED_MASK            0x7FFFU

/* function declarations */
/* allocate a new channel for the pipe */
uint8_t usbh_channel_alloc (usb_core_handle_struct *pudev, uint8_t ep_addr);
/* free all usb host channel */
uint8_t usbh_allchannel_dealloc (usb_core_handle_struct *pudev);
/* free the usb host channel */
uint8_t usbh_channel_free (usb_core_handle_struct *pudev, uint8_t index);
/* open a channel */
uint8_t usbh_channel_open (usb_core_handle_struct *pudev, 
                           uint8_t  channel_num,
                           uint8_t  dev_addr,
                           uint8_t  dev_speed,
                           uint8_t  ep_type,
                           uint16_t ep_mps);
/* modify a channel */
uint8_t usbh_channel_modify (usb_core_handle_struct *pudev,
                             uint8_t  channel_num,
                             uint8_t  dev_addr,
                             uint8_t  dev_speed,
                             uint8_t  ep_type,
                             uint16_t ep_mps);

#endif /* USBH_HCS_H */
