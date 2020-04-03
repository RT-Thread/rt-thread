/*!
    \file  usbh_enum.h
    \brief USB host mode USB enumeration header file

    \version 2019-6-5, V1.0.0, firmware for GD32 USBFS&USBHS
*/

/*
    Copyright (c) 2019, GigaDevice Semiconductor Inc.

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

#ifndef __USBH_ENUM_H
#define __USBH_ENUM_H

#include "usb_conf.h"
#include "usbh_core.h"

/* get the next descriptor header */
usb_desc_header *usbh_nextdesc_get (uint8_t *pbuf, uint16_t *ptr);

/* configure USB control status parameters */
void usbh_ctlstate_config (usbh_host *puhost, uint8_t *buf, uint16_t len);

/* get device descriptor from the USB device */
usbh_status usbh_devdesc_get (usb_core_driver *pudev, usbh_host *puhost, uint8_t len);

/* get configuration descriptor from the USB device */
usbh_status usbh_cfgdesc_get (usb_core_driver *pudev, usbh_host *puhost, uint16_t len);

/* get string descriptor from the USB device */
usbh_status usbh_strdesc_get (usb_core_driver *pudev, 
                              usbh_host *puhost,
                              uint8_t str_index, 
                              uint8_t *buf,
                              uint16_t len);

/* set the configuration value to the connected device */
usbh_status usbh_setcfg (usb_core_driver *pudev, usbh_host *puhost, uint16_t config);

/* set the address to the connected device */
usbh_status usbh_setaddress (usb_core_driver *pudev, usbh_host *puhost, uint8_t dev_addr);

/* clear or disable a specific feature */
usbh_status usbh_clrfeature (usb_core_driver *pudev,
                             usbh_host *puhost, 
                             uint8_t ep_num,
                             uint8_t pp_num); 

/* set the interface value to the connected device */
usbh_status usbh_setinterface (usb_core_driver *pudev, 
                               usbh_host *puhost,
                               uint8_t ep_num,
                               uint8_t alter_setting);

#endif /* __USBH_ENUM_H */
