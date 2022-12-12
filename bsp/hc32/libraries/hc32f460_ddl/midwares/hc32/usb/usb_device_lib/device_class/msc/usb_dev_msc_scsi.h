/**
 *******************************************************************************
 * @file  usb_dev_msc_scsi.h
 * @brief header file for the usb_dev_msc_scsi.c
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __USB_DEV_MSC_SCSI_H__
#define __USB_DEV_MSC_SCSI_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_dev_def.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_MSC
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/
typedef struct _SENSE_ITEM {
    char Skey;
    union {
        struct _ASCs {
            char ASC;
            char ASCQ;
        } b;
        unsigned int ASC;
        char        *pData;
    } w;
} SCSI_Sense_TypeDef;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define SENSE_LIST_DEEPTH                           (4U)

/* SCSI Commands */
#define SCSI_FORMAT_UNIT                            (0x04U)
#define SCSI_INQUIRY                                (0x12U)
#define SCSI_MODE_SELECT6                           (0x15U)
#define SCSI_MODE_SELECT10                          (0x55U)
#define SCSI_MODE_SENSE6                            (0x1AU)
#define SCSI_MODE_SENSE10                           (0x5AU)
#define SCSI_ALLOW_MEDIUM_REMOVAL                   (0x1EU)
#define SCSI_READ6                                  (0x08U)
#define SCSI_READ10                                 (0x28U)
#define SCSI_READ12                                 (0xA8U)
#define SCSI_READ16                                 (0x88U)

#define SCSI_READ_CAPACITY10                        (0x25U)
#define SCSI_READ_CAPACITY16                        (0x9EU)

#define SCSI_REQUEST_SENSE                          (0x03U)
#define SCSI_START_STOP_UNIT                        (0x1BU)
#define SCSI_TEST_UNIT_READY                        (0x00U)
#define SCSI_WRITE6                                 (0x0AU)
#define SCSI_WRITE10                                (0x2AU)
#define SCSI_WRITE12                                (0xAAU)
#define SCSI_WRITE16                                (0x8AU)

#define SCSI_VERIFY10                               (0x2FU)
#define SCSI_VERIFY12                               (0xAFU)
#define SCSI_VERIFY16                               (0x8FU)

#define SCSI_SEND_DIAGNOSTIC                        (0x1DU)
#define SCSI_READ_FORMAT_CAPACITIES                 (0x23U)

#define NO_SENSE                                    (0U)
#define RECOVERED_ERROR                             (1U)
#define NOT_READY                                   (2U)
#define MEDIUM_ERROR                                (3U)
#define HARDWARE_ERROR                              (4U)
#define ILLEGAL_REQUEST                             (5U)
#define UNIT_ATTENTION                              (6U)
#define DATA_PROTECT                                (7U)
#define BLANK_CHECK                                 (8U)
#define VENDOR_SPECIFIC                             (9U)
#define COPY_ABORTED                                (10U)
#define ABORTED_COMMAND                             (11U)
#define VOLUME_OVERFLOW                             (13U)
#define MISCOMPARE                                  (14U)

#define INVALID_CDB                                 (0x20U)
#define INVALID_FIELED_IN_COMMAND                   (0x24U)
#define PARAMETER_LIST_LENGTH_ERROR                 (0x1AU)
#define INVALID_FIELD_IN_PARAMETER_LIST             (0x26U)
#define ADDRESS_OUT_OF_RANGE                        (0x21U)
#define MEDIUM_NOT_PRESENT                          (0x3AU)
#define MEDIUM_HAVE_CHANGED                         (0x28U)
#define WRITE_PROTECTED                             (0x27U)
#define UNRECOVERED_READ_ERROR                      (0x11U)
#define WRITE_FAULT                                 (0x03U)

#define READ_FORMAT_CAPACITY_DATA_LEN               (0x0Cu)
#define READ_CAPACITY10_DATA_LEN                    (0x08U)
#define MODE_SENSE10_DATA_LEN                       (0x08U)
#define MODE_SENSE6_DATA_LEN                        (0x04U)
#define REQUEST_SENSE_DATA_LEN                      (0x12U)
#define STANDARD_INQUIRY_DATA_LEN                   (0x24U)
#define BLKVFY                                      (0x04U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern SCSI_Sense_TypeDef SCSI_Sense [SENSE_LIST_DEEPTH];
extern uint8_t SCSI_Sense_Head;
extern uint8_t SCSI_Sense_Tail;

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
extern int8_t scsi_cmdprocess(usb_core_instance *pdev, uint8_t lun, uint8_t *params);
extern void scsi_sensecode(uint8_t sKey, uint8_t ASC);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEV_MSC_SCSI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
