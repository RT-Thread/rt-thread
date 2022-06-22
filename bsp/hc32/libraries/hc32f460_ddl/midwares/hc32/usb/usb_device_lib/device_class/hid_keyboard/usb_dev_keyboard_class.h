/**
 *******************************************************************************
 * @file  usb_dev_keyboard_class.h
 * @brief Head file for usb_dev_keyboard_class.c
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
#ifndef __USB_DEV_KEYBOARD_CLASS_H__
#define __USB_DEV_KEYBOARD_CLASS_H__

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
 * @addtogroup LL_USB_DEV_HID_KEYBOARD
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define KEYBOARD_CFGDESC_SIZE              (41U)
#define KEYBOARD_DESC_SIZE                 (9U)
#define KEYBOARD_REPORT_DESC_SIZE          (66U)

#define KEYBOARD_DESCRIPTOR_TYPE           (0x21U)
#define KEYBOARD_REPORT_DESC               (0x22U)


#define KEYBOARD_REQ_SET_PROTOCOL          (0x0BU)
#define KEYBOARD_REQ_GET_PROTOCOL          (0x03U)

#define KEYBOARD_REQ_SET_IDLE              (0x0AU)
#define KEYBOARD_REQ_GET_IDLE              (0x02U)


/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern usb_dev_class_func  usb_dev_keyboard_cbk;

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

#endif  /* __USB_DEV_KEYBOARD_CLASS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
