/*!
    \file    usbh_msc_bbb.h
    \brief   header file for usbh_msc_bbb.c

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

#ifndef USBH_MSC_BBB_H
#define USBH_MSC_BBB_H

#include "msc_bbb.h"
#include "usbh_core.h"

#define USBH_MSC_BBB_CBW_TAG                0x20304050U          /*!< MSC BBB CBW tag */

#define USBH_MSC_CSW_MAX_LENGTH             63U                  /*!< MSC CSW maximum length */

#define USBH_MSC_SEND_CSW_DISABLE           0U                   /*!< MSC send CSW disable */
#define USBH_MSC_SEND_CSW_ENABLE            1U                   /*!< MSC send CSW enable */

#define USBH_MSC_DIR_IN                     0U                   /*!< MSC data transfer IN */
#define USBH_MSC_DIR_OUT                    1U                   /*!< MSC data transfer OUT */
#define USBH_MSC_BOTH_DIR                   2U                   /*!< MSC data transfer IN/OUT */

#define USBH_MSC_PAGE_LENGTH                512U                 /*!< MSC memory page length */

#define CBW_CB_LENGTH                       16U                  /*!< MSC CBW CB length */
#define CBW_LENGTH                          10U                  /*!< MSC CBW length */
#define CBW_LENGTH_TEST_UNIT_READY          0U                   /*!< MSC CBW test unit ready length */

#define MAX_BULK_STALL_COUNT_LIMIT          0x04U                /*!< if STALL is seen on bulk 
                                                                      endpoint continously, this means 
                                                                      that device and host has phase error
                                                                      hence a reset is needed */

typedef union {
    msc_bbb_cbw field;                             /*!< MSC BBB CBW structure */

    uint8_t CBWArray[31];                          /*!< MSC BBB CBW array buff */
}usbh_cbw_pkt;

typedef union {
    msc_bbb_csw field;                             /*!< MSC BBB CSW structure */

    uint8_t CSWArray[13];                          /*!< MSC BBB CSW array buff */
}usbh_csw_pkt;

enum usbh_msc_state {
    USBH_MSC_BBB_INIT_STATE = 0U,                  /*!< MSC BBB init state */
    USBH_MSC_BBB_RESET,                            /*!< MSC BBB reset state */
    USBH_MSC_GET_MAX_LUN,                          /*!< MSC init state */
    USBH_MSC_TEST_UNIT_READY,                      /*!< MSC test unit ready state */
    USBH_MSC_READ_CAPACITY10,                      /*!< MSC read capacity10 state */
    USBH_MSC_MODE_SENSE6,                          /*!< MSC sense6 mode state */
    USBH_MSC_REQUEST_SENSE,                        /*!< MSC request sense state */
    USBH_MSC_BBB_USB_TRANSFERS,                    /*!< MSC BBB transfers state */
    USBH_MSC_DEFAULT_APPLI_STATE,                  /*!< MSC default application state */
    USBH_MSC_CTRL_ERROR_STATE,                     /*!< MSC control error state */
    USBH_MSC_UNRECOVERED_STATE                     /*!< MSC unrecovered state */
};

/* MSC BBB status types */
typedef enum {
    BBB_OK = 0U,                                   /*!< MSC BBB OK status */
    BBB_FAIL,                                      /*!< MSC BBB fail status */
    BBB_PHASE_ERROR,                               /*!< MSC BBB phase error status */
    BBB_BUSY                                       /*!< MSC BBB busy status */
} bbb_status;

/* MSC BBB command state types */
typedef enum {
    BBB_CMD_IDLE = 0U,                             /*!< MSC BBB command idle state */
    BBB_CMD_SEND,                                  /*!< MSC BBB command send state */
    BBB_CMD_WAIT                                   /*!< MSC BBB command wait state */
} bbb_cmd_state;

/* CSW status definitions */
typedef enum {
    BBB_CSW_CMD_PASSED = 0U,                       /*!< MSC BBB CSW command passed status */
    BBB_CSW_CMD_FAILED,                            /*!< MSC BBB CSW command failed status */
    BBB_CSW_PHASE_ERROR                            /*!< MSC BBB CSW phase error status */
} bbb_csw_status;

/* MSC BBB state types */
typedef enum {
    BBB_SEND_CBW = 1U,                             /*!< MSC BBB send CBW state */
    BBB_SEND_CBW_WAIT,                             /*!< MSC BBB send CBW wait state */
    BBB_DATA_IN,                                   /*!< MSC BBB data IN state */
    BBB_DATA_IN_WAIT,                              /*!< MSC BBB data IN wait state */
    BBB_DATA_OUT,                                  /*!< MSC BBB data OUT state */
    BBB_DATA_OUT_WAIT,                             /*!< MSC BBB data OUT wait state */
    BBB_RECEIVE_CSW,                               /*!< MSC BBB receive CSW state */
    BBB_RECEIVE_CSW_WAIT,                          /*!< MSC BBB receive CSW wait state */
    BBB_ERROR_IN,                                  /*!< MSC BBB error IN state */
    BBB_ERROR_OUT,                                 /*!< MSC BBB error OUT state */
    BBB_UNRECOVERED_ERROR                          /*!< MSC BBB unrecovered error state */
} bbb_state;

typedef struct {
    uint8_t                *pbuf;                  /*!< MSC BBB data buff pointer */
    uint32_t                data[16];              /*!< MSC BBB data buff */
    bbb_state               state;                 /*!< MSC BBB state */
    bbb_state               prev_state;            /*!< MSC BBB previous state */
    bbb_cmd_state           cmd_state;             /*!< MSC BBB command state */
    usbh_cbw_pkt            cbw;                   /*!< MSC CBW pocket structure */
    usbh_csw_pkt            csw;                   /*!< MSC CSW pocket structure */
} bbb_handle;

/* function declarations */
/* initialize the mass storage parameters */
void usbh_msc_bbb_init(usbh_host *uhost);
/* manage the different states of BBB transfer and updates the status to upper layer */
usbh_status usbh_msc_bbb_process(usbh_host *uhost, uint8_t lun);
/* manages the different error handling for STALL */
usbh_status usbh_msc_bbb_abort(usbh_host *uhost, uint8_t direction);
/* reset MSC BBB request structure */
usbh_status usbh_msc_bbb_reset(usbh_host *uhost);
/* decode the CSW received by the device and updates the same to upper layer */
bbb_csw_status usbh_msc_csw_decode(usbh_host *uhost);

#endif /* USBH_MSC_BBB_H */
