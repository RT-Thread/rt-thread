/**
 *******************************************************************************
 * @file  usb_host_cfgch.h
 * @brief header file for the usb_host_cfgch.c
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
#ifndef __USB_HOST_CFGCH_H__
#define __USB_HOST_CFGCH_H__

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

/* USBH_HCS_Exported_Defines */
#define MAX_CHNUM           (12U)

#define HC_OK               (0x0000U)
#define HC_USED             (0x8000U)
#define HC_ERROR            (0xFFFFU)
#define HC_USED_MASK        (0x7FFFU)

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
extern uint8_t usb_host_distrch(usb_core_instance *pdev, uint8_t ep_addr);

extern uint8_t usb_host_freech(usb_core_instance *pdev, uint8_t idx);

extern void usb_host_dedistrallch(usb_core_instance *pdev);

extern void usb_host_chopen(usb_core_instance *pdev,
                            uint8_t  hc_num,
                            uint8_t  dev_address,
                            uint8_t  speed,
                            uint8_t  ep_type,
                            uint16_t mps);

extern void usb_host_mdfch(usb_core_instance *pdev,
                           uint8_t  hc_num,
                           uint8_t  dev_address,
                           uint8_t  speed,
                           uint8_t  ep_type,
                           uint16_t mps);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __USB_HOST_CFGCH_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
