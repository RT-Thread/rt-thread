/*!
    \file    usbh_msc_scsi.h
    \brief   header file for usbh_msc_scsi.c

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

#ifndef USBH_MSC_SCSI_H
#define USBH_MSC_SCSI_H

#include "msc_scsi.h"
#include "usbh_enum.h"

#define DESC_REQUEST_SENSE                   00U                  /*!< sense request descriptor */
#define ALLOCATION_LENGTH_REQUEST_SENSE      63U                  /*!< sense request allocation length */
#define XFER_LEN_MODE_SENSE6                 63U                  /*!< MSC sense6 mode transfer length */

#define MASK_MODE_SENSE_WRITE_PROTECT        0x80U                /*!< sense write protect mask mode */
#define MODE_SENSE_PAGE_CONTROL_FIELD        0x00U                /*!< sense page control field mode */
#define MODE_SENSE_PAGE_CODE                 0x3FU                /*!< sense page code mode */
#define DISK_WRITE_PROTECTED                 0x01U                /*!< disk write protected */

/* capacity data */
typedef struct {
    uint32_t block_nbr;                         /*!< MSC SCSI block number */
    uint16_t block_size;                        /*!< MSC SCSI block size */
} scsi_capacity;

/* inquiry data */
typedef struct {
    uint8_t peripheral_qualifier;               /*!< MSC SCSI standard peripheral qualifier */
    uint8_t device_type;                        /*!< MSC SCSI standard inquiry device types */
    uint8_t removable_media;                    /*!< MSC SCSI standard inquiry removable media */
    uint8_t vendor_id[9];                       /*!< MSC SCSI standard inquiry vendor id buff */
    uint8_t product_id[17];                     /*!< MSC SCSI standard inquiry product id buff */
    uint8_t revision_id[5];                     /*!< MSC SCSI standard inquiry revision id buff */
} scsi_std_inquiry_data;

typedef struct {
    uint32_t msc_capacity;                      /*!< MSC capacity */
    uint32_t msc_sense_key;                     /*!< MSC sense key */
    uint16_t msc_page_len;                      /*!< MSC memory page length */
    uint8_t msc_write_protect;                  /*!< MSC write protect */
}usbh_msc_parameter;

/* function declarations */
/* send 'inquiry' command to the device */
usbh_status usbh_msc_scsi_inquiry(usbh_host *uhost, uint8_t lun, scsi_std_inquiry_data *inquiry);
/* send 'test unit ready' command to the device */
usbh_status usbh_msc_test_unitready(usbh_host *uhost, uint8_t lun);
/* send the read capacity command to the device */
usbh_status usbh_msc_read_capacity10(usbh_host *uhost, uint8_t lun, scsi_capacity *capacity);
/* send the mode sense6 command to the device */
usbh_status usbh_msc_mode_sense6(usbh_host *uhost, uint8_t lun);
/* send the request sense command to the device */
usbh_status usbh_msc_request_sense(usbh_host *uhost, uint8_t lun, msc_scsi_sense *sense_data);
/* send the write10 command to the device */
usbh_status usbh_msc_write10(usbh_host *uhost, \
                             uint8_t lun, \
                             uint8_t *data_buf, \
                             uint32_t addr, \
                             uint32_t byte_num);
/* send the read10 command to the device */
usbh_status usbh_msc_read10(usbh_host *uhost, \
                            uint8_t lun, \
                            uint8_t *data_buf, \
                            uint32_t addr, \
                            uint32_t byte_num);

#endif /* USBH_MSC_SCSI_H */
