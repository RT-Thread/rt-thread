/**
 *******************************************************************************
 * @file  usb_dev_mouse_class.h
 * @brief header file for the usb_dev_mouse_class.c
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
#ifndef __USB_DEV_MOUSE_CLASS_H__
#define __USB_DEV_MOUSE_CLASS_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include  "usb_dev_def.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_DEV_HID_MOUSE
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define MOUSE_CFGDESC_SIZE              (41U)
#define MOUSE_DESC_SIZE                 (9U)
#define MOUSE_REPORT_DESC_SIZE          (74U)

#define MOUSE_DESCRIPTOR_TYPE           (0x21U)
#define MOUSE_REPORT_DESC               (0x22U)


#define MOUSE_REQ_SET_PROTOCOL          (0x0BU)
#define MOUSE_REQ_GET_PROTOCOL          (0x03U)

#define MOUSE_REQ_SET_IDLE              (0x0AU)
#define MOUSE_REQ_GET_IDLE              (0x02U)


/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern usb_dev_class_func  usb_dev_mouse_cbk;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern uint8_t usb_dev_mouse_txreport(usb_core_instance *pdev, uint8_t *report, uint16_t len);

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

#endif  /* __USB_DEV_MOUSE_CLASS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
