/*!
    \file  usbd_std.h
    \brief USB 2.0 standard defines

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

#ifndef USBD_STD_H
#define USBD_STD_H

#include "usb_std.h"
#include "usbd_core.h"
#include "usbd_conf.h"
#include <wchar.h>

/* constants definitions */
#define USBD_LANGID_STR_IDX                            0x00U     /*!< USB language ID string index*/
#define USBD_MFC_STR_IDX                               0x01U     /*!< USB manufacturer string index*/
#define USBD_PRODUCT_STR_IDX                           0x02U     /*!< USB product string index*/
#define USBD_SERIAL_STR_IDX                            0x03U     /*!< USB serial string index*/
#define USBD_CONFIG_STR_IDX                            0x04U     /*!< USB configuration string index*/
#define USBD_INTERFACE_STR_IDX                         0x05U     /*!< USB interface string index*/

#define USB_STATUS_REMOTE_WAKEUP                       0x02U     /*!< USB remote wakeup status*/
#define USB_STATUS_SELF_POWERED                        0x01U     /*!< USB self power status*/

#define USB_FEATURE_ENDP_HALT                          0x00U     /*!< USB halt endpoint feature*/
#define USB_FEATURE_REMOTE_WAKEUP                      0x01U     /*!< USB remote wakeup feature*/
#define USB_FEATURE_TEST_MODE                          0x02U     /*!< USB test mode feature*/

#define ENG_LANGID                                     0x0409U   /*!< USB english language id*/
#define CHN_LANGID                                     0x0804U   /*!< USB chinese language id*/

#define USB_DEVICE_DESC_SIZE                           0x12U     /*!< USB device descriptor size*/

#define LOWBYTE(x)           ((uint8_t)((x) & 0x00FFU))          /*!< USB lowbyte operation marco*/
#define HIGHBYTE(x)          ((uint8_t)(((x) & 0xFF00U) >> 8U))  /*!< USB highbyte operation marco*/

#define USB_MIN(a, b)        (((a) < (b)) ? (a) : (b))           /*!< USB minimum operation marco*/

#define WIDE_STRING(string)  _WIDE_STRING(string)
#define _WIDE_STRING(string) L##string

#define USBD_STRING_DESC(string) \
    (uint8_t *)&(struct { \
        uint8_t _len; \
        uint8_t _type; \
        wchar_t _data[sizeof(string)]; \
    }) { \
        sizeof(WIDE_STRING(string)) + 2U - 2U, \
        USB_DESCTYPE_STRING, \
        WIDE_STRING(string) \
    }

#define IS_NOT_EP0(ep_addr)   (((ep_addr) != 0x00U) && ((ep_addr) != 0x80U))

/* function declarations */
/* USB device setup transaction*/
usbd_status_enum usbd_setup_transaction (usb_core_handle_struct *pudev);
/* USB device out transaction*/
usbd_status_enum usbd_out_transaction (usb_core_handle_struct *pudev, uint8_t endp_num);
/* USB device in transaction*/
usbd_status_enum usbd_in_transaction (usb_core_handle_struct *pudev, uint8_t endp_num);
/* USB device enum error handle*/
void usbd_enum_error (usb_core_handle_struct *pudev, usb_device_req_struct *req);

#endif /* USBD_STD_H */
