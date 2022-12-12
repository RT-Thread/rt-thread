/**
 *******************************************************************************
 * @file  usb_host_stdreq.h
 * @brief Header file for usb_host_stdreq.c
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
#ifndef __USB_HOST_STDREQ_H__
#define __USB_HOST_STDREQ_H__

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

/* USBH_STDREQ_Exported_Defines */
/* Standard Feature Selector for clear feature command */
#define FEATURE_SELECTOR_ENDPOINT         (0x00U)
#define FEATURE_SELECTOR_DEVICE           (0x01U)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern HOST_STATUS usb_host_getdesc(usb_core_instance *pdev,
                                    USBH_HOST *phost,
                                    uint8_t req_type,
                                    uint16_t value_idx,
                                    uint8_t *buff,
                                    uint16_t length);

extern HOST_STATUS usb_host_getdevdesc(usb_core_instance *pdev, USBH_HOST *phost, uint8_t length);

HOST_STATUS usb_host_getstringdesc(usb_core_instance *pdev,
                                   USBH_HOST *phost,
                                   uint8_t string_index,
                                   uint8_t *buff,
                                   uint16_t length);

extern HOST_STATUS usb_host_setconfig(usb_core_instance *pdev, USBH_HOST *phost, uint16_t cfg_idx);

extern HOST_STATUS usb_host_getcfgdesc(usb_core_instance *pdev, USBH_HOST *phost, uint16_t  length);

extern HOST_STATUS usb_host_setdevaddr(usb_core_instance *pdev, USBH_HOST *phost, uint8_t DeviceAddress);

extern HOST_STATUS usb_host_clrfeature(usb_core_instance *pdev, USBH_HOST *phost, uint8_t ep_num, uint8_t hc_num);

extern HOST_STATUS usb_host_setintf(usb_core_instance *pdev, USBH_HOST *phost, uint8_t ep_num, uint8_t altSetting);

extern USB_HOST_DescHeader_TypeDef *usb_host_getnextdesc(uint8_t *pbuf, uint16_t *ptr);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_HOST_STDREQ_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
