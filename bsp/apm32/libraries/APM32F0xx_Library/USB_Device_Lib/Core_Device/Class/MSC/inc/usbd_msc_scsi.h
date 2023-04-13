/*!
 * @file        usbd_msc_scsi.h
 *
 * @brief       MSC scsi
 *
 * @version     V1.0.1
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __USBD_MSC_SCSI_H_
#define __USBD_MSC_SCSI_H_

/* Includes */
#include "usbd_core.h"

/** @addtogroup USB_Driver_Library USB Driver Library
  @{
*/

/** @addtogroup Core_Device Core Device
  @{
*/

/** @addtogroup Class
  @{
*/

/** @addtogroup MSC_SCSI
  @{
*/

/** @defgroup MSC_SCSI_Macros Macros
  @{
*/

#define SCSI_SENSE_LIST_NUMBER                      4
#define SCSI_INQUIRY_LENGTH                         36

/* SCSI Commands */
#define SCSI_CMD_FORMAT_UNIT                        ((uint8_t)0x04)
#define SCSI_CMD_INQUIRY                            ((uint8_t)0x12)
#define SCSI_CMD_MODE_SELECT_6                      ((uint8_t)0x15)
#define SCSI_CMD_MODE_SELECT_10                     ((uint8_t)0x55)
#define SCSI_CMD_MODE_SENSE_6                       ((uint8_t)0x1A)
#define SCSI_CMD_MODE_SENSE_10                      ((uint8_t)0x5A)
#define SCSI_CMD_ALLOW_MEDIUM_REMOVAL               ((uint8_t)0x1E)
#define SCSI_CMD_READ_6                             ((uint8_t)0x08)
#define SCSI_CMD_READ_10                            ((uint8_t)0x28)
#define SCSI_CMD_READ_12                            ((uint8_t)0xA8)
#define SCSI_CMD_READ_16                            ((uint8_t)0x88)

#define SCSI_CMD_READ_CAPACITY_10                   ((uint8_t)0x25)
#define SCSI_CMD_READ_CAPACITY_16                   ((uint8_t)0x9E)

#define SCSI_CMD_REQUEST_SENSE                      ((uint8_t)0x03)
#define SCSI_CMD_START_STOP_UNIT                    ((uint8_t)0x1B)
#define SCSI_CMD_TEST_UNIT_READY                    ((uint8_t)0x00)
#define SCSI_CMD_WRITE6                             ((uint8_t)0x0A)
#define SCSI_CMD_WRITE10                            ((uint8_t)0x2A)
#define SCSI_CMD_WRITE12                            ((uint8_t)0xAA)
#define SCSI_CMD_WRITE16                            ((uint8_t)0x8A)

#define SCSI_CMD_VERIFY_10                          ((uint8_t)0x2F)
#define SCSI_CMD_VERIFY_12                          ((uint8_t)0xAF)
#define SCSI_CMD_VERIFY_16                          ((uint8_t)0x8F)

#define SCSI_CMD_SEND_DIAGNOSTIC                    ((uint8_t)0x1D)
#define SCSI_CMD_READ_FORMAT_CAPACITIES             ((uint8_t)0x23)

#define SCSI_ASC_INVALID_CDB                         0x20
#define SCSI_ASC_INVALID_FIELED_IN_COMMAND           0x24
#define SCSI_ASC_PARAMETER_LIST_LENGTH_ERROR         0x1A
#define SCSI_ASC_INVALID_FIELD_IN_PARAMETER_LIST     0x26
#define SCSI_ASC_ADDRESS_OUT_OF_RANGE                0x21
#define SCSI_ASC_MEDIUM_NOT_PRESENT                  0x3A
#define SCSI_ASC_MEDIUM_HAVE_CHANGED                 0x28
#define SCSI_ASC_WRITE_PROTECTED                     0x27
#define SCSI_ASC_UNRECOVERED_READ_ERROR              0x11
#define SCSI_ASC_WRITE_FAULT                         0x03

#define SCSI_READ_FORMAT_CAPACITY_DATA_LEN           0x0C
#define SCSI_READ_CAPACITY10_DATA_LEN                0x08
#define SCSI_MODE_SENSE10_DATA_LEN                   0x08
#define SCSI_MODE_SENSE6_DATA_LEN                    0x04
#define SCSI_REQUEST_SENSE_DATA_LEN                  0x12
#define SCSI_STANDARD_INQUIRY_DATA_LEN               0x24
#define SCSI_BLKVFY                                  0x04

/**@} end of group MSC_SCSI_Macros */

/** @defgroup MSC_SCSI_Enumerations Enumerations
  @{
*/

/**
 * @brief   SCSI function status
 */
typedef enum
{
    SCSI_FAIL,
    SCSI_OK,
} SCSI_STATUS_T;

/**
 * @brief   SCSI Sense Key
 */
typedef enum
{
    SCSI_SKEY_NO_SENSE,
    SCSI_SKEY_RECOVERED_ERROR,
    SCSI_SKEY_NOT_READY,
    SCSI_SKEY_MEDIUM_ERROR,
    SCSI_SKEY_HARDWARE_ERROR,
    SCSI_SKEY_ILLEGAL_REQUEST,
    SCSI_SKEY_UNIT_ATTENTION,
    SCSI_SKEY_DATA_PROTECT,
    SCSI_SKEY_BLANK_CHECK,
    SCSI_SKEY_VENDOR_SPECIFIC,
    SCSI_SKEY_COPY_ABORTED,
    SCSI_SKEY_ABORTED_COMMAND,
    SCSI_SKEY_VOLUME_OVERFLOW = 13,
    SCSI_SKEY_MISCOMPARE      = 14
} SCSI_SKEY_T;

/**@} end of group MSC_SCSI_Enumerations */

/** @defgroup MSC_SCSI_Structures Structures
  @{
*/

/**
 * @brief   SCSI Sense
 */
typedef struct
{
    uint8_t sensekey;
    uint8_t ASC;
    uint8_t ASCQ;
} SCSI_Sense_T;

/**@} end of group MSC_SCSI_Structures */

/** @defgroup MSC_SCSI_Variables Variables
  @{
*/

extern SCSI_Sense_T g_scsiSense[SCSI_SENSE_LIST_NUMBER];
extern uint8_t g_senseTxCnt;
extern uint8_t g_sensePutCnt;

/**@} end of group MSC_SCSI_Variables */

/** @defgroup MSC_SCSI_Functions Functions
  @{
*/

uint8_t SCSI_CmdHandler(uint8_t lun, uint8_t* cmd);
void   SCSI_PutSenseCode(uint8_t lun, uint8_t sKey, uint8_t ASC, uint8_t ASCQ);

#endif

/**@} end of group MSC_SCSI_Functions */
/**@} end of group MSC_SCSI */
/**@} end of group Class */
/**@} end of group Core_Device */
/**@} end of group USB_Driver_Library */
