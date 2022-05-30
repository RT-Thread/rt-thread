/**
 *******************************************************************************
 * @file  usb_host_msc_bot.h
 * @brief Head file for usb_host_msc_bot.c
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
#ifndef __USB_HOST_MSC_BOT_H__
#define __USB_HOST_MSC_BOT_H__

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
typedef union _USBH_CBW_Block {
    struct __CBW {
        uint32_t CBWSignature;
        uint32_t CBWTag;
        uint32_t CBWTransferLength;
        uint8_t CBWFlags;
        uint8_t CBWLUN;
        uint8_t CBWLength;
        uint8_t CBWCB[16];
    } field;
    uint8_t CBWArray[31];
} HostCBWPkt_TypeDef;

typedef struct {
    uint8_t  MSCState;
    uint8_t  MSCStateBkp;
    uint8_t  MSCStateCurrent;
    uint8_t  CmdStateMachine;
    uint8_t  BOTState;
    uint8_t  BOTStateBkp;
    uint8_t  *pRxTxBuff;
    uint16_t DataLength;
    uint8_t  BOTXferStatus;
} USB_HOST_BOTXFER_TypeDef;

typedef union {
    struct {
        uint32_t dCSWSignature;
        uint32_t dCSWTag;
        uint32_t dCSWDataResidue;
        uint8_t  dCSWStatus;
    } field;
    uint8_t      CSWArray[13];
} HOST_CSW_PACKET_TypeDef;

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define HOST_MSC_BOT_INIT_STATE           (0U)
#define HOST_MSC_BOT_RESET                (1U)
#define HOST_MSC_GET_MAX_LUN              (2U)
#define HOST_MSC_TEST_UNIT_READY          (3U)
#define HOST_MSC_READ_CAPACITY10          (4U)
#define HOST_MSC_MODE_SENSE6              (5U)
#define HOST_MSC_REQUEST_SENSE            (6U)
#define HOST_MSC_BOT_USB_TRANSFERS        (7U)
#define HOST_MSC_DEFAULT_APPLI_STATE      (8U)
#define HOST_MSC_CTRL_ERROR_STATE         (9U)
#define HOST_MSC_UNRECOVERED_STATE        (10U)

#define HOST_MSC_SEND_CBW                 (1U)
#define HOST_MSC_SENT_CBW                 (2U)
#define HOST_MSC_BOT_DATAIN_STATE         (3U)
#define HOST_MSC_BOT_DATAOUT_STATE        (4U)
#define HOST_MSC_RECEIVE_CSW_STATE        (5U)
#define HOST_MSC_DECODE_CSW               (6U)
#define HOST_MSC_BOT_ERROR_IN             (7U)
#define HOST_MSC_BOT_ERROR_OUT            (8U)

#define HOST_MSC_BOT_CBW_SIGNATURE        (0x43425355UL)
#define HOST_MSC_BOT_CBW_TAG              (0x20304050UL)
#define HOST_MSC_BOT_CSW_SIGNATURE        (0x53425355UL)
#define HOST_MSC_CSW_DATA_LENGTH          (13U)
#define HOST_MSC_BOT_CBW_PACKET_LENGTH    (31U)
#define HOST_MSC_CSW_LENGTH               (13U)
#define HOST_MSC_CSW_MAX_LENGTH           (63U)
#define HOST_MSC_DIR_IN                   (0U)
#define HOST_MSC_DIR_OUT                  (1U)
#define HOST_MSC_BOTH_DIR                 (2U)
#define HOST_MSC_PAGE_LENGTH              (512UL)

#define CBW_CB_LENGTH                     (16U)
#define CBW_LENGTH                        (10U)
#define CBW_LENGTH_TEST_UNIT_READY        (6U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern USB_HOST_BOTXFER_TypeDef USBH_MSC_BOTXferParam;
extern HostCBWPkt_TypeDef USBH_MSC_CBWData;
extern HOST_CSW_PACKET_TypeDef USBH_MSC_CSWData;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern void usb_host_msc_init(usb_core_instance *pdev);
extern void usb_host_msc_botxferprocess(usb_core_instance *pdev, USBH_HOST *phost);
extern uint8_t usb_host_msc_cswdecode(usb_core_instance *pdev, USBH_HOST *phost);
extern HOST_STATUS usb_host_msc_botabort(usb_core_instance *pdev, USBH_HOST *phost, uint8_t direction);

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

#endif  /* __USB_HOST_MSC_BOT_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
