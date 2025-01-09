/*!
    \file    usbh_core.h
    \brief   header file for the usbh_core.c

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

#ifndef USBH_MSC_CORE_H
#define USBH_MSC_CORE_H

#include "usb_msc.h"
#include "usbh_msc_scsi.h"
#include "usbh_msc_bbb.h"

#define MSC_MAX_SUPPORTED_LUN                   2U

/* MSC state types */
typedef enum {
    MSC_INIT = 0U,                                       /*!< MSC init state */
    MSC_IDLE,                                            /*!< MSC idle state */
    MSC_TEST_UNIT_READY,                                 /*!< MSC test unit ready state */
    MSC_READ_CAPACITY10,                                 /*!< MSC read capacity10 state */
    MSC_READ_INQUIRY,                                    /*!< MSC read inquiry state */
    MSC_REQUEST_SENSE,                                   /*!< MSC request sense state */
    MSC_READ,                                            /*!< MSC read state */
    MSC_WRITE,                                           /*!< MSC write state */
    MSC_UNRECOVERED_ERROR,                               /*!< MSC unrecovered state */
    MSC_PERIODIC_CHECK                                   /*!< MSC periodic check state */
} msc_state;

/* MSC error types */
typedef enum {
    MSC_OK = 0U,                                         /*!< MSC no error */
    MSC_NOT_READY,                                       /*!< MSC not ready */
    MSC_ERROR                                            /*!< MSC error */
} msc_error;

/* MSC request types */
typedef enum {
    MSC_REQ_IDLE = 0U,                                   /*!< MSC idle request state */
    MSC_REQ_RESET,                                       /*!< MSC reset request state */
    MSC_REQ_GET_MAX_LUN,                                 /*!< MSC get maximum LUN request state */
    MSC_REQ_ERROR                                        /*!< MSC error request state */
} msc_req_state;

/* structure for LUN */
typedef struct {
    msc_state               state;                       /*!< MSC LUN state */
    msc_error               error;                       /*!< MSC LUN error */
    msc_scsi_sense          sense;                       /*!< MSC SCSI sense */
    scsi_capacity           capacity;                    /*!< MSC SCSI capacity */
    scsi_std_inquiry_data   inquiry;                     /*!< MSC SCSI standard inquiry data */
    usbh_status             prev_ready_state;            /*!< MSC previous ready state */
    uint8_t                 state_changed;               /*!< MSC state changed */
} msc_lun;

/* structure for MSC process */
typedef struct _msc_process {
    uint8_t         pipe_in;                             /*!< MSC pipe IN */
    uint8_t         pipe_out;                            /*!< MSC pipe OUT */
    uint8_t         ep_in;                               /*!< MSC endpoint IN */
    uint8_t         ep_out;                              /*!< MSC endpoint OUT */
    uint16_t        ep_size_in;                          /*!< MSC endpoint IN size */
    uint16_t        ep_size_out;                         /*!< MSC endpoint OUT size */
    uint8_t         cur_lun;                             /*!< MSC current LUN */
    uint16_t        rw_lun;                              /*!< MSC review LUN */
    uint32_t        max_lun;                             /*!< MSC maximum LUN */
    msc_state       state;                               /*!< MSC state */
    msc_error       error;                               /*!< MSC error */
    msc_req_state   req_state;                           /*!< MSC request state */
    msc_req_state   prev_req_state;                      /*!< MSC previous request state */
    bbb_handle      bbb;                                 /*!< MSC BBB correlation parameter handle */
    msc_lun         unit[MSC_MAX_SUPPORTED_LUN];         /*!< MSC LUN unit buff */
    uint32_t        timer;                               /*!< MSC read/write timer */
} usbh_msc_handler;

extern usbh_class usbh_msc;

/* function declarations */
/* get MSC logic unit information */
usbh_status usbh_msc_lun_info_get(usbh_host *uhost, uint8_t lun, msc_lun *info);
/* MSC read interface */
usbh_status usbh_msc_read(usbh_host *uhost, \
                          uint8_t lun, \
                          uint32_t address, \
                          uint8_t *pbuf, \
                          uint32_t length);
/* MSC write interface */
usbh_status usbh_msc_write(usbh_host *uhost, \
                           uint8_t lun, \
                           uint32_t address, \
                           uint8_t *pbuf, \
                           uint32_t length);

#endif /* USBH_MSC_CORE_H */
