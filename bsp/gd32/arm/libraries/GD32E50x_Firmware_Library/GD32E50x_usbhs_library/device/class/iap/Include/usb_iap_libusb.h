/*!
    \file    usb_iap_libusb.h
    \brief   the header file of IAP driver

    \version 2023-12-31, V1.4.0, firmware for GD32E50x
*/

/*
    Copyright (c) 2023, GigaDevice Semiconductor Inc.

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

#ifndef __USB_IAP_LIBUSB_H
#define __USB_IAP_LIBUSB_H

#include "usbd_enum.h"
#include "usb_hid.h"

#define USB_SERIAL_STRING_SIZE                  0x06U

#ifdef GD32F450
    #define DEVICE_ID                           0x40023D00U
#else
    #define DEVICE_ID                           0x40022100U
#endif

/* special commands with download request */
#define IAP_OPTION_BYTE1                    0x01U
#define IAP_ERASE                           0x02U
#define IAP_DNLOAD                          0x03U
#define IAP_LEAVE                           0x04U
#define IAP_GETBIN_ADDRESS                  0x05U
#define IAP_OPTION_BYTE2                    0x06U

typedef void (*pAppFunction) (void);

typedef struct
{
    usb_desc_config         config;
    usb_desc_itf            itf;
    usb_desc_ep             epin;
    usb_desc_ep             epout;
}usb_iap_libusb_desc_config_set;

extern void* const usbd_iap_strings[USB_STRING_COUNT];
extern const usb_desc_dev iap_dev_desc;
extern const usb_iap_libusb_desc_config_set iap_config_desc;

extern usb_class_core iap_libusb_class;

/* function declarations */
/* send IAP report */
uint8_t iap_data_send (usb_dev *udev, uint8_t *report, uint16_t len);

#endif /* __USB_IAP_LIBUSB_H */
