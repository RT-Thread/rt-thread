/*!
    \file    usb_iap_core.h
    \brief   the header file of IAP driver

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

#ifndef USB_IAP_CORE_H
#define USB_IAP_CORE_H

#include "usbd_enum.h"
#include "usb_hid.h"

#define USB_SERIAL_STRING_SIZE              0x06U                              /*!< serial string size */

#ifdef USE_USB_FS
    #define USB_DESC_LEN_IAP_REPORT         35U                                /*!< report descriptor length */
#elif defined(USE_USB_HS)
    #ifdef USE_ULPI_PHY
        #define USB_DESC_LEN_IAP_REPORT     37U                                /*!< report descriptor length */
    #else
        #define USB_DESC_LEN_IAP_REPORT     35U                                /*!< report descriptor length */
    #endif /* USE_ULPI_PHY */
#else
    #error "please select 'USE_USB_FS' or 'USE_USB_HS'"
#endif /* USE_USB_FS */

#define USB_DESC_LEN_IAP_CONFIG_SET         41U                                /*!< configuration descriptor length */

/* special commands with download request */
#define IAP_READ_OPTION_BYTE                0x01U
#define IAP_ERASE                           0x02U
#define IAP_DOWNLOAD                        0x03U
#define IAP_LEAVE                           0x04U
#define IAP_GETBIN_ADDRESS                  0x05U
#define IAP_WRITE_OPTION_BYTE               0x06U
#define IAP_UPLOAD                          0x07U
#define IAP_CHECK_RDP                       0x08U

#define OPERATION_SUCCESS                   0x02U
#define OPERATION_FAIL                      0x5FU
#define LEAVE_FINISH                        0x04U
#define OB_WRITE_SUCCESS                    0x03U
#define IS_RDP_MODE                         0xBBU
#define IS_NORMAL_MODE                      0xA5U

#define IAP_HOST_ID                         0x01U                                  /*!< IAP host ID */
#define IAP_DEVICE_ID                       0x02U                                  /*!< IAP device ID */

typedef struct {
    __ALIGN_BEGIN uint8_t report_buf[IAP_OUT_PACKET + 1U] __ALIGN_END;
    __ALIGN_BEGIN uint8_t option_byte[IAP_IN_PACKET] __ALIGN_END;

    /* state machine variables */
    __ALIGN_BEGIN uint8_t dev_status[IAP_IN_PACKET] __ALIGN_END;                   /*!< device status */
    __ALIGN_BEGIN uint8_t bin_addr[IAP_IN_PACKET] __ALIGN_END;                     /*!< load bin address */
    uint8_t reportID;                                                              /*!< report id */
    uint8_t flag;                                                                  /*!< flag */
    uint32_t protocol;                                                             /*!< control request protocol */
    uint32_t idlestate;                                                            /*!< control request idle state */
    uint16_t transfer_times;                                                       /*!< data transfer times */
    uint16_t page_count;                                                           /*!< memory page count */
    uint32_t file_length;                                                          /*!< file length*/
    uint32_t base_address;                                                         /*!< loaded base address */
} usbd_iap_handler;

typedef void (*app_func)(void);

extern usb_desc iap_desc;
extern usb_class_core iap_class;

/* function declarations */
/* send IAP report */
uint8_t iap_report_send(usb_dev *udev, uint8_t *report, uint32_t len);

#endif /* USB_IAP_CORE_H */
