/**
 *******************************************************************************
 * @file  usb_host_core.h
 * @brief header file for the usb_host_core.c
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
#ifndef __USB_HOST_CORE_H__
#define __USB_HOST_CORE_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_host_def.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CORE
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/* USBH_CORE_Exported_Defines */
#define MSC_CLASS                         (0x08U)
#define HID_CLASS                         (0x03U)
#define MSC_PROTOCOL                      (0x50U)
#define CBI_PROTOCOL                      (0x01U)

#define DEV_DEFAULT_ADDRESS               (0U)
#define DEV_ASSIGNED_ADDRESS              (1U)

#define HOST_MAX_ERROR_CNT                (2U)

#define ENUM_LOCAL_BUF                    (256U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern void usb_host_init(usb_core_instance *pdev,
                          USBH_HOST *phost,
                          usb_host_class_callback_func *class_cbk,
                          usb_host_user_callback_func *user_cbk);
extern void usb_host_deinit(usb_core_instance *pdev, USBH_HOST *phost);
extern void usb_host_mainprocess(usb_core_instance *pdev, USBH_HOST *phost);
extern void usb_host_errorprocess(USBH_HOST *phost, HOST_STATUS errType);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_HOST_CORE_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
