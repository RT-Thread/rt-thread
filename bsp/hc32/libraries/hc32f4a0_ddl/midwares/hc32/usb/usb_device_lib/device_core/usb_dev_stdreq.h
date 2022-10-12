/**
 *******************************************************************************
 * @file  usb_dev_stdreq.h
 * @brief header file for the usb_dev_stdreq.c
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
#ifndef __USB_DEV_STDREQ_H__
#define __USB_DEV_STDREQ_H__

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
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
void usb_standarddevreq(usb_core_instance *pdev, USB_SETUP_REQ *req);
void usb_standarditfreq(usb_core_instance *pdev, USB_SETUP_REQ *req);
void usb_standardepreq(usb_core_instance *pdev, USB_SETUP_REQ *req);
void usb_parsesetupreq(usb_core_instance *pdev, USB_SETUP_REQ *req);
void usb_ctrlerr(usb_core_instance *pdev);
void usb_getstring(uint8_t *desc, uint8_t *unicode, uint16_t *len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEV_STDREQ_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
