/**
 *******************************************************************************
 * @file  usb_dev_ctrleptrans.h
 * @brief header file for the usb_dev_ctrleptrans.c file
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
#ifndef __USB_DEV_CTRLEPTRANS_H__
#define __USB_DEV_CTRLEPTRANS_H__

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
extern void usb_ctrldatatx(usb_core_instance  *pdev, uint8_t *pbuf, uint16_t len);
extern void usb_ctrldatacontinuetx(usb_core_instance *pdev, uint8_t *pbuf, uint16_t len);
extern void usb_ctrldatarx(usb_core_instance  *pdev, uint8_t *pbuf, uint16_t len);
extern void usb_ctrldatacontinuerx(usb_core_instance *pdev, uint8_t *pbuf, uint16_t len);
extern void usb_ctrlstatustx(usb_core_instance *pdev);
extern void usb_ctrlstatusrx(usb_core_instance *pdev);
extern uint16_t usb_getrxcnt(usb_core_instance *pdev, uint8_t epnum);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_DEV_CTRLEPTRANS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
