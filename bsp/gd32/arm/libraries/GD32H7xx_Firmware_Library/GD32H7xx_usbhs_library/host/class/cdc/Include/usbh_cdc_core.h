/*!
    \file    usbh_cdc_core.h
    \brief   header file for the usbh_cdc_core.c

    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
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

#ifndef __USBH_CDC_CORE_H
#define __USBH_CDC_CORE_H

#include "drv_usb_hw.h"
#include "usb_cdc.h"
#include "usbh_core.h"
#include "usbh_pipe.h"
#include "usbh_enum.h"
#include "usbh_transc.h"

#define CDC_BUFFER_SIZE                                    1024U
#define LINE_CODING_STRUCTURE_SIZE                         0x07U

/* states for CDC state machine */
typedef enum
{
    CDC_IDLE = 0U,
    CDC_READ_DATA,
    CDC_SEND_DATA,
    CDC_DATA_SENT,
    CDC_BUSY,
    CDC_GET_DATA,
    CDC_POLL,
    CDC_CTRL_STATE
} cdc_state;

/* CDC transfer state */
typedef struct _cdc_xfer
{
    volatile cdc_state cdc_cur_state;

    uint8_t *prxtx_buff;
    uint8_t *pfill_buff;
    uint8_t *pempty_buff;
    uint32_t buffer_len;
    uint16_t data_length;
} cdc_xfer;

typedef struct _cdc_usercb
{
    void  (*send)       (uint8_t *data_buf);
    void  (*receive)    (uint8_t *data_buf);
} cdc_usercb;

/* structure for CDC command interface */
typedef struct _cdc_cmd_itf
{
    uint8_t              pipe_notify;
    uint8_t              ep_notify;
    uint8_t              buff[8];
    uint16_t             ep_size_notify;
} cdc_cmd_itf;

/* structure for CDC data interface */
typedef struct _cdc_data_itf
{
    uint8_t              pipe_in;
    uint8_t              pipe_out;
    uint8_t              ep_in;
    uint8_t              ep_out;
    uint8_t              buff[8];
    uint16_t             ep_size_in;
    uint16_t             ep_size_out;
} cdc_data_itf;

/* states for CDC class state machine */
typedef enum
{
    CDC_SET_LINE_CODING_RQUEST = 0U,
    CDC_GET_LINE_CODING_RQUEST,
    CDC_SET_CONTROL_LINE_STATE_REQUEST,
    CDC_ERROR_STATE
} cdc_requests;

/* line coding structure */
typedef union {
    uint8_t array[LINE_CODING_STRUCTURE_SIZE];

   __ALIGN_BEGIN acm_line __ALIGN_END b;
} cdc_line_coding;

/* structure for CDC process */
typedef struct _cdc_process
{
    uint8_t         rx_enabled;
    cdc_xfer        tx_param;
    cdc_xfer        rx_param;
    cdc_line_coding line_code_get;
    cdc_line_coding line_code_set;
    cdc_cmd_itf     cmd_itf;
    cdc_data_itf    data_itf;
    cdc_requests    req_state;
    cdc_usercb      user_cb;
} usbh_cdc_handler;

extern usbh_class usbh_cdc;

/* function declarations */
/* send data to the device */
void cdc_data_send (usbh_host *uhost, uint8_t *data, uint16_t length);
/* send dummy data to the device */
void cdc_dummydata_send (usbh_host *uhost);
/* enable CDC receive */
void cdc_start_reception (usbh_host *uhost);
/* stop CDC receive */
void cdc_stop_reception (usbh_host *uhost);
/* get currently configured line coding */
usbh_status cdc_get_line_coding (usbh_host *uhost);
/* specify typical asynchronous line-character formatting properties */
usbh_status cdc_set_line_coding (usbh_host *uhost);
/* this request generates RS-232/V.24 style control signals */
usbh_status cdc_set_control_line_state (usbh_host *uhost);
/* this function prepares the state before issuing the class specific commands */
void cdc_change_state_to_issue_setconfig (usbh_host *uhost);
/* this function prepares the state before issuing the class specific commands */
void cdc_issue_getconfig (usbh_host *uhost);

#endif /* __USBH_CDC_CORE_H */
