/*!
    \file    dfu_core.h
    \brief   the header file of USB DFU device class core functions

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

#ifndef DFU_CORE_H
#define DFU_CORE_H

#include "usbd_enum.h"

/* DFU class code */
#define USB_DFU_CLASS                 0xFEU

/* DFU subclass code */
#define USB_DFU_SUBCLASS_UPGRADE      0x01U

/* DFU protocol code */
#define USB_DFU_PROTOCL_RUNTIME       0x01U                     /*!< runtime interface protocol */
#define USB_DFU_PROTOCL_DFU           0x02U                     /*!< DFU interface protocol */

/* manifestation state */
#define MANIFEST_COMPLETE             0x00U                     /*!< manifest complete state */
#define MANIFEST_IN_PROGRESS          0x01U                     /*!< manifest in progress state */

/* DFU attributes code */
#define USB_DFU_CAN_DOWNLOAD          0x01U                     /*!< download attribute */
#define USB_DFU_CAN_UPLOAD            0x02U                     /*!< upload attribute */
#define USB_DFU_MANIFEST_TOLERANT     0x04U                     /*!< manifest tolerant attribute */
#define USB_DFU_WILL_DETACH           0x08U                     /*!< detach attribute */

/* special commands with download request */
#define GET_COMMANDS                  0x00U                     /*!< get command request */
#define SET_ADDRESS_POINTER           0x21U                     /*!< set address pointer request */
#define ERASE                         0x41U                     /*!< erase request */

/* memory operation command */
#define CMD_ERASE                     0U                        /*!< erase command */
#define CMD_WRITE                     1U                        /*!< write command */

#define _BYTE1(x)                     (uint8_t)((x) & 0xFFU)                /*!< addressing cycle 1st byte */
#define _BYTE2(x)                     (uint8_t)(((x) & 0xFF00U) >> 8)       /*!< addressing cycle 2nd byte */
#define _BYTE3(x)                     (uint8_t)(((x) & 0xFF0000U) >> 16)    /*!< addressing cycle 3rd byte */

#define FLASH_ERASE_TIMEOUT           60U                       /*!< erase flash timeout */
#define FLASH_WRITE_TIMEOUT           80U                       /*!< write flash timeout */

/* bit detach capable = bit 3 in bmAttributes field */
#define DFU_DETACH_MASK               (uint8_t)(0x10U)

/* DFU descriptor type code */
#define DFU_DESC_TYPE                 0x21U

/* DFU device state defines */
typedef enum {
    STATE_APP_IDLE = 0x00U,                                     /*!< DFU APP idle state */
    STATE_APP_DETACH,                                           /*!< DFU APP detach state */
    STATE_DFU_IDLE,                                             /*!< idle state */
    STATE_DFU_DNLOAD_SYNC,                                      /*!< download synchronous state */
    STATE_DFU_DNBUSY,                                           /*!< download busy state */
    STATE_DFU_DNLOAD_IDLE,                                      /*!< download idle state */
    STATE_DFU_MANIFEST_SYNC,                                    /*!< manifest synchronous state */
    STATE_DFU_MANIFEST,                                         /*!< manifest state */
    STATE_DFU_MANIFEST_WAIT_RESET,                              /*!< manifest wait reset state */
    STATE_DFU_UPLOAD_IDLE,                                      /*!< upload idle state */
    STATE_DFU_ERROR                                             /*!< DFU error state */
} dfu_state;

/* DFU device status defines */
typedef enum {
    STATUS_OK = 0x00U,                                          /*!< no error status */
    STATUS_ERR_TARGET,                                          /*!< trigger error status */
    STATUS_ERR_FILE,                                            /*!< file error status */
    STATUS_ERR_WRITE,                                           /*!< write error status */
    STATUS_ERR_ERASE,                                           /*!< erase error status */
    STATUS_ERR_CHECK_ERASED,                                    /*!< check erased error status */
    STATUS_ERR_PROG,                                            /*!< program error status */
    STATUS_ERR_VERIFY,                                          /*!< verify error status */
    STATUS_ERR_ADDRESS,                                         /*!< address error status */
    STATUS_ERR_NOTDONE,                                         /*!< not done error status */
    STATUS_ERR_FIRMWARE,                                        /*!< firmware error status */
    STATUS_ERR_VENDOR,                                          /*!< vendor error status */
    STATUS_ERR_USBR,                                            /*!< USB reset error status */
    STATUS_ERR_POR,                                             /*!< power error status */
    STATUS_ERR_UNKNOWN,                                         /*!< unknown error status */
    STATUS_ERR_STALLEDPKT                                       /*!< stalled pocket error status */
} dfu_status;

/* DFU class-specific requests */
typedef enum {
    DFU_DETACH = 0U,                                            /*!< detach request */
    DFU_DNLOAD,                                                 /*!< download request */
    DFU_UPLOAD,                                                 /*!< upload request */
    DFU_GETSTATUS,                                              /*!< get status request */
    DFU_CLRSTATUS,                                              /*!< clear status request */
    DFU_GETSTATE,                                               /*!< get state request */
    DFU_ABORT,                                                  /*!< abort request */
    DFU_REQ_MAX                                                 /*!< maximum request */
} dfu_requests;

#pragma pack(1)

/* USB DFU function descriptor structure */
typedef struct {
    usb_desc_header header;               /*!< descriptor header, including type and size */
    uint8_t bmAttributes;                 /*!< DFU attributes */
    uint16_t wDetachTimeOut;              /*!< time, in milliseconds, that the device will wait after receipt of the DFU_DETACH request. */
    uint16_t wTransferSize;               /*!< maximum number of bytes that the device can accept per control-write transaction */
    uint16_t bcdDFUVersion;               /*!< numeric expression identifying the version of the DFU Specification release. */
} usb_desc_dfu_func;

#pragma pack()

/* USB configuration descriptor structure */
typedef struct {
    usb_desc_config config;              /*!< configuration descriptor */
    usb_desc_itf dfu_itf0;               /*!< DFU interface 0 descriptor */
    usb_desc_itf dfu_itf1;               /*!< DFU interface 1 descriptor */
    usb_desc_itf dfu_itf2;               /*!< DFU interface 2 descriptor */
    usb_desc_dfu_func dfu_func;          /*!< DFU function descriptor */
} usb_dfu_desc_config_set;

/* USB DFU handler structure */
typedef struct {
    uint8_t bStatus;                     /*!< DFU device current status */
    uint8_t bwPollTimeout0;              /*!< DFU device polling timeout 0 */
    uint8_t bwPollTimeout1;              /*!< DFU device polling timeout 1 */
    uint8_t bwPollTimeout2;              /*!< DFU device polling timeout 2 */
    uint8_t bState;                      /*!< DFU device current state */
    uint8_t iString;                     /*!< DFU device string */

    uint8_t manifest_state;              /*!< DFU device current manifest state */
    uint32_t data_len;                   /*!< DFU device data transfer length */
    uint16_t block_num;                  /*!< memory block number */
    uint32_t base_addr;                  /*!< memory base address */

    uint8_t buf[TRANSFER_SIZE];          /*!< data transfer buff */
} usbd_dfu_handler;

typedef void (*app_func)(void);

extern usb_desc dfu_desc;
extern usb_class_core dfu_class;

#endif  /* DFU_CORE_H */
