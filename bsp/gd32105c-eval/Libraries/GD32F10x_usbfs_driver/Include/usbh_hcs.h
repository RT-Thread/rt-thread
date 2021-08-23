/*!
    \file  usbh_hcs.h
    \brief header file for usbh_hcs.c

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

#ifndef USBH_HCS_H
#define USBH_HCS_H

#include "usbh_core.h"

/* constants definitions */
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
