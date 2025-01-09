/*!
    \file    msc_scsi.h
    \brief   definitions for the USB MSC SCSI commands

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

#ifndef MSC_SCSI_H
#define MSC_SCSI_H

#include "usb_ch9_std.h"

/* SCSI commands */
#define SCSI_FORMAT_UNIT                            0x04U        /*!< MSC SCSI format unit */
#define SCSI_INQUIRY                                0x12U        /*!< MSC SCSI inquiry */
#define SCSI_MODE_SELECT6                           0x15U        /*!< MSC SCSI select6 mode */
#define SCSI_MODE_SELECT10                          0x55U        /*!< MSC SCSI select10 mode */
#define SCSI_MODE_SENSE6                            0x1AU        /*!< MSC SCSI sense6 mode */
#define SCSI_READ_TOC_DATA                          0x43U        /*!< MSC SCSI read TOC data */
#define SCSI_MODE_SENSE10                           0x5AU        /*!< MSC SCSI sense10 mode */
#define SCSI_ALLOW_MEDIUM_REMOVAL                   0x1EU        /*!< MSC SCSI allow medium removal */
#define SCSI_READ6                                  0x08U        /*!< MSC SCSI read6 */
#define SCSI_READ10                                 0x28U        /*!< MSC SCSI read10 */
#define SCSI_READ12                                 0xA8U        /*!< MSC SCSI read12 */
#define SCSI_READ16                                 0x88U        /*!< MSC SCSI read16 */

#define SCSI_READ_CAPACITY10                        0x25U        /*!< MSC SCSI read capacity10 */
#define SCSI_READ_CAPACITY16                        0x9EU        /*!< MSC SCSI read capacity16 */

#define SCSI_REQUEST_SENSE                          0x03U        /*!< MSC SCSI request sense */
#define SCSI_START_STOP_UNIT                        0x1BU        /*!< MSC SCSI start stop unit */
#define SCSI_TEST_UNIT_READY                        0x00U        /*!< MSC SCSI test unit ready */
#define SCSI_WRITE6                                 0x0AU        /*!< MSC SCSI write6 */
#define SCSI_WRITE10                                0x2AU        /*!< MSC SCSI write10 */
#define SCSI_WRITE12                                0xAAU        /*!< MSC SCSI write12 */
#define SCSI_WRITE16                                0x8AU        /*!< MSC SCSI write16 */

#define SCSI_VERIFY10                               0x2FU        /*!< MSC SCSI verify10 */
#define SCSI_VERIFY12                               0xAFU        /*!< MSC SCSI verify12 */
#define SCSI_VERIFY16                               0x8FU        /*!< MSC SCSI verify16 */

#define SCSI_SEND_DIAGNOSTIC                        0x1DU        /*!< MSC SCSI send diagnostic */
#define SCSI_READ_FORMAT_CAPACITIES                 0x23U        /*!< MSC SCSI read format capacities */

#define INVALID_CDB                                 0x20U        /*!< invalid CDB */
#define INVALID_FIELD_IN_COMMAND                    0x24U        /*!< invalid field in command */
#define PARAMETER_LIST_LENGTH_ERROR                 0x1AU        /*!< parameter list length error */
#define INVALID_FIELD_IN_PARAMETER_LIST             0x26U        /*!< invalid field in parameter list */
#define ADDRESS_OUT_OF_RANGE                        0x21U        /*!< address out of range */
#define MEDIUM_NOT_PRESENT                          0x3AU        /*!< medium not present */
#define MEDIUM_HAVE_CHANGED                         0x28U        /*!< medium have changed */
#define WRITE_PROTECTED                             0x27U        /*!< write protected */
#define UNRECOVERED_READ_ERROR                      0x11U        /*!< unrecovered read error */
#define WRITE_FAULT                                 0x03U        /*!< write fault */

#define READ_FORMAT_CAPACITY_DATA_LEN               0x0CU        /*!< read format capacity data length */
#define READ_CAPACITY10_DATA_LEN                    0x08U        /*!< read capacity10 data length */
#define MODE_SENSE10_DATA_LEN                       0x08U        /*!< sense10 mode data length */
#define MODE_SENSE6_DATA_LEN                        0x04U        /*!< sense6 mode data length */
#define READ_TOC_CMD_LEN                            0x14U        /*!< read TOC command length */
#define REQUEST_SENSE_DATA_LEN                      0x12U        /*!< request sense data length */
#define STANDARD_INQUIRY_DATA_LEN                   0x24U        /*!< standard inquiry data length */
#define BLKVFY                                      0x04U        /*!< block verify */

enum sense_state {
    NO_SENSE = 0U,                                  /*!< MSC SCSI Sense NO_SENSE state */
    RECOVERED_ERROR,                                /*!< MSC SCSI Sense RECOVERED_ERROR */
    NOT_READY,                                      /*!< MSC SCSI Sense NOT READY state*/
    MEDIUM_ERROR,                                   /*!< MSC SCSI Sense MEDIUM ERROR state*/
    HARDWARE_ERROR,                                 /*!< MSC SCSI Sense HARDWARE ERROR state*/
    ILLEGAL_REQUEST,                                /*!< MSC SCSI Sense ILLEGAL REQUEST state*/
    UNIT_ATTENTION,                                 /*!< MSC SCSI Sense UNIT ATTENTION state*/
    DATA_PROTECT,                                   /*!< MSC SCSI Sense DATA PROTECT state*/
    BLANK_CHECK,                                    /*!< MSC SCSI Sense BLANK CHECK state*/
    VENDOR_SPECIFIC,                                /*!< MSC SCSI Sense VENDOR SPECIFIC state*/
    COPY_ABORTED,                                   /*!< MSC SCSI Sense COPY ABORTED state*/
    ABORTED_COMMAND,                                /*!< MSC SCSI Sense ABORTED COMMAND state*/
    RESERVED,                                       /*!< MSC SCSI Sense RESERVED state*/
    VOLUME_OVERFLOW,                                /*!< MSC SCSI Sense VOLUME OVERFLOW state*/
    MISCOMPARE                                      /*!< MSC SCSI Sense MISCOMPARE state*/
};

typedef struct {
    uint8_t  SenseKey;                              /*!< MSC SCSI SenseKey */
    uint32_t Information;                           /*!< MSC SCSI sense Information */
    uint8_t  ASC;                                   /*!< MSC SCSI sense ASC */
    uint8_t  ASCQ;                                  /*!< MSC SCSI sense ASCQ */
} msc_scsi_sense;

#endif /* MSC_SCSI_H */
