/**
 *******************************************************************************
 * @file  usb_dev_core.h
 * @brief header file for the usb_dev_core.c
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
#ifndef __USB_DEV_CORE_H__
#define __USB_DEV_CORE_H__

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
 * @addtogroup LL_USB_DEV_CORE
 * @{
 */

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/
extern __IO uint32_t SET_TEST_MODE;

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern void usb_dev_init(usb_core_instance *pdev,
                         usb_dev_desc_func *pdesc,
                         usb_dev_class_func *class_cb,
                         usb_dev_user_func *usr_cb);
extern void usb_dev_deinit(usb_core_instance *pdev);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEV_CORE_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
