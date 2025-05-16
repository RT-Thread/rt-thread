/*!
    \file    usbh_hid_core.h
    \brief   header file for the usbh_hid_core.c

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

#ifndef USBH_HID_CORE_H
#define USBH_HID_CORE_H

#include "usb_hid.h"
#include "usbh_enum.h"
#include "usbh_transc.h"

#define HID_MIN_POLL                                    10U              /*!< HID minimum polling */
#define HID_REPORT_SIZE                                 16U              /*!< HID report size */
#define HID_QUEUE_SIZE                                  10U              /*!< HID queue size */

#define USB_HID_DESC_SIZE                               9U               /*!< HID descriptor size */

/* states for HID state machine */
typedef enum {
    HID_INIT = 0U,                                                       /*!< HID init state */
    HID_IDLE,                                                            /*!< HID idle state */
    HID_SEND_DATA,                                                       /*!< HID send data state */
    HID_BUSY,                                                            /*!< HID busy state */
    HID_GET_DATA,                                                        /*!< HID get data state */
    HID_SYNC,                                                            /*!< HID synchronous state */
    HID_POLL,                                                            /*!< HID polling state */
    HID_ERROR                                                            /*!< HID error state */
} hid_state;

/* state types of HID control request */
typedef enum {
    HID_REQ_INIT = 0U,                                                   /*!< HID init request */
    HID_REQ_IDLE,                                                        /*!< HID idle request */
    HID_REQ_GET_REPORT_DESC,                                             /*!< get report descriptor request */
    HID_REQ_GET_HID_DESC,                                                /*!< get HID descriptor request */
    HID_REQ_SET_IDLE,                                                    /*!< set idle request */
    HID_REQ_SET_PROTOCOL,                                                /*!< set protocol request */
    HID_REQ_SET_REPORT                                                   /*!< set report request */
} hid_ctlstate;

/* HID types */
typedef enum {
    HID_MOUSE    = 0x01U,                                                /*!< HID mouse type */
    HID_KEYBOARD = 0x02U,                                                /*!< HID keyboard type */
    HID_UNKNOWN  = 0xFFU                                                 /*!< unknown type */
} hid_type;

typedef struct {
     uint8_t  *buf;                                                      /*!< data FIFO buff pointer */
     uint16_t  head;                                                     /*!< data FIFO header */
     uint16_t  tail;                                                     /*!< data FIFO tail */
     uint16_t  size;                                                     /*!< data FIFO size */
     uint8_t   lock;                                                     /*!< data FIFO lock */
} data_fifo;

/* structure for HID process */
typedef struct _hid_process {
    uint8_t              pipe_in;                                 /*!< pipe IN */
    uint8_t              pipe_out;                                /*!< pipe OUT */
    uint8_t              ep_addr;                                 /*!< endpoint address */
    uint8_t              ep_in;                                   /*!< endpoint IN */
    uint8_t              ep_out;                                  /*!< endpoint OUT */
    uint8_t              *pdata;                                  /*!< HID data pointer */
    __IO uint8_t         data_ready;                              /*!< HID data ready */
    uint16_t             len;                                     /*!< HID data length */
    uint16_t             poll;                                    /*!< HID polling */
    __IO uint32_t        timer;                                   /*!< HID timer */
    usb_desc_hid         hid_desc;                                /*!< HID descriptor */
    hid_state            state;                                   /*!< HID state structure */
    hid_ctlstate         ctl_state;                               /*!< control request state structure */
    usbh_status          (*init)(usb_core_driver *udev, usbh_host *uhost);
    usbh_status          (*decode)(uint8_t *data);
} usbh_hid_handler;

extern usbh_class usbh_hid;

/* function declarations */
/* set HID report */
usbh_status usbh_set_report(usb_core_driver *udev, \
                            usbh_host *uhost, \
                            uint8_t report_type, \
                            uint8_t report_ID, \
                            uint8_t report_len, \
                            uint8_t *report_buf);

#endif /* USBH_HID_CORE_H */
