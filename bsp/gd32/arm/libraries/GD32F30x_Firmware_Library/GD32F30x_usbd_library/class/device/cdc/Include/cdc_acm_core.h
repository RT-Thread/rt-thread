/*!
    \file    cdc_acm_core.h
    \brief   the header file of cdc acm driver

    \version 2020-08-01, V3.0.0, firmware for GD32F30x
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

#ifndef __CDC_ACM_CORE_H
#define __CDC_ACM_CORE_H

#include "usbd_enum.h"

/* communications device class code */
#define USB_CLASS_CDC                           0x02U

/* CDC subclass code */
#define USB_CDC_SUBCLASS_DLCM                   0x01U
#define USB_CDC_SUBCLASS_ACM                    0x02U

/* communications interface class control protocol codes */
#define USB_CDC_PROTOCOL_NONE                   0x00U
#define USB_CDC_PROTOCOL_AT                     0x01U

/* data interface class code */
#define USB_CLASS_DATA                          0x0AU

#define USB_DESCTYPE_CDC_ACM                    0x21U
#define USB_DESCTYPE_CS_INTERFACE               0x24U

#define USB_CDC_ACM_CONFIG_DESC_SIZE            0x43U

/* class-specific notification codes for PSTN subclasses */
#define USB_CDC_NOTIFY_SERIAL_STATE             0x20U

/* class-specific request codes */
#define SEND_ENCAPSULATED_COMMAND               0x00U
#define GET_ENCAPSULATED_RESPONSE               0x01U
#define SET_COMM_FEATURE                        0x02U
#define GET_COMM_FEATURE                        0x03U
#define CLEAR_COMM_FEATURE                      0x04U
#define SET_LINE_CODING                         0x20U
#define GET_LINE_CODING                         0x21U
#define SET_CONTROL_LINE_STATE                  0x22U
#define SEND_BREAK                              0x23U
#define NO_CMD                                  0xFFU

#pragma pack(1)

/* CDC ACM line coding struct */
typedef struct {
    uint32_t dwDTERate;                   /*!< data terminal rate */
    uint8_t  bCharFormat;                 /*!< stop bits */
    uint8_t  bParityType;                 /*!< parity */
    uint8_t  bDataBits;                   /*!< data bits */
} acm_line;

/* notification structure */
typedef struct {
    uint8_t bmRequestType;                /*!< type of request */
    uint8_t bNotification;                /*!< communication interface class notifications */
    uint16_t wValue;                      /*!< value of notification */
    uint16_t wIndex;                      /*!< index of interface */
    uint16_t wLength;                     /*!< length of notification data */
} acm_notification;

/* header function struct */
typedef struct {
    usb_desc_header header;               /*!< descriptor header, including type and size. */
    uint8_t   bDescriptorSubtype;         /*!< bDescriptorSubtype: header function descriptor */
    uint16_t  bcdCDC;                     /*!< bcdCDC: low byte of spec release number (CDC1.10) */
} usb_desc_header_func;

/* call managment function struct */
typedef struct {
    usb_desc_header header;               /*!< descriptor header, including type and size. */
    uint8_t  bDescriptorSubtype;          /*!< bDescriptorSubtype:  call management function descriptor */
    uint8_t  bmCapabilities;              /*!< bmCapabilities: D0 is reset, D1 is ignored */
    uint8_t  bDataInterface;              /*!< bDataInterface: 1 interface used for call management */
} usb_desc_call_managment_func;

/* acm function struct */
typedef struct {
    usb_desc_header header;               /*!< descriptor header, including type and size. */
    uint8_t  bDescriptorSubtype;          /*!< bDescriptorSubtype: abstract control management descriptor */
    uint8_t  bmCapabilities;              /*!< bmCapabilities: D1 */
} usb_desc_acm_func;

/* union function struct */
typedef struct {
    usb_desc_header header;               /*!< descriptor header, including type and size. */
    uint8_t  bDescriptorSubtype;          /*!< bDescriptorSubtype: union function descriptor */
    uint8_t  bMasterInterface;            /*!< bMasterInterface: communication class interface */
    uint8_t  bSlaveInterface0;            /*!< bSlaveInterface0: data class interface */
} usb_desc_union_func;

#pragma pack()
/* configuration descriptor struct */
typedef struct {
    usb_desc_config                  config;
    usb_desc_itf                     cmd_itf;
    usb_desc_header_func             cdc_header;
    usb_desc_call_managment_func     cdc_call_managment;
    usb_desc_acm_func                cdc_acm;
    usb_desc_union_func              cdc_union;
    usb_desc_ep                      cdc_cmd_endpoint;
    usb_desc_itf                     cdc_data_interface;
    usb_desc_ep                      cdc_out_endpoint;
    usb_desc_ep                      cdc_in_endpoint;
} usb_cdc_desc_config_set;

#define USB_CDC_RX_LEN      64U

typedef struct {
    uint8_t pre_packet_send;
    uint8_t packet_sent;
    uint8_t packet_receive;

    uint8_t data[USB_CDC_RX_LEN];

    uint32_t receive_length;

    acm_line line_coding;
} usb_cdc_handler;

extern usb_desc cdc_desc;
extern usb_class cdc_class;

/* function declarations */
/* receive CDC ACM data */
void cdc_acm_data_receive(usb_dev *udev);
/* send CDC ACM data */
void cdc_acm_data_send(usb_dev *udev);
/* check cdc acm is ready for data transfer */
uint8_t cdc_acm_check_ready(usb_dev *udev);

#endif  /* __CDC_ACM_CORE_H */
