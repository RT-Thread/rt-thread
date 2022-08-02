/**
 *******************************************************************************
 * @file  usb_host_hid_mouseapp.h
 * @brief Head file for usb_host_hid_mouseapp.c
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
#ifndef __USB_HOST_HID_MOUSEAPP_H__
#define __USB_HOST_HID_MOUSEAPP_H__

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
typedef struct _HID_MOUSE_Data {
    uint8_t              z;
    uint8_t              button;
    uint8_t              x;               /* Not Supported */
    uint8_t              y;
}
HID_MOUSE_Data_TypeDef;

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern HID_cb_TypeDef HID_MOUSE_cb;
extern HID_MOUSE_Data_TypeDef    HID_MOUSE_Data;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
void user_mouse_init(void);
void user_mouse_dataprocess(HID_MOUSE_Data_TypeDef *data);

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

#endif /* __USB_HOST_HID_MOUSEAPP_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
