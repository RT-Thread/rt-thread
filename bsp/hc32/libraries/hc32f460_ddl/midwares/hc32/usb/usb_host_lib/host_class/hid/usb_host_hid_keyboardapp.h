/**
 *******************************************************************************
 * @file  usb_host_hid_keyboardapp.h
 * @brief Head file for usb_host_hid_keyboardapp.c
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
#ifndef __USB_HOST_HID_KEYBOARDAPP_H__
#define __USB_HOST_HID_KEYBOARDAPP_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "usb_host_hid_class.h"

/**
 * @addtogroup LL_USB_LIB
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_CLASS
 * @{
 */

/**
 * @addtogroup LL_USB_HOST_HID
 * @{
 */

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
#define QWERTY_KEYBOARD
/* #define AZERTY_KEYBOARD */

#define  KBD_LEFT_CTRL              (0x01U)
#define  KBD_LEFT_SHIFT             (0x02U)
#define  KBD_LEFT_ALT               (0x04U)
#define  KBD_LEFT_GUI               (0x08U)
#define  KBD_RIGHT_CTRL             (0x10U)
#define  KBD_RIGHT_SHIFT            (0x20U)
#define  KBD_RIGHT_ALT              (0x40U)
#define  KBD_RIGHT_GUI              (0x80U)

#define  KBR_MAX_NBR_PRESSED        (6U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern HID_cb_TypeDef HID_KEYBRD_cb;

/*******************************************************************************
 * Global function prototypes (definition in C source)
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

#endif /* __USB_HOST_HID_KEYBOARDAPP_H__ */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
