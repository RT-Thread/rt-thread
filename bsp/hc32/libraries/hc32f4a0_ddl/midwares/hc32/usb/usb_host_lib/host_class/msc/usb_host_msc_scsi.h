/**
 *******************************************************************************
 * @file  usb_host_msc_scsi.h
 * @brief Head file for usb_host_msc_scsi.c
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
#ifndef __USB_HOST_MSC_SCSI_H__
#define __USB_HOST_MSC_SCSI_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_host_stdreq.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_MSC
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/* USBH_MSC_SCSI_Exported_Types */
typedef enum {
    USB_HOST_MSC_OK = 0U,
    USB_HOST_MSC_FAIL,
    USB_HOST_MSC_PHASE_ERROR,
    USB_HOST_MSC_BUSY
} USB_HOST_MSC_STATUS;

typedef struct {
    uint32_t MSC_Capacity;
    uint32_t MSC_Sense;
    uint16_t MSC_PageLength;
    uint8_t  MSC_BulkOutEP;
    uint8_t  MSC_BulkInEP;
    uint8_t  MSC_WriteProtect;
} MSC_PARAMETER;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define USB_HOST_MSC_CMD_SEND             (1)
#define USB_HOST_MSC_CMD_WAIT             (2)

#define OPCODE_TEST_UNIT_READY            (0x00U)
#define OPCODE_READ_CAPACITY10            (0x25U)
#define OPCODE_MODE_SENSE6                (0x1AU)
#define OPCODE_READ10                     (0x28U)
#define OPCODE_WRITE10                    (0x2AU)
#define OPCODE_REQUEST_SENSE              (0x03U)

#define DESC_REQUEST_SENSE                (0x00U)
#define ALLOCATION_LENGTH_REQUEST_SENSE   (63U)
#define XFER_LEN_READ_CAPACITY10          (8U)
#define XFER_LEN_MODE_SENSE6              (63U)

#define MASK_MODE_SENSE_WRITE_PROTECT     (0x80U)
#define MODE_SENSE_PAGE_CONTROL_FIELD     (0x00U)
#define MODE_SENSE_PAGE_CODE              (0x3FU)
#define DISK_WRITE_PROTECTED              (0x01U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern MSC_PARAMETER USB_HOST_MSC_Param;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern USB_HOST_MSC_STATUS usb_host_msc_TestUnitReady(usb_core_instance *pdev);
extern USB_HOST_MSC_STATUS usb_host_msc_ReadCapacity10(usb_core_instance *pdev);
extern USB_HOST_MSC_STATUS usb_host_msc_ModeSense6(usb_core_instance *pdev);
extern USB_HOST_MSC_STATUS usb_host_msc_RequestSense(usb_core_instance *pdev);
extern USB_HOST_MSC_STATUS usb_host_msc_Write10(usb_core_instance *pdev,
                                                uint8_t *dataBuffer,
                                                uint32_t address,
                                                uint32_t nbOfbytes);
extern USB_HOST_MSC_STATUS usb_host_msc_Read10(usb_core_instance *pdev,
                                                uint8_t *dataBuffer,
                                                uint32_t address,
                                                uint32_t nbOfbytes);

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

#endif  /* __USB_HOST_MSC_SCSI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


