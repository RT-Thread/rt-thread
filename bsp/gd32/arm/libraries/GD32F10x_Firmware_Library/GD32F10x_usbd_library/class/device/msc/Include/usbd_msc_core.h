/*!
    \file    usbd_msc_core.h
    \brief   the header file of USB MSC device class core functions

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

#ifndef __USBD_MSC_CORE_H
#define __USBD_MSC_CORE_H

#include "usbd_core.h"

/* mass storage device class code */
#define USB_CLASS_MSC                     0x08U

/* mass storage subclass code */
#define USB_MSC_SUBCLASS_RBC              0x01U
#define USB_MSC_SUBCLASS_ATAPI            0x02U
#define USB_MSC_SUBCLASS_UFI              0x04U
#define USB_MSC_SUBCLASS_SCSI             0x06U
#define USB_MSC_SUBCLASS_LOCKABLE         0x07U
#define USB_MSC_SUBCLASS_IEEE1667         0x08U

/* mass storage interface class control protocol codes */
#define USB_MSC_PROTOCOL_CBI              0x00U
#define USB_MSC_PROTOCOL_CBI_ALT          0x01U
#define USB_MSC_PROTOCOL_BBB              0x50U

/* mass storage request codes */
#define USB_MSC_REQ_CODES_ADSC            0x00U
#define USB_MSC_REQ_CODES_GET             0xFCU
#define USB_MSC_REQ_CODES_PUT             0xFDU
#define USB_MSC_REQ_CODES_GML             0xFEU
#define USB_MSC_REQ_CODES_BOMSR           0xFFU

/* mass storage class-specific request codes */
#define BBB_GET_MAX_LUN                   0xFEU
#define BBB_RESET                         0xFFU

#define USB_MSC_CONFIG_DESC_SIZE          32U

#define MSC_EPIN_SIZE                     MSC_DATA_PACKET_SIZE
#define MSC_EPOUT_SIZE                    MSC_DATA_PACKET_SIZE

/* USB configuration descriptor structure */
typedef struct
{
    usb_desc_config         config;

    usb_desc_itf            msc_itf;
    usb_desc_ep             msc_epin;
    usb_desc_ep             msc_epout;
} usb_desc_config_set;

extern usb_desc msc_desc;
extern usb_class msc_class;

#endif /* __USBD_MSC_CORE_H */
