/**
 *******************************************************************************
 * @file  usb_dev_custom_hid_class.h
 * @brief Head file for usb_dev_custom_hid_class.c
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
#ifndef __USB_DEV_CUSTOMHID_HID_CORE_H__
#define __USB_DEV_CUSTOMHID_HID_CORE_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include  "usb_dev_ctrleptrans.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CUSTOM_HID
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define CUSTOM_HID_REPORT_DESC_SIZE         (0x21)

#define USB_CUSTOM_HID_CONFIG_DESC_SIZ      (41U)
#define USB_CUSTOM_HID_DESC_SIZ             (9U)

#define CUSTOM_HID_DESCRIPTOR_TYPE          (0x21U)
#define CUSTOM_HID_REPORT_DESC              (0x22U)

#define CUSTOM_HID_REQ_SET_PROTOCOL         (0x0BU)
#define CUSTOM_HID_REQ_GET_PROTOCOL         (0x03U)

#define CUSTOM_HID_REQ_SET_IDLE             (0x0AU)
#define CUSTOM_HID_REQ_GET_IDLE             (0x02U)

#define CUSTOM_HID_REQ_SET_REPORT           (0x09U)
#define CUSTOM_HID_REQ_GET_REPORT           (0x01U)

#define LED1_REPORT_ID                      (0x01U)
#define LED1_REPORT_COUNT                   (0x01U)

#define LED2_REPORT_ID                      (0x02U)
#define LED2_REPORT_COUNT                   (0x01U)

#define LED3_REPORT_ID                      (0x03U)
#define LED3_REPORT_COUNT                   (0x01U)

#define LED4_REPORT_ID                      (0x04U)
#define LED4_REPORT_COUNT                   (0x01U)

#define KEY_REPORT_ID                       (0x05U)
#define TAMPER_REPORT_ID                    (0x06U)
#define ADC_REPORT_ID                       (0x07U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern usb_dev_class_func  class_customhid_cbk;
extern uint8_t Report_buf[64];
extern uint8_t Send_Buf[64];
extern uint8_t usb_dev_hid_txreport(usb_core_instance *pdev, uint8_t *report, uint16_t len);

/* HID Device library callbacks */
extern void usb_dev_hid_init(void *pdev);
extern void usb_dev_hid_deinit(void *pdev);
extern uint8_t usb_dev_hid_setup(void *pdev, USB_SETUP_REQ *req);
extern uint8_t *usb_dev_hid_getcfgdesc(uint16_t *length);
extern void usb_dev_hid_datain(void *pdev, uint8_t epnum);
extern void usb_dev_hid_dataout(void *pdev, uint8_t epnum);
extern void usb_dev_hid_ctrlep_rxready(void *pdev);

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

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

#endif /* __USB_DEV_CUSTOMHID_HID_CORE_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
