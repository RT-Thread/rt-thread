/*!
    \file    usb_hid.h
    \brief   definitions for the USB HID class

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

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

#ifndef USB_HID_H
#define USB_HID_H

#include "usb_ch9_std.h"

#define USB_HID_CLASS               0x03U          /*!< HID class code */

#define USB_DESCTYPE_HID            0x21U          /*!< HID descriptor type */
#define USB_DESCTYPE_REPORT         0x22U          /*!< report descriptor type */

/* HID subclass code */
#define USB_HID_SUBCLASS_BOOT_ITF   0x01U

/* HID protocol codes */
#define USB_HID_PROTOCOL_KEYBOARD   0x01U         /*!< HID keyboard protocol */
#define USB_HID_PROTOCOL_MOUSE      0x02U         /*!< HID mouse protocol */

#define GET_REPORT                  0x01U         /*!< get report request */
#define GET_IDLE                    0x02U         /*!< get idle request */
#define GET_PROTOCOL                0x03U         /*!< get protocol request */
#define SET_REPORT                  0x09U         /*!< set report request */
#define SET_IDLE                    0x0AU         /*!< set idle request */
#define SET_PROTOCOL                0x0BU         /*!< set protocol request */

#pragma pack(1)

typedef struct {
    usb_desc_header header;     /*!< regular descriptor header containing the descriptor's type and length */

    uint16_t bcdHID;            /*!< BCD encoded version that the HID descriptor and device complies to */
    uint8_t  bCountryCode;      /*!< country code of the localized device, or zero if universal */
    uint8_t  bNumDescriptors;   /*!< total number of HID report descriptors for the interface */
    uint8_t  bDescriptorType;   /*!< type of HID report */
    uint16_t wDescriptorLength; /*!< length of the associated HID report descriptor, in bytes */
} usb_desc_hid;

#pragma pack()

typedef struct {
    usb_desc_config         config;             /*!< configure descriptor */
    usb_desc_itf            hid_itf;            /*!< HID interface descriptor */
    usb_desc_hid            hid_vendor;         /*!< HID vendor descriptor */
    usb_desc_ep             hid_epin;           /*!< HID IN endpoint descriptor */
    usb_desc_ep             hid_epout;          /*!< HID OUT endpoint descriptor */
}usb_hid_desc_config_set;

#endif /* USB_HID_H */
