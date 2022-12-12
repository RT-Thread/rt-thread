/*!
    \file    usbd_enum.h
    \brief   USB enumeration definitions

    \version 2020-07-17, V3.0.0, firmware for GD32F10x
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

#ifndef __USBD_ENUM_H
#define __USBD_ENUM_H

#include "usbd_core.h"
#include "usb_ch9_std.h"

#ifndef NULL
    #define NULL                 0U
#endif

/* request state enumeration */
typedef enum _usb_reqsta
{
    REQ_SUPP     = 0x0U,                         /* supported request */
    REQ_NOTSUPP  = 0x1U                          /* unsupported request */
} usb_reqsta;

/* string descriptor index enumeration */
enum _str_index
{
    STR_IDX_LANGID                = 0x0U,        /* language ID string index */
    STR_IDX_MFC                   = 0x1U,        /* manufacturer string index */
    STR_IDX_PRODUCT               = 0x2U,        /* product string index */
    STR_IDX_SERIAL                = 0x3U,        /* serial string index */
    STR_IDX_CONFIG                = 0x4U,        /* configuration string index */
    STR_IDX_ITF                   = 0x5U,        /* interface string index */
    STR_IDX_MAX                   = 0x6U         /* string index max value */
};

/* PWR status enumeration */
typedef enum
{
    USB_PWRSTA_SELF_POWERED       = 0x1U,        /* USB is in self powered status */
    USB_PWRSTA_REMOTE_WAKEUP      = 0x2U,        /* USB is in remote wakeup status */
} usb_pwrsta;

/* USB endpoint feature enumeration */
typedef enum
{
    USB_FEATURE_EP_HALT           = 0x0U,        /* USB has endpoint halt feature */
    USB_FEATURE_REMOTE_WAKEUP     = 0x1U,        /* USB has endpoint remote wakeup feature */
    USB_FEATURE_TEST_MODE         = 0x2U         /* USB has endpoint test mode feature */
} usb_feature;

#define ENG_LANGID                0x0409U        /* english language ID */
#define CHN_LANGID                0x0804U        /* chinese language ID */

/* device unique ID */
#define DEVICE_ID1                (0x1FFFF7E8U)  /* device ID1 */
#define DEVICE_ID2                (0x1FFFF7ECU)  /* device ID2 */
#define DEVICE_ID3                (0x1FFFF7F0U)  /* device ID3 */

#define DEVICE_ID                 (0x40022100U)  /* device ID information */

//#define USB_SERIAL_STRING_SIZE    0x1AU

/* USB device exported macros */
#define BYTE_SWAP(addr)      (((uint16_t)(*((uint8_t *)(addr)))) + \
                             (uint16_t)(((uint16_t)(*(((uint8_t *)(addr)) + 1U))) << 8U))
#define BYTE_LOW(x)          ((uint8_t)((x) & 0x00FFU))
#define BYTE_HIGH(x)         ((uint8_t)(((x) & 0xFF00U) >> 8U))

#define USB_MIN(a, b)        (((a) < (b)) ? (a) : (b))

#define CTL_EP(ep)           (((ep) == 0x00U) || ((ep) == 0x80U))

/* function declarations */
/* handle USB standard device request */
usb_reqsta usbd_standard_request (usb_dev *udev, usb_req *req);
/* handle device class request */
usb_reqsta usbd_class_request (usb_dev *udev, usb_req *req);
/* handle USB vendor request */
usb_reqsta usbd_vendor_request (usb_dev *udev, usb_req *req);
/* get serial string */
void serial_string_get (uint16_t *unicode_str);

#endif /* __USBD_ENUM_H */
