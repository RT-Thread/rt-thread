/*!
    \file  usbh_ctrl.h
    \brief header file for usbh_ctrl.c

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

#ifndef USBH_CTRL_H
#define USBH_CTRL_H

#include "usbh_core.h"
#include "usbh_usr.h"

/* constants definitions */
/* the enum of CTRL event */
typedef enum 
{
    CTRL_EVENT_IDLE = 0,                /* the ctrl idle event */
    CTRL_EVENT_SETUP,                   /* the ctrl setup event */
    CTRL_EVENT_DATA,                    /* the ctrl data event */
    CTRL_EVENT_STATUS,                  /* the ctrl status event */
    CTRL_EVENT_COMPLETE,                /* the ctrl complete event */
    CTRL_EVENT_ERROR,                   /* the ctrl error event */
    CTRL_EVENT_STALLED,                 /* the ctrl stalled event */
}ctrl_event_enum;

#define CTRL_HANDLE_TABLE_SIZE   13U    /*!< the ctrl handle table size define */

extern state_table_struct        ctrl_handle_table[CTRL_HANDLE_TABLE_SIZE];
extern uint8_t                   ctrl_polling_handle_flag;

/* function declarations */
/* the polling function of control transfer state handle */
usbh_status_enum ctrl_state_polling_fun (usb_core_handle_struct *pudev, usbh_host_struct *puhost, void *pustate);
/* send datas from the host channel */
usbh_status_enum usbh_xfer (usb_core_handle_struct *pudev, uint8_t *buf, uint8_t  hc_num, uint16_t len);
/* send the setup packet to the device */
usbh_status_enum usbh_ctltx_setup (usb_core_handle_struct *pudev, uint8_t *buf, uint8_t  hc_num);
/* this function prepare a hc and start a transfer */
uint32_t  hcd_submit_request (usb_core_handle_struct *pudev, uint8_t channel_num);

#endif /* USBH_CTRL_H */
