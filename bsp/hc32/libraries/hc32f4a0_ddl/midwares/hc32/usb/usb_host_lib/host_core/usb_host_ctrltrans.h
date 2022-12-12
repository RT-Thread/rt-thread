/**
 *******************************************************************************
 * @file  usb_host_ctrltrans.h
 * @brief header file for the usb_host_ctrltrans.c
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
#ifndef __USB_HOST_CTRLTRANS_H__
#define __USB_HOST_CTRLTRANS_H__

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

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern void usb_host_sendctrlsetup(usb_core_instance *pdev, uint8_t *buff, uint8_t hc_num);
extern void usb_host_sendctrldata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num);
extern void usb_host_recvctrldata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num);
extern void usb_host_recvbulkdata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num);
extern void usb_host_sendbulkdata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num);
extern void usb_host_recvintdata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num);
extern void usb_host_sentintdata(usb_core_instance *pdev, uint8_t *buff, uint16_t length, uint8_t hc_num);
extern HOST_STATUS usb_host_ctrlreq(usb_core_instance *pdev, USBH_HOST *phost, uint8_t *buff, uint16_t length);
extern void usb_host_recvisocdata(usb_core_instance *pdev, uint8_t *buff, uint32_t length, uint8_t hc_num);
extern void usb_host_sendisocdata(usb_core_instance *pdev, uint8_t *buff, uint32_t length, uint8_t hc_num);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_HOST_CTRLTRANS_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
