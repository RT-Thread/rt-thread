/*!
    \file    usbh_hid_core.h
    \brief   header file for the usbh_hid_core.c

    \version 2020-08-01, V3.0.0, firmware for GD32F4xx
    \version 2022-03-09, V3.1.0, firmware for GD32F4xx
    \version 2022-06-30, V3.2.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2022, GigaDevice Semiconductor Inc.

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

#ifndef __USBH_HID_CORE_H
#define __USBH_HID_CORE_H

#include "usb_hid.h"
#include "usbh_enum.h"
#include "usbh_transc.h"

#define HID_MIN_POLL                                    10U
#define HID_REPORT_SIZE                                 16U
#define HID_QUEUE_SIZE                                  10U

#define USB_HID_DESC_SIZE                               9U

/* states for HID state machine */
typedef enum {
    HID_INIT = 0U,
    HID_IDLE,
    HID_SEND_DATA,
    HID_BUSY,
    HID_GET_DATA,
    HID_SYNC,
    HID_POLL,
    HID_ERROR,
} hid_state;

typedef enum {
    HID_REQ_INIT = 0U,
    HID_REQ_IDLE,
    HID_REQ_GET_REPORT_DESC,
    HID_REQ_GET_HID_DESC,
    HID_REQ_SET_IDLE,
    HID_REQ_SET_PROTOCOL,
    HID_REQ_SET_REPORT,
} hid_ctlstate;

typedef enum
{
    HID_MOUSE    = 0x01U,
    HID_KEYBOARD = 0x02U,
    HID_UNKNOWN  = 0xFFU,
} hid_type;

typedef struct
{
     uint8_t  *buf;
     uint16_t  head;
     uint16_t  tail;
     uint16_t  size;
     uint8_t   lock;
} data_fifo;

/* structure for HID process */
typedef struct _hid_process
{
    uint8_t              pipe_in;
    uint8_t              pipe_out;
    uint8_t              ep_addr;
    uint8_t              ep_in;
    uint8_t              ep_out;
    uint8_t              *pdata;
    __IO uint8_t         data_ready;
    uint16_t             len;
    uint16_t             poll;

    __IO uint32_t        timer;
    usb_desc_hid         hid_desc;

    hid_state            state;
    hid_ctlstate         ctl_state;

    usbh_status          (*init)(usb_core_driver *udev, usbh_host *uhost);
    usbh_status          (*decode)(uint8_t *data);
} usbh_hid_handler;

extern usbh_class usbh_hid;

/* function declarations */
/* set HID report */
usbh_status usbh_set_report (usb_core_driver *udev,
                             usbh_host *uhost,
                             uint8_t  report_type,
                             uint8_t  report_ID,
                             uint8_t  report_len,
                             uint8_t *report_buf);

#endif /* __USBH_HID_CORE_H */
