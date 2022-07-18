/**
 *******************************************************************************
 * @file  usb_dev_def.h
 * @brief general defines for the usb device library
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
#ifndef __USB_DEV_DEF_H__
#define __USB_DEV_DEF_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_lib.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CORE
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#ifndef NULL
#define NULL    (0U)
#endif

/* Function return status */
#define USB_DEV_OK                                      (0U)
#define USB_DEV_BUSY                                    (1U)
#define USB_DEV_FAIL                                    (2U)

/*  Device Status */
#define USB_DEV_DEFAULT                                 (1U)
#define USB_DEV_ADDRESSED                               (2U)
#define USB_DEV_CONFIGURED                              (3U)
#define USB_DEV_SUSPENDED                               (4U)

/* String descriptor type */
#define LANGID_STR_IDX                                  (0x00U)
#define MFC_STR_IDX                                     (0x01U)
#define PRODUCT_STR_IDX                                 (0x02U)
#define SERIAL_STR_IDX                                  (0x03U)
#define CONFIG_STR_IDX                                  (0x04U)
#define INTERFACE_STR_IDX                               (0x05U)

/* Request type */
#define USB_REQ_TYPE_STANDARD                           (0x00U)
#define USB_REQ_TYPE_CLASS                              (0x20U)
#define USB_REQ_TYPE_VENDOR                             (0x40U)
#define USB_REQ_TYPE_MASK                               (0x60U)

/* Request recipient */
#define USB_REQ_RECIPIENT_DEVICE                        (0x00U)
#define USB_REQ_RECIPIENT_INTERFACE                     (0x01U)
#define USB_REQ_RECIPIENT_ENDPOINT                      (0x02U)
#define USB_REQ_RECIPIENT_MASK                          (0x03U)

/* Standart request type */
#define USB_REQ_GET_STATUS                              (0x00U)
#define USB_REQ_CLEAR_FEATURE                           (0x01U)
#define USB_REQ_SET_FEATURE                             (0x03U)
#define USB_REQ_SET_ADDRESS                             (0x05U)
#define USB_REQ_GET_DESCRIPTOR                          (0x06U)
#define USB_REQ_SET_DESCRIPTOR                          (0x07U)
#define USB_REQ_GET_CONFIGURATION                       (0x08U)
#define USB_REQ_SET_CONFIGURATION                       (0x09U)
#define USB_REQ_GET_INTERFACE                           (0x0AU)
#define USB_REQ_SET_INTERFACE                           (0x0BU)
#define USB_REQ_SYNCH_FRAME                             (0x0CU)

/* Descriptor type */
#define USB_DESC_TYPE_DEVICE                            (1U)
#define USB_DESC_TYPE_CONFIGURATION                     (2U)
#define USB_DESC_TYPE_STRING                            (3U)
#define USB_DESC_TYPE_INTERFACE                         (4U)
#define USB_DESC_TYPE_ENDPOINT                          (5U)
#define USB_DESC_TYPE_DEVICE_QUALIFIER                  (6U)
#define USB_DESC_TYPE_OTHER_SPEED_CONFIGURATION         (7U)

/* Configuration status */
#define USB_CONFIG_REMOTE_WAKEUP                        (2U)
#define USB_CONFIG_SELF_POWERED                         (1U)

/* USB device feature */
#define USB_FEATURE_EP_HALT                             (0U)
#define USB_FEATURE_REMOTE_WAKEUP                       (1U)
#define USB_FEATURE_TEST_MODE                           (2U)

/* USB device configuration status */
#define USB_DEV_CONFIG_CLEAR                            (0U)
#define USB_DEV_CONFIG_SET                              (1U)
#define USB_DEV_CONFIG_GET                              (2U)

/* USB EP0 state */
#define USB_EP0_IDLE                                    (0U)
#define USB_EP0_SETUP                                   (1U)
#define USB_EP0_DATA_IN                                 (2U)
#define USB_EP0_DATA_OUT                                (3U)
#define USB_EP0_STATUS_IN                               (4U)
#define USB_EP0_STATUS_OUT                              (5U)
#define USB_EP0_STALL                                   (6U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEV_DEF_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
